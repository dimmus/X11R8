/* -*- c-basic-offset: 4 -*- */
/*
 * Copyright 2006 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config_intel.h"
#endif

#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "xorg-server.h"
#include "xf86.h"
#include "intel.h"
#include "i830_reg.h"
#include "i915_drm.h"
#include "i965_reg.h"

#include "intel_uxa.h"

#define DUMP_BATCHBUFFERS NULL // "/tmp/i915-batchbuffers.dump"

static void
intel_end_vertex(intel_screen_private *intel)
{
    if (intel->vertex_bo)
    {
        if (intel->vertex_used)
        {
            dri_bo_subdata(intel->vertex_bo,
                           0,
                           intel->vertex_used * 4,
                           intel->vertex_ptr);
            intel->vertex_used = 0;
        }

        dri_bo_unreference(intel->vertex_bo);
        intel->vertex_bo = NULL;
    }

    intel->vertex_id = 0;
}

void
intel_next_vertex(intel_screen_private *intel)
{
    intel_end_vertex(intel);

    intel->vertex_bo =
        dri_bo_alloc(intel->bufmgr, "vertex", sizeof(intel->vertex_ptr), 4096);
}

static dri_bo *
bo_alloc(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);
    int                   size  = 4 * 4096;
    /* The 865 has issues with larger-than-page-sized batch buffers. */
    if (IS_I865G(intel)) size = 4096;
    return dri_bo_alloc(intel->bufmgr, "batch", size, 4096);
}

static void
intel_next_batch(ScrnInfoPtr scrn, int mode)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);
    dri_bo               *tmp;

    drm_intel_gem_bo_clear_relocs(intel->batch_bo, 0);

    tmp                        = intel->last_batch_bo[mode];
    intel->last_batch_bo[mode] = intel->batch_bo;
    intel->batch_bo            = tmp;

    intel->batch_used = 0;

    /* We don't know when another client has executed, so we have
	 * to reinitialize our 3D state per batch.
	 */
    intel->last_3d = LAST_3D_OTHER;
}

void
intel_batch_init(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);

    intel->batch_emit_start = 0;
    intel->batch_emitting   = 0;
    intel->vertex_id        = 0;

    intel->last_batch_bo[0] = bo_alloc(scrn);
    intel->last_batch_bo[1] = bo_alloc(scrn);

    intel->batch_bo   = bo_alloc(scrn);
    intel->batch_used = 0;
    intel->last_3d    = LAST_3D_OTHER;
}

void
intel_batch_teardown(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);
    int                   i;

    for (i = 0; i < ARRAY_SIZE(intel->last_batch_bo); i++)
    {
        if (intel->last_batch_bo[i] != NULL)
        {
            dri_bo_unreference(intel->last_batch_bo[i]);
            intel->last_batch_bo[i] = NULL;
        }
    }

    if (intel->batch_bo != NULL)
    {
        dri_bo_unreference(intel->batch_bo);
        intel->batch_bo = NULL;
    }

    if (intel->vertex_bo)
    {
        dri_bo_unreference(intel->vertex_bo);
        intel->vertex_bo = NULL;
    }

    while (!list_is_empty(&intel->batch_pixmaps))
        list_del(intel->batch_pixmaps.next);
}

static void
intel_batch_do_flush(ScrnInfoPtr scrn)
{
    intel_screen_private    *intel = intel_get_screen_private(scrn);
    struct intel_uxa_pixmap *priv;

    list_for_each_entry(priv, &intel->batch_pixmaps, batch) priv->dirty = 0;
}

static void
intel_emit_post_sync_nonzero_flush(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);

    /* keep this entire sequence of 3 PIPE_CONTROL cmds in one batch to
	 * avoid upsetting the gpu. */
    BEGIN_BATCH(3 * 4);
    OUT_BATCH(BRW_PIPE_CONTROL | (4 - 2));
    OUT_BATCH(BRW_PIPE_CONTROL_CS_STALL | BRW_PIPE_CONTROL_STALL_AT_SCOREBOARD);
    OUT_BATCH(0); /* address */
    OUT_BATCH(0); /* write data */

    OUT_BATCH(BRW_PIPE_CONTROL | (4 - 2));
    OUT_BATCH(BRW_PIPE_CONTROL_WRITE_QWORD);
    OUT_RELOC(intel->wa_scratch_bo,
              I915_GEM_DOMAIN_INSTRUCTION,
              I915_GEM_DOMAIN_INSTRUCTION,
              0);
    OUT_BATCH(0); /* write data */

    /* now finally the _real flush */
    OUT_BATCH(BRW_PIPE_CONTROL | (4 - 2));
    OUT_BATCH(BRW_PIPE_CONTROL_WC_FLUSH | BRW_PIPE_CONTROL_TC_FLUSH |
              BRW_PIPE_CONTROL_NOWRITE);
    OUT_BATCH(0); /* write address */
    OUT_BATCH(0); /* write data */
    ADVANCE_BATCH();
}

void
intel_batch_emit_flush(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);
    int                   flags;

    assert(!intel->in_batch_atomic);

    /* Big hammer, look to the pipelined flushes in future. */
    if ((INTEL_INFO(intel)->gen >= 0100))
    {
        /* Only BLT supported */
        BEGIN_BATCH_BLT(4);
        OUT_BATCH(MI_FLUSH_DW | 2);
        OUT_BATCH(0); /* address low */
        OUT_BATCH(0); /* address high */
        OUT_BATCH(0); /* dword data */
        ADVANCE_BATCH();
    }
    else if ((INTEL_INFO(intel)->gen >= 060))
    {
        if (intel->current_batch == BLT_BATCH)
        {
            BEGIN_BATCH_BLT(4);
            OUT_BATCH(MI_FLUSH_DW | 2);
            OUT_BATCH(0); /* address */
            OUT_BATCH(0); /* qword low */
            OUT_BATCH(0); /* qword high */
            ADVANCE_BATCH();
        }
        else
        {
            if ((INTEL_INFO(intel)->gen == 060))
            {
                /* HW-Workaround for Sandybdrige */
                intel_emit_post_sync_nonzero_flush(scrn);
            }
            else
            {
                BEGIN_BATCH(4);
                OUT_BATCH(BRW_PIPE_CONTROL | (4 - 2));
                OUT_BATCH(BRW_PIPE_CONTROL_WC_FLUSH |
                          BRW_PIPE_CONTROL_TC_FLUSH | BRW_PIPE_CONTROL_NOWRITE);
                OUT_BATCH(0); /* write address */
                OUT_BATCH(0); /* write data */
                ADVANCE_BATCH();
            }
        }
    }
    else
    {
        flags = MI_WRITE_DIRTY_STATE | MI_INVALIDATE_MAP_CACHE;
        if (INTEL_INFO(intel)->gen >= 040) flags = 0;

        BEGIN_BATCH(1);
        OUT_BATCH(MI_FLUSH | flags);
        ADVANCE_BATCH();
    }
    intel_batch_do_flush(scrn);
}

void
intel_batch_submit(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);
    int                   ret;

    assert(!intel->in_batch_atomic);

    if (intel->vertex_flush) intel->vertex_flush(intel);
    intel_end_vertex(intel);

    if (intel->batch_flush) intel->batch_flush(intel);

    if (intel->batch_used == 0) return;

    if (intel->current_batch == I915_EXEC_BLT && INTEL_INFO(intel)->gen >= 060)
    {
        OUT_BATCH(MI_FLUSH_DW);
        OUT_BATCH(0);
        OUT_BATCH(0);
        OUT_BATCH(0);
        OUT_BATCH(MI_LOAD_REGISTER_IMM);
        OUT_BATCH(BCS_SWCTRL);
        OUT_BATCH((BCS_SWCTRL_DST_Y | BCS_SWCTRL_SRC_Y) << 16);
    }

    /* Mark the end of the batchbuffer. */
    OUT_BATCH(MI_BATCH_BUFFER_END);
    /* Emit a padding dword if we aren't going to be quad-word aligned. */
    if (intel->batch_used & 1) OUT_BATCH(MI_NOOP);

    if (DUMP_BATCHBUFFERS)
    {
        FILE *file = fopen(DUMP_BATCHBUFFERS, "a");
        if (file)
        {
            fwrite(intel->batch_ptr, intel->batch_used * 4, 1, file);
            fclose(file);
        }
    }

    ret = dri_bo_subdata(intel->batch_bo,
                         0,
                         intel->batch_used * 4,
                         intel->batch_ptr);
    if (ret == 0)
    {
        ret = drm_intel_bo_mrb_exec(
            intel->batch_bo,
            intel->batch_used * 4,
            NULL,
            0,
            0xffffffff,
            (HAS_BLT(intel) ? intel->current_batch : I915_EXEC_DEFAULT));
    }

    if (ret != 0)
    {
        static int once;
        if (!once)
        {
            if (ret == -EIO)
            {
                /* The GPU has hung and unlikely to recover by this point. */
                xf86DrvMsg(scrn->scrnIndex,
                           X_ERROR,
                           "Detected a hung GPU, disabling acceleration.\n");
                xf86DrvMsg(
                    scrn->scrnIndex,
                    X_ERROR,
                    "When reporting this, please include i915_error_state from "
                    "debugfs and the full dmesg.\n");
            }
            else
            {
                /* The driver is broken. */
                xf86DrvMsg(scrn->scrnIndex,
                           X_ERROR,
                           "Failed to submit batch buffer, expect rendering "
                           "corruption: %s.\n ",
                           strerror(-ret));
            }
            uxa_set_force_fallback(xf86ScrnToScreen(scrn), TRUE);
            intel->force_fallback = TRUE;
            once                  = 1;
        }
    }

    while (!list_is_empty(&intel->batch_pixmaps))
    {
        struct intel_uxa_pixmap *entry;

        entry = list_first_entry(&intel->batch_pixmaps,
                                 struct intel_uxa_pixmap,
                                 batch);

        entry->busy  = -1;
        entry->dirty = 0;
        list_del(&entry->batch);
    }

    if (intel->debug_flush & DEBUG_FLUSH_WAIT)
        drm_intel_bo_wait_rendering(intel->batch_bo);

    intel_next_batch(scrn, intel->current_batch == I915_EXEC_BLT);

    if (intel->batch_commit_notify) intel->batch_commit_notify(intel);

    intel->current_batch = 0;
}

void
intel_uxa_debug_flush(ScrnInfoPtr scrn)
{
    intel_screen_private *intel = intel_get_screen_private(scrn);

    if (intel->debug_flush & DEBUG_FLUSH_CACHES) intel_batch_emit_flush(scrn);

    if (intel->debug_flush & DEBUG_FLUSH_BATCHES) intel_batch_submit(scrn);
}
