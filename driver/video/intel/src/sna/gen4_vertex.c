/*
 * Copyright 2012 Intel Corporation
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
 *    Chris Wilson <chris@chris-wilson.co.uk>
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config_intel.h"
#endif

#include "sna.h"
#include "sna_render.h"
#include "sna_render_inline.h"
#include "gen4_vertex.h"

#ifndef sse2
#  define sse2
#endif

void
gen4_vertex_align(struct sna *sna, const struct sna_composite_op *op)
{
    int vertex_index;

    assert(op->floats_per_vertex);
    assert(op->floats_per_rect == 3 * op->floats_per_vertex);
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    vertex_index = (sna->render.vertex_used + op->floats_per_vertex - 1) /
                   op->floats_per_vertex;
    if ((int)sna->render.vertex_size - vertex_index * op->floats_per_vertex <
        2 * op->floats_per_rect)
    {
        DBG(("%s: flushing vertex buffer: new index=%d, max=%d\n",
             __FUNCTION__,
             vertex_index,
             sna->render.vertex_size / op->floats_per_vertex));
        if (gen4_vertex_finish(sna) < 2 * op->floats_per_rect)
        {
            kgem_submit(&sna->kgem);
            _kgem_set_mode(&sna->kgem, KGEM_RENDER);
        }
        assert(sna->render.vertex_used < sna->render.vertex_size);

        vertex_index = (sna->render.vertex_used + op->floats_per_vertex - 1) /
                       op->floats_per_vertex;
        assert(vertex_index * op->floats_per_vertex <= sna->render.vertex_size);
    }

    sna->render.vertex_index = vertex_index;
    sna->render.vertex_used  = vertex_index * op->floats_per_vertex;
}

void
gen4_vertex_flush(struct sna *sna)
{
    DBG(("%s[%x] = %d\n",
         __FUNCTION__,
         4 * sna->render.vertex_offset,
         sna->render.vertex_index - sna->render.vertex_start));

    assert(sna->render.vertex_offset);
    assert(sna->render.vertex_offset <= sna->kgem.nbatch);
    assert(sna->render.vertex_index > sna->render.vertex_start);
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    sna->kgem.batch[sna->render.vertex_offset] =
        sna->render.vertex_index - sna->render.vertex_start;
    sna->render.vertex_offset = 0;
}

int
gen4_vertex_finish(struct sna *sna)
{
    struct kgem_bo *bo;
    unsigned int    i;
    unsigned        hint, size;

    DBG(("%s: used=%d / %d\n",
         __FUNCTION__,
         sna->render.vertex_used,
         sna->render.vertex_size));
    assert(sna->render.vertex_offset == 0);
    assert(sna->render.vertex_used);
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    sna_vertex_wait__locked(&sna->render);

    /* Note: we only need dword alignment (currently) */

    hint = CREATE_GTT_MAP;

    bo = sna->render.vbo;
    if (bo)
    {
        for (i = 0; i < sna->render.nvertex_reloc; i++)
        {
            DBG(("%s: reloc[%d] = %d\n",
                 __FUNCTION__,
                 i,
                 sna->render.vertex_reloc[i]));

            sna->kgem.batch[sna->render.vertex_reloc[i]] =
                kgem_add_reloc(&sna->kgem,
                               sna->render.vertex_reloc[i],
                               bo,
                               I915_GEM_DOMAIN_VERTEX << 16,
                               0);
        }

        assert(!sna->render.active);
        sna->render.nvertex_reloc = 0;
        sna->render.vertex_used   = 0;
        sna->render.vertex_index  = 0;
        sna->render.vbo           = NULL;
        sna->render.vb_id         = 0;

        kgem_bo_destroy(&sna->kgem, bo);
        hint |= CREATE_CACHED | CREATE_NO_THROTTLE;
    }
    else
    {
        assert(sna->render.vertex_size == ARRAY_SIZE(sna->render.vertex_data));
        assert(sna->render.vertices == sna->render.vertex_data);
        if (kgem_is_idle(&sna->kgem)) return 0;
    }

    size = 256 * 1024;
    assert(!sna->render.active);
    sna->render.vertices = NULL;
    sna->render.vbo      = kgem_create_linear(&sna->kgem, size, hint);
    while (sna->render.vbo == NULL && size > sizeof(sna->render.vertex_data))
    {
        size /= 2;
        sna->render.vbo = kgem_create_linear(&sna->kgem, size, hint);
    }
    if (sna->render.vbo == NULL)
        sna->render.vbo =
            kgem_create_linear(&sna->kgem, 256 * 1024, CREATE_GTT_MAP);
    if (sna->render.vbo && kgem_check_bo(&sna->kgem, sna->render.vbo, NULL))
        sna->render.vertices = kgem_bo_map(&sna->kgem, sna->render.vbo);
    if (sna->render.vertices == NULL)
    {
        if (sna->render.vbo)
        {
            kgem_bo_destroy(&sna->kgem, sna->render.vbo);
            sna->render.vbo = NULL;
        }
        sna->render.vertices    = sna->render.vertex_data;
        sna->render.vertex_size = ARRAY_SIZE(sna->render.vertex_data);
        return 0;
    }

    if (sna->render.vertex_used)
    {
        DBG(("%s: copying initial buffer x %d to handle=%d\n",
             __FUNCTION__,
             sna->render.vertex_used,
             sna->render.vbo->handle));
        assert(sizeof(float) * sna->render.vertex_used <=
               __kgem_bo_size(sna->render.vbo));
        memcpy(sna->render.vertices,
               sna->render.vertex_data,
               sizeof(float) * sna->render.vertex_used);
    }

    size = __kgem_bo_size(sna->render.vbo) / 4;
    if (size >= UINT16_MAX) size = UINT16_MAX - 1;

    DBG(("%s: create vbo handle=%d, size=%d floats [%d bytes]\n",
         __FUNCTION__,
         sna->render.vbo->handle,
         size,
         __kgem_bo_size(sna->render.vbo)));
    assert(size > sna->render.vertex_used);

    sna->render.vertex_size = size;
    return size - sna->render.vertex_used;
}

void
gen4_vertex_close(struct sna *sna)
{
    struct kgem_bo *bo, *free_bo = NULL;
    unsigned int    i, delta     = 0;

    assert(sna->render.vertex_offset == 0);
    if (!sna->render.vb_id) return;

    DBG(("%s: used=%d, vbo active? %d, vb=%x, nreloc=%d\n",
         __FUNCTION__,
         sna->render.vertex_used,
         sna->render.vbo ? sna->render.vbo->handle : 0,
         sna->render.vb_id,
         sna->render.nvertex_reloc));

    assert(!sna->render.active);

    bo = sna->render.vbo;
    if (bo)
    {
        if (sna->render.vertex_size - sna->render.vertex_used < 64)
        {
            DBG(("%s: discarding vbo (full), handle=%d\n",
                 __FUNCTION__,
                 sna->render.vbo->handle));
            sna->render.vbo         = NULL;
            sna->render.vertices    = sna->render.vertex_data;
            sna->render.vertex_size = ARRAY_SIZE(sna->render.vertex_data);
            free_bo                 = bo;
        }
        else if (!sna->kgem.has_llc &&
                 sna->render.vertices == MAP(bo->map__cpu))
        {
            DBG(("%s: converting CPU map to GTT\n", __FUNCTION__));
            sna->render.vertices =
                kgem_bo_map__gtt(&sna->kgem, sna->render.vbo);
            if (sna->render.vertices == NULL)
            {
                sna->render.vbo         = NULL;
                sna->render.vertices    = sna->render.vertex_data;
                sna->render.vertex_size = ARRAY_SIZE(sna->render.vertex_data);
                free_bo                 = bo;
            }
        }
    }
    else
    {
        int size;

        size = sna->kgem.nbatch;
        size += sna->kgem.batch_size - sna->kgem.surface;
        size += sna->render.vertex_used;

        if (size <= 1024)
        {
            DBG(("%s: copy to batch: %d @ %d\n",
                 __FUNCTION__,
                 sna->render.vertex_used,
                 sna->kgem.nbatch));
            assert(sna->kgem.nbatch + sna->render.vertex_used <=
                   sna->kgem.surface);
            memcpy(sna->kgem.batch + sna->kgem.nbatch,
                   sna->render.vertex_data,
                   sna->render.vertex_used * 4);
            delta = sna->kgem.nbatch * 4;
            bo    = NULL;
            sna->kgem.nbatch += sna->render.vertex_used;
        }
        else
        {
            size = 256 * 1024;
            do
            {
                bo = kgem_create_linear(&sna->kgem,
                                        size,
                                        CREATE_GTT_MAP | CREATE_NO_RETIRE |
                                            CREATE_NO_THROTTLE | CREATE_CACHED);
            }
            while (bo == NULL &&
                   (size >>= 1) > sizeof(float) * sna->render.vertex_used);

            sna->render.vertices = NULL;
            if (bo) sna->render.vertices = kgem_bo_map(&sna->kgem, bo);
            if (sna->render.vertices != NULL)
            {
                DBG(("%s: new vbo: %d / %d\n",
                     __FUNCTION__,
                     sna->render.vertex_used,
                     __kgem_bo_size(bo) / 4));

                assert(sizeof(float) * sna->render.vertex_used <=
                       __kgem_bo_size(bo));
                memcpy(sna->render.vertices,
                       sna->render.vertex_data,
                       sizeof(float) * sna->render.vertex_used);

                size = __kgem_bo_size(bo) / 4;
                if (size >= UINT16_MAX) size = UINT16_MAX - 1;

                sna->render.vbo         = bo;
                sna->render.vertex_size = size;
            }
            else
            {
                DBG(("%s: tmp vbo: %d\n",
                     __FUNCTION__,
                     sna->render.vertex_used));

                if (bo) kgem_bo_destroy(&sna->kgem, bo);

                bo = kgem_create_linear(&sna->kgem,
                                        4 * sna->render.vertex_used,
                                        CREATE_NO_THROTTLE);
                if (bo && !kgem_bo_write(&sna->kgem,
                                         bo,
                                         sna->render.vertex_data,
                                         4 * sna->render.vertex_used))
                {
                    kgem_bo_destroy(&sna->kgem, bo);
                    bo = NULL;
                }

                assert(sna->render.vbo == NULL);
                sna->render.vertices    = sna->render.vertex_data;
                sna->render.vertex_size = ARRAY_SIZE(sna->render.vertex_data);
                free_bo                 = bo;
            }
        }
    }

    assert(sna->render.nvertex_reloc);
    for (i = 0; i < sna->render.nvertex_reloc; i++)
    {
        DBG(("%s: reloc[%d] = %d\n",
             __FUNCTION__,
             i,
             sna->render.vertex_reloc[i]));

        sna->kgem.batch[sna->render.vertex_reloc[i]] =
            kgem_add_reloc(&sna->kgem,
                           sna->render.vertex_reloc[i],
                           bo,
                           I915_GEM_DOMAIN_VERTEX << 16,
                           delta);
    }
    sna->render.nvertex_reloc = 0;
    sna->render.vb_id         = 0;

    if (sna->render.vbo == NULL)
    {
        assert(!sna->render.active);
        sna->render.vertex_used  = 0;
        sna->render.vertex_index = 0;
        assert(sna->render.vertices == sna->render.vertex_data);
        assert(sna->render.vertex_size == ARRAY_SIZE(sna->render.vertex_data));
    }

    if (free_bo) kgem_bo_destroy(&sna->kgem, free_bo);
}

/* specialised vertex emission routines */

#define OUT_VERTEX(x, y) \
    vertex_emit_2s(sna, x, y) /* XXX assert(!too_large(x, y)); */
#define OUT_VERTEX_F(v) vertex_emit(sna, v)

force_inline static float
compute_linear(const struct sna_composite_channel *channel,
               int16_t                             x,
               int16_t                             y)
{
    return ((x + channel->offset[0]) * channel->u.linear.dx +
            (y + channel->offset[1]) * channel->u.linear.dy +
            channel->u.linear.offset);
}

static inline sse2 void
emit_texcoord(struct sna                         *sna,
              const struct sna_composite_channel *channel,
              int16_t                             x,
              int16_t                             y)
{
    if (channel->is_solid)
    {
        OUT_VERTEX_F(0.5);
        return;
    }

    x += channel->offset[0];
    y += channel->offset[1];

    if (channel->is_affine)
    {
        float s, t;

        sna_get_transformed_coordinates(x, y, channel->transform, &s, &t);
        OUT_VERTEX_F(s * channel->scale[0]);
        OUT_VERTEX_F(t * channel->scale[1]);
    }
    else
    {
        float s, t, w;

        sna_get_transformed_coordinates_3d(x,
                                           y,
                                           channel->transform,
                                           &s,
                                           &t,
                                           &w);
        OUT_VERTEX_F(s * channel->scale[0]);
        OUT_VERTEX_F(t * channel->scale[1]);
        OUT_VERTEX_F(w);
    }
}

sse2 static force_inline void
emit_vertex(struct sna                    *sna,
            const struct sna_composite_op *op,
            int16_t                        srcX,
            int16_t                        srcY,
            int16_t                        mskX,
            int16_t                        mskY,
            int16_t                        dstX,
            int16_t                        dstY)
{
    OUT_VERTEX(dstX, dstY);
    emit_texcoord(sna, &op->src, srcX, srcY);
}

sse2 static fastcall void
emit_primitive(struct sna                            *sna,
               const struct sna_composite_op         *op,
               const struct sna_composite_rectangles *r)
{
    emit_vertex(sna,
                op,
                r->src.x + r->width,
                r->src.y + r->height,
                r->mask.x + r->width,
                r->mask.y + r->height,
                r->dst.x + r->width,
                r->dst.y + r->height);
    emit_vertex(sna,
                op,
                r->src.x,
                r->src.y + r->height,
                r->mask.x,
                r->mask.y + r->height,
                r->dst.x,
                r->dst.y + r->height);
    emit_vertex(sna,
                op,
                r->src.x,
                r->src.y,
                r->mask.x,
                r->mask.y,
                r->dst.x,
                r->dst.y);
}

static inline sse2 float *
vemit_texcoord(float                              *v,
               const struct sna_composite_channel *channel,
               int16_t                             x,
               int16_t                             y)
{
    if (channel->is_solid)
    {
        *v++ = 0.5;
    }
    else
    {
        x += channel->offset[0];
        y += channel->offset[1];

        if (channel->is_affine)
        {
            float s, t;

            sna_get_transformed_coordinates(x, y, channel->transform, &s, &t);
            *v++ = s * channel->scale[0];
            *v++ = t * channel->scale[1];
        }
        else
        {
            float s, t, w;

            sna_get_transformed_coordinates_3d(x,
                                               y,
                                               channel->transform,
                                               &s,
                                               &t,
                                               &w);
            *v++ = s * channel->scale[0];
            *v++ = t * channel->scale[1];
            *v++ = w;
        }
    }

    return v;
}

sse2 static force_inline float *
vemit_vertex(float *v, const struct sna_composite_op *op, int16_t x, int16_t y)
{
    *v++ = pack_2s(x, y);
    return vemit_texcoord(v, &op->src, x, y);
}

sse2 static fastcall void
emit_boxes(const struct sna_composite_op *op,
           const BoxRec                  *box,
           int                            nbox,
           float                         *v)
{
    do
    {
        v = vemit_vertex(v, op, box->x2, box->y2);
        v = vemit_vertex(v, op, box->x1, box->y2);
        v = vemit_vertex(v, op, box->x1, box->y1);

        box++;
    }
    while (--nbox);
}

sse2 static force_inline void
emit_vertex_mask(struct sna                    *sna,
                 const struct sna_composite_op *op,
                 int16_t                        srcX,
                 int16_t                        srcY,
                 int16_t                        mskX,
                 int16_t                        mskY,
                 int16_t                        dstX,
                 int16_t                        dstY)
{
    OUT_VERTEX(dstX, dstY);
    emit_texcoord(sna, &op->src, srcX, srcY);
    emit_texcoord(sna, &op->mask, mskX, mskY);
}

sse2 static fastcall void
emit_primitive_mask(struct sna                            *sna,
                    const struct sna_composite_op         *op,
                    const struct sna_composite_rectangles *r)
{
    emit_vertex_mask(sna,
                     op,
                     r->src.x + r->width,
                     r->src.y + r->height,
                     r->mask.x + r->width,
                     r->mask.y + r->height,
                     r->dst.x + r->width,
                     r->dst.y + r->height);
    emit_vertex_mask(sna,
                     op,
                     r->src.x,
                     r->src.y + r->height,
                     r->mask.x,
                     r->mask.y + r->height,
                     r->dst.x,
                     r->dst.y + r->height);
    emit_vertex_mask(sna,
                     op,
                     r->src.x,
                     r->src.y,
                     r->mask.x,
                     r->mask.y,
                     r->dst.x,
                     r->dst.y);
}

sse2 static force_inline float *
vemit_vertex_mask(float                         *v,
                  const struct sna_composite_op *op,
                  int16_t                        x,
                  int16_t                        y)
{
    *v++ = pack_2s(x, y);
    v    = vemit_texcoord(v, &op->src, x, y);
    v    = vemit_texcoord(v, &op->mask, x, y);
    return v;
}

sse2 static fastcall void
emit_boxes_mask(const struct sna_composite_op *op,
                const BoxRec                  *box,
                int                            nbox,
                float                         *v)
{
    do
    {
        v = vemit_vertex_mask(v, op, box->x2, box->y2);
        v = vemit_vertex_mask(v, op, box->x1, box->y2);
        v = vemit_vertex_mask(v, op, box->x1, box->y1);

        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_solid(struct sna                            *sna,
                     const struct sna_composite_op         *op,
                     const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    assert(op->floats_per_rect == 6);
    assert((sna->render.vertex_used % 2) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 6;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[2]    = dst.f;
    dst.p.y = r->dst.y;
    v[4]    = dst.f;

    v[5] = v[3] = v[1] = .5;
}

sse2 static fastcall void
emit_boxes_solid(const struct sna_composite_op *op,
                 const BoxRec                  *box,
                 int                            nbox,
                 float                         *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[2]    = dst.f;
        dst.p.y = box->y1;
        v[4]    = dst.f;

        v[5] = v[3] = v[1] = .5;
        box++;
        v += 6;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_linear(struct sna                            *sna,
                      const struct sna_composite_op         *op,
                      const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    assert(op->floats_per_rect == 6);
    assert((sna->render.vertex_used % 2) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 6;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[2]    = dst.f;
    dst.p.y = r->dst.y;
    v[4]    = dst.f;

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[3] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y);
}

sse2 static fastcall void
emit_boxes_linear(const struct sna_composite_op *op,
                  const BoxRec                  *box,
                  int                            nbox,
                  float                         *v)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    do
    {
        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[2]    = dst.f;
        dst.p.y = box->y1;
        v[4]    = dst.f;

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[3] = compute_linear(&op->src, box->x1, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y1);

        v += 6;
        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_identity_source(struct sna                            *sna,
                               const struct sna_composite_op         *op,
                               const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    dst.p.y = r->dst.y;
    v[6]    = dst.f;

    v[7] = v[4] = (r->src.x + op->src.offset[0]) * op->src.scale[0];
    v[1]        = v[4] + r->width * op->src.scale[0];

    v[8] = (r->src.y + op->src.offset[1]) * op->src.scale[1];
    v[5] = v[2] = v[8] + r->height * op->src.scale[1];
}

sse2 static fastcall void
emit_boxes_identity_source(const struct sna_composite_op *op,
                           const BoxRec                  *box,
                           int                            nbox,
                           float                         *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[3]    = dst.f;
        dst.p.y = box->y1;
        v[6]    = dst.f;

        v[7] = v[4] = (box->x1 + op->src.offset[0]) * op->src.scale[0];
        v[1]        = (box->x2 + op->src.offset[0]) * op->src.scale[0];

        v[8] = (box->y1 + op->src.offset[1]) * op->src.scale[1];
        v[2] = v[5] = (box->y2 + op->src.offset[1]) * op->src.scale[1];

        v += 9;
        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_simple_source(struct sna                            *sna,
                             const struct sna_composite_op         *op,
                             const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 3;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[1]    = ((r->src.x + r->width + tx) * xx + x0) * sx;
    v[5] = v[2] = ((r->src.y + r->height + ty) * yy + y0) * sy;

    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    v[7] = v[4] = ((r->src.x + tx) * xx + x0) * sx;

    dst.p.y = r->dst.y;
    v[6]    = dst.f;
    v[8]    = ((r->src.y + ty) * yy + y0) * sy;
}

sse2 static fastcall void
emit_boxes_simple_source(const struct sna_composite_op *op,
                         const BoxRec                  *box,
                         int                            nbox,
                         float                         *v)
{
    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[1]    = ((box->x2 + tx) * xx + x0) * sx;
        v[5] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

        dst.p.x = box->x1;
        v[3]    = dst.f;
        v[7] = v[4] = ((box->x1 + tx) * xx + x0) * sx;

        dst.p.y = box->y1;
        v[6]    = dst.f;
        v[8]    = ((box->y1 + ty) * yy + y0) * sy;

        v += 9;
        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_affine_source(struct sna                            *sna,
                             const struct sna_composite_op         *op,
                             const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x + r->width,
                                op->src.offset[1] + r->src.y + r->height,
                                op->src.transform,
                                op->src.scale,
                                &v[1],
                                &v[2]);

    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x,
                                op->src.offset[1] + r->src.y + r->height,
                                op->src.transform,
                                op->src.scale,
                                &v[4],
                                &v[5]);

    dst.p.y = r->dst.y;
    v[6]    = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x,
                                op->src.offset[1] + r->src.y,
                                op->src.transform,
                                op->src.scale,
                                &v[7],
                                &v[8]);
}

sse2 static fastcall void
emit_boxes_affine_source(const struct sna_composite_op *op,
                         const BoxRec                  *box,
                         int                            nbox,
                         float                         *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        _sna_get_transformed_scaled(op->src.offset[0] + box->x2,
                                    op->src.offset[1] + box->y2,
                                    op->src.transform,
                                    op->src.scale,
                                    &v[1],
                                    &v[2]);

        dst.p.x = box->x1;
        v[3]    = dst.f;
        _sna_get_transformed_scaled(op->src.offset[0] + box->x1,
                                    op->src.offset[1] + box->y2,
                                    op->src.transform,
                                    op->src.scale,
                                    &v[4],
                                    &v[5]);

        dst.p.y = box->y1;
        v[6]    = dst.f;
        _sna_get_transformed_scaled(op->src.offset[0] + box->x1,
                                    op->src.offset[1] + box->y1,
                                    op->src.transform,
                                    op->src.scale,
                                    &v[7],
                                    &v[8]);
        box++;
        v += 9;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_identity_mask(struct sna                            *sna,
                             const struct sna_composite_op         *op,
                             const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[9] = v[5] = v[1] = .5;
}

sse2 static fastcall void
emit_boxes_identity_mask(const struct sna_composite_op *op,
                         const BoxRec                  *box,
                         int                            nbox,
                         float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[9] = v[5] = v[1] = .5;
        v += 12;
        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_linear_identity_mask(struct sna                            *sna,
                                    const struct sna_composite_op         *op,
                                    const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[9] = compute_linear(&op->src, r->src.x, r->src.y);
}

sse2 static fastcall void
emit_boxes_linear_identity_mask(const struct sna_composite_op *op,
                                const BoxRec                  *box,
                                int                            nbox,
                                float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y2);
        v[9] = compute_linear(&op->src, box->x1, box->y1);

        v += 12;
        box++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_primitive_identity_source_mask(struct sna                            *sna,
                                    const struct sna_composite_op         *op,
                                    const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  src_x, src_y;
    float  msk_x, msk_y;
    float  w, h;
    float *v;

    src_x = r->src.x + op->src.offset[0];
    src_y = r->src.y + op->src.offset[1];
    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    assert(op->floats_per_rect == 15);
    assert((sna->render.vertex_used % 5) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 15;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[1]    = (src_x + w) * op->src.scale[0];
    v[2]    = (src_y + h) * op->src.scale[1];
    v[3]    = (msk_x + w) * op->mask.scale[0];
    v[4]    = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[5]    = dst.f;
    v[6]    = src_x * op->src.scale[0];
    v[7]    = v[2];
    v[8]    = msk_x * op->mask.scale[0];
    v[9]    = v[4];

    dst.p.y = r->dst.y;
    v[10]   = dst.f;
    v[11]   = v[6];
    v[12]   = src_y * op->src.scale[1];
    v[13]   = v[8];
    v[14]   = msk_y * op->mask.scale[1];
}

sse2 static fastcall void
emit_primitive_simple_source_identity(struct sna                    *sna,
                                      const struct sna_composite_op *op,
                                      const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx    = op->src.transform->matrix[0][0];
    float   x0    = op->src.transform->matrix[0][2];
    float   yy    = op->src.transform->matrix[1][1];
    float   y0    = op->src.transform->matrix[1][2];
    float   sx    = op->src.scale[0];
    float   sy    = op->src.scale[1];
    int16_t tx    = op->src.offset[0];
    int16_t ty    = op->src.offset[1];
    float   msk_x = r->mask.x + op->mask.offset[0];
    float   msk_y = r->mask.y + op->mask.offset[1];
    float   w = r->width, h = r->height;

    assert(op->floats_per_rect == 15);
    assert((sna->render.vertex_used % 5) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 5;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[1]    = ((r->src.x + r->width + tx) * xx + x0) * sx;
    v[2]    = ((r->src.y + r->height + ty) * yy + y0) * sy;
    v[3]    = (msk_x + w) * op->mask.scale[0];
    v[4]    = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[5]    = dst.f;
    v[6]    = ((r->src.x + tx) * xx + x0) * sx;
    v[7]    = v[2];
    v[8]    = msk_x * op->mask.scale[0];
    v[9]    = v[4];

    dst.p.y = r->dst.y;
    v[10]   = dst.f;
    v[11]   = v[6];
    v[12]   = ((r->src.y + ty) * yy + y0) * sy;
    v[13]   = v[8];
    v[14]   = msk_y * op->mask.scale[1];
}

sse2 static fastcall void
emit_primitive_affine_source_identity(struct sna                    *sna,
                                      const struct sna_composite_op *op,
                                      const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float msk_x = r->mask.x + op->mask.offset[0];
    float msk_y = r->mask.y + op->mask.offset[1];
    float w = r->width, h = r->height;

    assert(op->floats_per_rect == 15);
    assert((sna->render.vertex_used % 5) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 5;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x + r->width,
                                op->src.offset[1] + r->src.y + r->height,
                                op->src.transform,
                                op->src.scale,
                                &v[1],
                                &v[2]);
    v[3] = (msk_x + w) * op->mask.scale[0];
    v[4] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[5]    = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x,
                                op->src.offset[1] + r->src.y + r->height,
                                op->src.transform,
                                op->src.scale,
                                &v[6],
                                &v[7]);
    v[8] = msk_x * op->mask.scale[0];
    v[9] = v[4];

    dst.p.y = r->dst.y;
    v[10]   = dst.f;
    _sna_get_transformed_scaled(op->src.offset[0] + r->src.x,
                                op->src.offset[1] + r->src.y,
                                op->src.transform,
                                op->src.scale,
                                &v[11],
                                &v[12]);
    v[13] = v[8];
    v[14] = msk_y * op->mask.scale[1];
}

/* SSE4_2 */
#if defined(sse4_2)

sse4_2 fastcall static void
emit_primitive_linear__sse4_2(struct sna                            *sna,
                              const struct sna_composite_op         *op,
                              const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    assert(op->floats_per_rect == 6);
    assert((sna->render.vertex_used % 2) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 6;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[2]    = dst.f;
    dst.p.y = r->dst.y;
    v[4]    = dst.f;

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[3] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y);
}

sse4_2 static fastcall void
emit_boxes_linear__sse4_2(const struct sna_composite_op *op,
                          const BoxRec                  *box,
                          int                            nbox,
                          float                         *v)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    do
    {
        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[2]    = dst.f;
        dst.p.y = box->y1;
        v[4]    = dst.f;

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[3] = compute_linear(&op->src, box->x1, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y1);

        v += 6;
        box++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_primitive_identity_source__sse4_2(struct sna                    *sna,
                                       const struct sna_composite_op *op,
                                       const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    dst.p.y = r->dst.y;
    v[6]    = dst.f;

    v[7] = v[4] = (r->src.x + op->src.offset[0]) * op->src.scale[0];
    v[1]        = v[4] + r->width * op->src.scale[0];

    v[8] = (r->src.y + op->src.offset[1]) * op->src.scale[1];
    v[5] = v[2] = v[8] + r->height * op->src.scale[1];
}

sse4_2 static fastcall void
emit_boxes_identity_source__sse4_2(const struct sna_composite_op *op,
                                   const BoxRec                  *box,
                                   int                            nbox,
                                   float                         *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[3]    = dst.f;
        dst.p.y = box->y1;
        v[6]    = dst.f;

        v[7] = v[4] = (box->x1 + op->src.offset[0]) * op->src.scale[0];
        v[1]        = (box->x2 + op->src.offset[0]) * op->src.scale[0];

        v[8] = (box->y1 + op->src.offset[1]) * op->src.scale[1];
        v[2] = v[5] = (box->y2 + op->src.offset[1]) * op->src.scale[1];

        v += 9;
        box++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_primitive_simple_source__sse4_2(struct sna                            *sna,
                                     const struct sna_composite_op         *op,
                                     const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 3;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[1]    = ((r->src.x + r->width + tx) * xx + x0) * sx;
    v[5] = v[2] = ((r->src.y + r->height + ty) * yy + y0) * sy;

    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    v[7] = v[4] = ((r->src.x + tx) * xx + x0) * sx;

    dst.p.y = r->dst.y;
    v[6]    = dst.f;
    v[8]    = ((r->src.y + ty) * yy + y0) * sy;
}

sse4_2 static fastcall void
emit_boxes_simple_source__sse4_2(const struct sna_composite_op *op,
                                 const BoxRec                  *box,
                                 int                            nbox,
                                 float                         *v)
{
    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[1]    = ((box->x2 + tx) * xx + x0) * sx;
        v[5] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

        dst.p.x = box->x1;
        v[3]    = dst.f;
        v[7] = v[4] = ((box->x1 + tx) * xx + x0) * sx;

        dst.p.y = box->y1;
        v[6]    = dst.f;
        v[8]    = ((box->y1 + ty) * yy + y0) * sy;

        v += 9;
        box++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_primitive_identity_mask__sse4_2(struct sna                            *sna,
                                     const struct sna_composite_op         *op,
                                     const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[9] = v[5] = v[1] = .5;
}

sse4_2 static fastcall void
emit_boxes_identity_mask__sse4_2(const struct sna_composite_op *op,
                                 const BoxRec                  *box,
                                 int                            nbox,
                                 float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[9] = v[5] = v[1] = .5;
        v += 12;
        box++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_primitive_linear_identity_mask__sse4_2(
    struct sna                            *sna,
    const struct sna_composite_op         *op,
    const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[9] = compute_linear(&op->src, r->src.x, r->src.y);
}

sse4_2 static fastcall void
emit_boxes_linear_identity_mask__sse4_2(const struct sna_composite_op *op,
                                        const BoxRec                  *box,
                                        int                            nbox,
                                        float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y2);
        v[9] = compute_linear(&op->src, box->x1, box->y1);

        v += 12;
        box++;
    }
    while (--nbox);
}

#endif

/* AVX2 */
#if defined(avx2)

avx2 fastcall static void
emit_primitive_linear__avx2(struct sna                            *sna,
                            const struct sna_composite_op         *op,
                            const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    assert(op->floats_per_rect == 6);
    assert((sna->render.vertex_used % 2) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 6;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[2]    = dst.f;
    dst.p.y = r->dst.y;
    v[4]    = dst.f;

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[3] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y);
}

avx2 static fastcall void
emit_boxes_linear__avx2(const struct sna_composite_op *op,
                        const BoxRec                  *box,
                        int                            nbox,
                        float                         *v)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    do
    {
        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[2]    = dst.f;
        dst.p.y = box->y1;
        v[4]    = dst.f;

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[3] = compute_linear(&op->src, box->x1, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y1);

        v += 6;
        box++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_primitive_identity_source__avx2(struct sna                            *sna,
                                     const struct sna_composite_op         *op,
                                     const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    dst.p.y = r->dst.y;
    v[6]    = dst.f;

    v[7] = v[4] = (r->src.x + op->src.offset[0]) * op->src.scale[0];
    v[1]        = v[4] + r->width * op->src.scale[0];

    v[8] = (r->src.y + op->src.offset[1]) * op->src.scale[1];
    v[5] = v[2] = v[8] + r->height * op->src.scale[1];
}

avx2 static fastcall void
emit_boxes_identity_source__avx2(const struct sna_composite_op *op,
                                 const BoxRec                  *box,
                                 int                            nbox,
                                 float                         *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        dst.p.x = box->x1;
        v[3]    = dst.f;
        dst.p.y = box->y1;
        v[6]    = dst.f;

        v[7] = v[4] = (box->x1 + op->src.offset[0]) * op->src.scale[0];
        v[1]        = (box->x2 + op->src.offset[0]) * op->src.scale[0];

        v[8] = (box->y1 + op->src.offset[1]) * op->src.scale[1];
        v[2] = v[5] = (box->y2 + op->src.offset[1]) * op->src.scale[1];

        v += 9;
        box++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_primitive_simple_source__avx2(struct sna                            *sna,
                                   const struct sna_composite_op         *op,
                                   const struct sna_composite_rectangles *r)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    assert(op->floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 3;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[1]    = ((r->src.x + r->width + tx) * xx + x0) * sx;
    v[5] = v[2] = ((r->src.y + r->height + ty) * yy + y0) * sy;

    dst.p.x = r->dst.x;
    v[3]    = dst.f;
    v[7] = v[4] = ((r->src.x + tx) * xx + x0) * sx;

    dst.p.y = r->dst.y;
    v[6]    = dst.f;
    v[8]    = ((r->src.y + ty) * yy + y0) * sy;
}

avx2 static fastcall void
emit_boxes_simple_source__avx2(const struct sna_composite_op *op,
                               const BoxRec                  *box,
                               int                            nbox,
                               float                         *v)
{
    float   xx = op->src.transform->matrix[0][0];
    float   x0 = op->src.transform->matrix[0][2];
    float   yy = op->src.transform->matrix[1][1];
    float   y0 = op->src.transform->matrix[1][2];
    float   sx = op->src.scale[0];
    float   sy = op->src.scale[1];
    int16_t tx = op->src.offset[0];
    int16_t ty = op->src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[1]    = ((box->x2 + tx) * xx + x0) * sx;
        v[5] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

        dst.p.x = box->x1;
        v[3]    = dst.f;
        v[7] = v[4] = ((box->x1 + tx) * xx + x0) * sx;

        dst.p.y = box->y1;
        v[6]    = dst.f;
        v[8]    = ((box->y1 + ty) * yy + y0) * sy;

        v += 9;
        box++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_primitive_identity_mask__avx2(struct sna                            *sna,
                                   const struct sna_composite_op         *op,
                                   const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[9] = v[5] = v[1] = .5;
}

avx2 static fastcall void
emit_boxes_identity_mask__avx2(const struct sna_composite_op *op,
                               const BoxRec                  *box,
                               int                            nbox,
                               float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[9] = v[5] = v[1] = .5;
        v += 12;
        box++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_primitive_linear_identity_mask__avx2(
    struct sna                            *sna,
    const struct sna_composite_op         *op,
    const struct sna_composite_rectangles *r)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float  msk_x, msk_y;
    float  w, h;
    float *v;

    msk_x = r->mask.x + op->mask.offset[0];
    msk_y = r->mask.y + op->mask.offset[1];
    w     = r->width;
    h     = r->height;

    DBG(("%s: dst=(%d, %d), mask=(%f, %f) x (%f, %f)\n",
         __FUNCTION__,
         r->dst.x,
         r->dst.y,
         msk_x,
         msk_y,
         w,
         h));

    assert(op->floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = r->dst.x + r->width;
    dst.p.y = r->dst.y + r->height;
    v[0]    = dst.f;
    v[2]    = (msk_x + w) * op->mask.scale[0];
    v[7] = v[3] = (msk_y + h) * op->mask.scale[1];

    dst.p.x = r->dst.x;
    v[4]    = dst.f;
    v[10] = v[6] = msk_x * op->mask.scale[0];

    dst.p.y = r->dst.y;
    v[8]    = dst.f;
    v[11]   = msk_y * op->mask.scale[1];

    v[1] = compute_linear(&op->src, r->src.x + r->width, r->src.y + r->height);
    v[5] = compute_linear(&op->src, r->src.x, r->src.y + r->height);
    v[9] = compute_linear(&op->src, r->src.x, r->src.y);
}

avx2 static fastcall void
emit_boxes_linear_identity_mask__avx2(const struct sna_composite_op *op,
                                      const BoxRec                  *box,
                                      int                            nbox,
                                      float                         *v)
{
    float msk_x = op->mask.offset[0];
    float msk_y = op->mask.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = box->x2;
        dst.p.y = box->y2;
        v[0]    = dst.f;
        v[2]    = (msk_x + box->x2) * op->mask.scale[0];
        v[7] = v[3] = (msk_y + box->y2) * op->mask.scale[1];

        dst.p.x = box->x1;
        v[4]    = dst.f;
        v[10] = v[6] = (msk_x + box->x1) * op->mask.scale[0];

        dst.p.y = box->y1;
        v[8]    = dst.f;
        v[11]   = (msk_y + box->y1) * op->mask.scale[1];

        v[1] = compute_linear(&op->src, box->x2, box->y2);
        v[5] = compute_linear(&op->src, box->x1, box->y2);
        v[9] = compute_linear(&op->src, box->x1, box->y1);

        v += 12;
        box++;
    }
    while (--nbox);
}

#endif

unsigned
gen4_choose_composite_emitter(struct sna *sna, struct sna_composite_op *tmp)
{
    unsigned vb;

    if (tmp->mask.bo)
    {
        if (tmp->mask.transform == NULL)
        {
            if (tmp->src.is_solid)
            {
                DBG(("%s: solid, identity mask\n", __FUNCTION__));
#if defined(avx2)
                if (sna->cpu_features & AVX2)
                {
                    tmp->prim_emit  = emit_primitive_identity_mask__avx2;
                    tmp->emit_boxes = emit_boxes_identity_mask__avx2;
                }
                else
#endif
#if defined(sse4_2)
                    if (sna->cpu_features & SSE4_2)
                {
                    tmp->prim_emit  = emit_primitive_identity_mask__sse4_2;
                    tmp->emit_boxes = emit_boxes_identity_mask__sse4_2;
                }
                else
#endif
                {
                    tmp->prim_emit  = emit_primitive_identity_mask;
                    tmp->emit_boxes = emit_boxes_identity_mask;
                }
                tmp->floats_per_vertex = 4;
                vb                     = 1 | 2 << 2;
            }
            else if (tmp->src.is_linear)
            {
                DBG(("%s: linear, identity mask\n", __FUNCTION__));
#if defined(avx2)
                if (sna->cpu_features & AVX2)
                {
                    tmp->prim_emit  = emit_primitive_linear_identity_mask__avx2;
                    tmp->emit_boxes = emit_boxes_linear_identity_mask__avx2;
                }
                else
#endif
#if defined(sse4_2)
                    if (sna->cpu_features & SSE4_2)
                {
                    tmp->prim_emit =
                        emit_primitive_linear_identity_mask__sse4_2;
                    tmp->emit_boxes = emit_boxes_linear_identity_mask__sse4_2;
                }
                else
#endif
                {
                    tmp->prim_emit  = emit_primitive_linear_identity_mask;
                    tmp->emit_boxes = emit_boxes_linear_identity_mask;
                }
                tmp->floats_per_vertex = 4;
                vb                     = 1 | 2 << 2;
            }
            else if (tmp->src.transform == NULL)
            {
                DBG(("%s: identity source, identity mask\n", __FUNCTION__));
                tmp->prim_emit         = emit_primitive_identity_source_mask;
                tmp->floats_per_vertex = 5;
                vb                     = 2 << 2 | 2;
            }
            else if (tmp->src.is_affine)
            {
                tmp->src.scale[0] /= tmp->src.transform->matrix[2][2];
                tmp->src.scale[1] /= tmp->src.transform->matrix[2][2];
                if (!sna_affine_transform_is_rotation(tmp->src.transform))
                {
                    DBG(("%s: simple src, identity mask\n", __FUNCTION__));
                    tmp->prim_emit = emit_primitive_simple_source_identity;
                }
                else
                {
                    DBG(("%s: affine src, identity mask\n", __FUNCTION__));
                    tmp->prim_emit = emit_primitive_affine_source_identity;
                }
                tmp->floats_per_vertex = 5;
                vb                     = 2 << 2 | 2;
            }
            else
            {
                DBG(("%s: projective source, identity mask\n", __FUNCTION__));
                tmp->prim_emit         = emit_primitive_mask;
                tmp->floats_per_vertex = 6;
                vb                     = 2 << 2 | 3;
            }
        }
        else
        {
            tmp->prim_emit         = emit_primitive_mask;
            tmp->emit_boxes        = emit_boxes_mask;
            tmp->floats_per_vertex = 1;
            vb                     = 0;
            if (tmp->mask.is_solid)
            {
                tmp->floats_per_vertex += 1;
                vb |= 1 << 2;
            }
            else if (tmp->mask.is_affine)
            {
                tmp->floats_per_vertex += 2;
                vb |= 2 << 2;
            }
            else
            {
                tmp->floats_per_vertex += 3;
                vb |= 3 << 2;
            }
            if (tmp->src.is_solid)
            {
                tmp->floats_per_vertex += 1;
                vb |= 1;
            }
            else if (tmp->src.is_affine)
            {
                tmp->floats_per_vertex += 2;
                vb |= 2;
            }
            else
            {
                tmp->floats_per_vertex += 3;
                vb |= 3;
            }
            DBG(("%s: general mask: floats-per-vertex=%d, vb=%x\n",
                 __FUNCTION__,
                 tmp->floats_per_vertex,
                 vb));
        }
    }
    else
    {
        if (tmp->src.is_solid)
        {
            DBG(("%s: solid, no mask\n", __FUNCTION__));
            tmp->prim_emit  = emit_primitive_solid;
            tmp->emit_boxes = emit_boxes_solid;
            if (tmp->src.is_opaque && tmp->op == PictOpOver)
                tmp->op = PictOpSrc;
            tmp->floats_per_vertex = 2;
            vb                     = 1;
        }
        else if (tmp->src.is_linear)
        {
            DBG(("%s: linear, no mask\n", __FUNCTION__));
#if defined(avx2)
            if (sna->cpu_features & AVX2)
            {
                tmp->prim_emit  = emit_primitive_linear__avx2;
                tmp->emit_boxes = emit_boxes_linear__avx2;
            }
            else
#endif
#if defined(sse4_2)
                if (sna->cpu_features & SSE4_2)
            {
                tmp->prim_emit  = emit_primitive_linear__sse4_2;
                tmp->emit_boxes = emit_boxes_linear__sse4_2;
            }
            else
#endif
            {
                tmp->prim_emit  = emit_primitive_linear;
                tmp->emit_boxes = emit_boxes_linear;
            }
            tmp->floats_per_vertex = 2;
            vb                     = 1;
        }
        else if (tmp->src.transform == NULL)
        {
            DBG(("%s: identity src, no mask\n", __FUNCTION__));
#if defined(avx2)
            if (sna->cpu_features & AVX2)
            {
                tmp->prim_emit  = emit_primitive_identity_source__avx2;
                tmp->emit_boxes = emit_boxes_identity_source__avx2;
            }
            else
#endif
#if defined(sse4_2)
                if (sna->cpu_features & SSE4_2)
            {
                tmp->prim_emit  = emit_primitive_identity_source__sse4_2;
                tmp->emit_boxes = emit_boxes_identity_source__sse4_2;
            }
            else
#endif
            {
                tmp->prim_emit  = emit_primitive_identity_source;
                tmp->emit_boxes = emit_boxes_identity_source;
            }
            tmp->floats_per_vertex = 3;
            vb                     = 2;
        }
        else if (tmp->src.is_affine)
        {
            tmp->src.scale[0] /= tmp->src.transform->matrix[2][2];
            tmp->src.scale[1] /= tmp->src.transform->matrix[2][2];
            if (!sna_affine_transform_is_rotation(tmp->src.transform))
            {
                DBG(("%s: simple src, no mask\n", __FUNCTION__));
#if defined(avx2)
                if (sna->cpu_features & AVX2)
                {
                    tmp->prim_emit  = emit_primitive_simple_source__avx2;
                    tmp->emit_boxes = emit_boxes_simple_source__avx2;
                }
                else
#endif
#if defined(sse4_2)
                    if (sna->cpu_features & SSE4_2)
                {
                    tmp->prim_emit  = emit_primitive_simple_source__sse4_2;
                    tmp->emit_boxes = emit_boxes_simple_source__sse4_2;
                }
                else
#endif
                {
                    tmp->prim_emit  = emit_primitive_simple_source;
                    tmp->emit_boxes = emit_boxes_simple_source;
                }
            }
            else
            {
                DBG(("%s: affine src, no mask\n", __FUNCTION__));
                tmp->prim_emit  = emit_primitive_affine_source;
                tmp->emit_boxes = emit_boxes_affine_source;
            }
            tmp->floats_per_vertex = 3;
            vb                     = 2;
        }
        else
        {
            DBG(("%s: projective src, no mask\n", __FUNCTION__));
            assert(!tmp->src.is_solid);
            tmp->prim_emit         = emit_primitive;
            tmp->emit_boxes        = emit_boxes;
            tmp->floats_per_vertex = 4;
            vb                     = 3;
        }
    }
    tmp->floats_per_rect = 3 * tmp->floats_per_vertex;

    return vb;
}

sse2 static force_inline void
emit_span_vertex(struct sna                          *sna,
                 const struct sna_composite_spans_op *op,
                 int16_t                              x,
                 int16_t                              y)
{
    OUT_VERTEX(x, y);
    emit_texcoord(sna, &op->base.src, x, y);
}

sse2 static fastcall void
emit_span_primitive(struct sna                          *sna,
                    const struct sna_composite_spans_op *op,
                    const BoxRec                        *box,
                    float                                opacity)
{
    emit_span_vertex(sna, op, box->x2, box->y2);
    OUT_VERTEX_F(opacity);

    emit_span_vertex(sna, op, box->x1, box->y2);
    OUT_VERTEX_F(opacity);

    emit_span_vertex(sna, op, box->x1, box->y1);
    OUT_VERTEX_F(opacity);
}

sse2 static fastcall void
emit_span_boxes(const struct sna_composite_spans_op *op,
                const struct sna_opacity_box        *b,
                int                                  nbox,
                float                               *v)
{
    do
    {
        v    = vemit_vertex(v, &op->base, b->box.x2, b->box.y2);
        *v++ = b->alpha;

        v    = vemit_vertex(v, &op->base, b->box.x1, b->box.y2);
        *v++ = b->alpha;

        v    = vemit_vertex(v, &op->base, b->box.x1, b->box.y1);
        *v++ = b->alpha;

        b++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_span_solid(struct sna                          *sna,
                const struct sna_composite_spans_op *op,
                const BoxRec                        *box,
                float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    assert(op->base.floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 3;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;

    dst.p.x = box->x1;
    v[3]    = dst.f;

    dst.p.y = box->y1;
    v[6]    = dst.f;

    v[7] = v[4] = v[1] = .5;
    v[8] = v[5] = v[2] = opacity;
}

sse2 static fastcall void
emit_span_boxes_solid(const struct sna_composite_spans_op *op,
                      const struct sna_opacity_box        *b,
                      int                                  nbox,
                      float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;

        dst.p.x = b->box.x1;
        v[3]    = dst.f;

        dst.p.y = b->box.y1;
        v[6]    = dst.f;

        v[7] = v[4] = v[1] = .5;
        v[8] = v[5] = v[2] = b->alpha;

        v += 9;
        b++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_span_identity(struct sna                          *sna,
                   const struct sna_composite_spans_op *op,
                   const BoxRec                        *box,
                   float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = (box->x2 + tx) * sx;
    v[6] = v[2] = (box->y2 + ty) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = (box->x1 + tx) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = (box->y1 + ty) * sy;

    v[11] = v[7] = v[3] = opacity;
}

sse2 static fastcall void
emit_span_boxes_identity(const struct sna_composite_spans_op *op,
                         const struct sna_opacity_box        *b,
                         int                                  nbox,
                         float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        float   sx = op->base.src.scale[0];
        float   sy = op->base.src.scale[1];
        int16_t tx = op->base.src.offset[0];
        int16_t ty = op->base.src.offset[1];

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = (b->box.x2 + tx) * sx;
        v[6] = v[2] = (b->box.y2 + ty) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = (b->box.x1 + tx) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = (b->box.y1 + ty) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_span_simple(struct sna                          *sna,
                 const struct sna_composite_spans_op *op,
                 const BoxRec                        *box,
                 float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = ((box->x2 + tx) * xx + x0) * sx;
    v[6] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = ((box->x1 + tx) * xx + x0) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = ((box->y1 + ty) * yy + y0) * sy;

    v[11] = v[7] = v[3] = opacity;
}

sse2 static fastcall void
emit_span_boxes_simple(const struct sna_composite_spans_op *op,
                       const struct sna_opacity_box        *b,
                       int                                  nbox,
                       float                               *v)
{
    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = ((b->box.x2 + tx) * xx + x0) * sx;
        v[6] = v[2] = ((b->box.y2 + ty) * yy + y0) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = ((b->box.x1 + tx) * xx + x0) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = ((b->box.y1 + ty) * yy + y0) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_span_affine(struct sna                          *sna,
                 const struct sna_composite_spans_op *op,
                 const BoxRec                        *box,
                 float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x2,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[1],
                                &v[2]);

    dst.p.x = box->x1;
    v[4]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[5],
                                &v[6]);

    dst.p.y = box->y1;
    v[8]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y1,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[9],
                                &v[10]);

    v[11] = v[7] = v[3] = opacity;
}

sse2 static fastcall void
emit_span_boxes_affine(const struct sna_composite_spans_op *op,
                       const struct sna_opacity_box        *b,
                       int                                  nbox,
                       float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x2,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[1],
                                    &v[2]);

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[5],
                                    &v[6]);

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y1,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[9],
                                    &v[10]);

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse2 static fastcall void
emit_span_linear(struct sna                          *sna,
                 const struct sna_composite_spans_op *op,
                 const BoxRec                        *box,
                 float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    dst.p.x = box->x1;
    v[3]    = dst.f;
    dst.p.y = box->y1;
    v[6]    = dst.f;

    v[1] = compute_linear(&op->base.src, box->x2, box->y2);
    v[4] = compute_linear(&op->base.src, box->x1, box->y2);
    v[7] = compute_linear(&op->base.src, box->x1, box->y1);

    v[8] = v[5] = v[2] = opacity;
}

sse2 static fastcall void
emit_span_boxes_linear(const struct sna_composite_spans_op *op,
                       const struct sna_opacity_box        *b,
                       int                                  nbox,
                       float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        dst.p.x = b->box.x1;
        v[3]    = dst.f;
        dst.p.y = b->box.y1;
        v[6]    = dst.f;

        v[1] = compute_linear(&op->base.src, b->box.x2, b->box.y2);
        v[4] = compute_linear(&op->base.src, b->box.x1, b->box.y2);
        v[7] = compute_linear(&op->base.src, b->box.x1, b->box.y1);

        v[8] = v[5] = v[2] = b->alpha;

        v += 9;
        b++;
    }
    while (--nbox);
}

/* SSE4_2 */
#if defined(sse4_2)

sse4_2 fastcall static void
emit_span_identity__sse4_2(struct sna                          *sna,
                           const struct sna_composite_spans_op *op,
                           const BoxRec                        *box,
                           float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = (box->x2 + tx) * sx;
    v[6] = v[2] = (box->y2 + ty) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = (box->x1 + tx) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = (box->y1 + ty) * sy;

    v[11] = v[7] = v[3] = opacity;
}

sse4_2 static fastcall void
emit_span_boxes_identity__sse4_2(const struct sna_composite_spans_op *op,
                                 const struct sna_opacity_box        *b,
                                 int                                  nbox,
                                 float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        float   sx = op->base.src.scale[0];
        float   sy = op->base.src.scale[1];
        int16_t tx = op->base.src.offset[0];
        int16_t ty = op->base.src.offset[1];

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = (b->box.x2 + tx) * sx;
        v[6] = v[2] = (b->box.y2 + ty) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = (b->box.x1 + tx) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = (b->box.y1 + ty) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_span_simple__sse4_2(struct sna                          *sna,
                         const struct sna_composite_spans_op *op,
                         const BoxRec                        *box,
                         float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = ((box->x2 + tx) * xx + x0) * sx;
    v[6] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = ((box->x1 + tx) * xx + x0) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = ((box->y1 + ty) * yy + y0) * sy;

    v[11] = v[7] = v[3] = opacity;
}

sse4_2 static fastcall void
emit_span_boxes_simple__sse4_2(const struct sna_composite_spans_op *op,
                               const struct sna_opacity_box        *b,
                               int                                  nbox,
                               float                               *v)
{
    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = ((b->box.x2 + tx) * xx + x0) * sx;
        v[6] = v[2] = ((b->box.y2 + ty) * yy + y0) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = ((b->box.x1 + tx) * xx + x0) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = ((b->box.y1 + ty) * yy + y0) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_span_affine__sse4_2(struct sna                          *sna,
                         const struct sna_composite_spans_op *op,
                         const BoxRec                        *box,
                         float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x2,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[1],
                                &v[2]);

    dst.p.x = box->x1;
    v[4]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[5],
                                &v[6]);

    dst.p.y = box->y1;
    v[8]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y1,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[9],
                                &v[10]);

    v[11] = v[7] = v[3] = opacity;
}

sse4_2 static fastcall void
emit_span_boxes_affine__sse4_2(const struct sna_composite_spans_op *op,
                               const struct sna_opacity_box        *b,
                               int                                  nbox,
                               float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x2,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[1],
                                    &v[2]);

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[5],
                                    &v[6]);

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y1,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[9],
                                    &v[10]);

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

sse4_2 static fastcall void
emit_span_linear__sse4_2(struct sna                          *sna,
                         const struct sna_composite_spans_op *op,
                         const BoxRec                        *box,
                         float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    dst.p.x = box->x1;
    v[3]    = dst.f;
    dst.p.y = box->y1;
    v[6]    = dst.f;

    v[1] = compute_linear(&op->base.src, box->x2, box->y2);
    v[4] = compute_linear(&op->base.src, box->x1, box->y2);
    v[7] = compute_linear(&op->base.src, box->x1, box->y1);

    v[8] = v[5] = v[2] = opacity;
}

sse4_2 static fastcall void
emit_span_boxes_linear__sse4_2(const struct sna_composite_spans_op *op,
                               const struct sna_opacity_box        *b,
                               int                                  nbox,
                               float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        dst.p.x = b->box.x1;
        v[3]    = dst.f;
        dst.p.y = b->box.y1;
        v[6]    = dst.f;

        v[1] = compute_linear(&op->base.src, b->box.x2, b->box.y2);
        v[4] = compute_linear(&op->base.src, b->box.x1, b->box.y2);
        v[7] = compute_linear(&op->base.src, b->box.x1, b->box.y1);

        v[8] = v[5] = v[2] = b->alpha;

        v += 9;
        b++;
    }
    while (--nbox);
}

#endif

/* AVX2 */
#if defined(avx2)

avx2 fastcall static void
emit_span_identity__avx2(struct sna                          *sna,
                         const struct sna_composite_spans_op *op,
                         const BoxRec                        *box,
                         float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = (box->x2 + tx) * sx;
    v[6] = v[2] = (box->y2 + ty) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = (box->x1 + tx) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = (box->y1 + ty) * sy;

    v[11] = v[7] = v[3] = opacity;
}

avx2 static fastcall void
emit_span_boxes_identity__avx2(const struct sna_composite_spans_op *op,
                               const struct sna_opacity_box        *b,
                               int                                  nbox,
                               float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        float   sx = op->base.src.scale[0];
        float   sy = op->base.src.scale[1];
        int16_t tx = op->base.src.offset[0];
        int16_t ty = op->base.src.offset[1];

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = (b->box.x2 + tx) * sx;
        v[6] = v[2] = (b->box.y2 + ty) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = (b->box.x1 + tx) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = (b->box.y1 + ty) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_span_simple__avx2(struct sna                          *sna,
                       const struct sna_composite_spans_op *op,
                       const BoxRec                        *box,
                       float                                opacity)
{
    float *v;

    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 3 * 4;
    assert(sna->render.vertex_used <= sna->render.vertex_size);

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    v[1]    = ((box->x2 + tx) * xx + x0) * sx;
    v[6] = v[2] = ((box->y2 + ty) * yy + y0) * sy;

    dst.p.x = box->x1;
    v[4]    = dst.f;
    v[9] = v[5] = ((box->x1 + tx) * xx + x0) * sx;

    dst.p.y = box->y1;
    v[8]    = dst.f;
    v[10]   = ((box->y1 + ty) * yy + y0) * sy;

    v[11] = v[7] = v[3] = opacity;
}

avx2 static fastcall void
emit_span_boxes_simple__avx2(const struct sna_composite_spans_op *op,
                             const struct sna_opacity_box        *b,
                             int                                  nbox,
                             float                               *v)
{
    float   xx = op->base.src.transform->matrix[0][0];
    float   x0 = op->base.src.transform->matrix[0][2];
    float   yy = op->base.src.transform->matrix[1][1];
    float   y0 = op->base.src.transform->matrix[1][2];
    float   sx = op->base.src.scale[0];
    float   sy = op->base.src.scale[1];
    int16_t tx = op->base.src.offset[0];
    int16_t ty = op->base.src.offset[1];

    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        v[1]    = ((b->box.x2 + tx) * xx + x0) * sx;
        v[6] = v[2] = ((b->box.y2 + ty) * yy + y0) * sy;

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        v[9] = v[5] = ((b->box.x1 + tx) * xx + x0) * sx;

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        v[10]   = ((b->box.y1 + ty) * yy + y0) * sy;

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_span_affine__avx2(struct sna                          *sna,
                       const struct sna_composite_spans_op *op,
                       const BoxRec                        *box,
                       float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 12);
    assert((sna->render.vertex_used % 4) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 12;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x2,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[1],
                                &v[2]);

    dst.p.x = box->x1;
    v[4]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y2,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[5],
                                &v[6]);

    dst.p.y = box->y1;
    v[8]    = dst.f;
    _sna_get_transformed_scaled(op->base.src.offset[0] + box->x1,
                                op->base.src.offset[1] + box->y1,
                                op->base.src.transform,
                                op->base.src.scale,
                                &v[9],
                                &v[10]);

    v[11] = v[7] = v[3] = opacity;
}

avx2 static fastcall void
emit_span_boxes_affine__avx2(const struct sna_composite_spans_op *op,
                             const struct sna_opacity_box        *b,
                             int                                  nbox,
                             float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x2,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[1],
                                    &v[2]);

        dst.p.x = b->box.x1;
        v[4]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y2,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[5],
                                    &v[6]);

        dst.p.y = b->box.y1;
        v[8]    = dst.f;
        _sna_get_transformed_scaled(op->base.src.offset[0] + b->box.x1,
                                    op->base.src.offset[1] + b->box.y1,
                                    op->base.src.transform,
                                    op->base.src.scale,
                                    &v[9],
                                    &v[10]);

        v[11] = v[7] = v[3] = b->alpha;

        v += 12;
        b++;
    }
    while (--nbox);
}

avx2 static fastcall void
emit_span_linear__avx2(struct sna                          *sna,
                       const struct sna_composite_spans_op *op,
                       const BoxRec                        *box,
                       float                                opacity)
{
    union {
        struct sna_coordinate p;
        float                 f;
    } dst;

    float *v;

    assert(op->base.floats_per_rect == 9);
    assert((sna->render.vertex_used % 3) == 0);
    v = sna->render.vertices + sna->render.vertex_used;
    sna->render.vertex_used += 9;

    dst.p.x = box->x2;
    dst.p.y = box->y2;
    v[0]    = dst.f;
    dst.p.x = box->x1;
    v[3]    = dst.f;
    dst.p.y = box->y1;
    v[6]    = dst.f;

    v[1] = compute_linear(&op->base.src, box->x2, box->y2);
    v[4] = compute_linear(&op->base.src, box->x1, box->y2);
    v[7] = compute_linear(&op->base.src, box->x1, box->y1);

    v[8] = v[5] = v[2] = opacity;
}

avx2 static fastcall void
emit_span_boxes_linear__avx2(const struct sna_composite_spans_op *op,
                             const struct sna_opacity_box        *b,
                             int                                  nbox,
                             float                               *v)
{
    do
    {
        union {
            struct sna_coordinate p;
            float                 f;
        } dst;

        dst.p.x = b->box.x2;
        dst.p.y = b->box.y2;
        v[0]    = dst.f;
        dst.p.x = b->box.x1;
        v[3]    = dst.f;
        dst.p.y = b->box.y1;
        v[6]    = dst.f;

        v[1] = compute_linear(&op->base.src, b->box.x2, b->box.y2);
        v[4] = compute_linear(&op->base.src, b->box.x1, b->box.y2);
        v[7] = compute_linear(&op->base.src, b->box.x1, b->box.y1);

        v[8] = v[5] = v[2] = b->alpha;

        v += 9;
        b++;
    }
    while (--nbox);
}
#endif

unsigned
gen4_choose_spans_emitter(struct sna *sna, struct sna_composite_spans_op *tmp)
{
    unsigned vb;

    if (tmp->base.src.is_solid)
    {
        DBG(("%s: solid source\n", __FUNCTION__));
        tmp->prim_emit              = emit_span_solid;
        tmp->emit_boxes             = emit_span_boxes_solid;
        tmp->base.floats_per_vertex = 3;
        vb                          = 1 << 2 | 1;
    }
    else if (tmp->base.src.is_linear)
    {
        DBG(("%s: linear source\n", __FUNCTION__));
#if defined(avx2)
        if (sna->cpu_features & AVX2)
        {
            tmp->prim_emit  = emit_span_linear__avx2;
            tmp->emit_boxes = emit_span_boxes_linear__avx2;
        }
        else
#endif
#if defined(sse4_2)
            if (sna->cpu_features & SSE4_2)
        {
            tmp->prim_emit  = emit_span_linear__sse4_2;
            tmp->emit_boxes = emit_span_boxes_linear__sse4_2;
        }
        else
#endif
        {
            tmp->prim_emit  = emit_span_linear;
            tmp->emit_boxes = emit_span_boxes_linear;
        }
        tmp->base.floats_per_vertex = 3;
        vb                          = 1 << 2 | 1;
    }
    else if (tmp->base.src.transform == NULL)
    {
        DBG(("%s: identity transform\n", __FUNCTION__));
#if defined(avx2)
        if (sna->cpu_features & AVX2)
        {
            tmp->prim_emit  = emit_span_identity__avx2;
            tmp->emit_boxes = emit_span_boxes_identity__avx2;
        }
        else
#endif
#if defined(sse4_2)
            if (sna->cpu_features & SSE4_2)
        {
            tmp->prim_emit  = emit_span_identity__sse4_2;
            tmp->emit_boxes = emit_span_boxes_identity__sse4_2;
        }
        else
#endif
        {
            tmp->prim_emit  = emit_span_identity;
            tmp->emit_boxes = emit_span_boxes_identity;
        }
        tmp->base.floats_per_vertex = 4;
        vb                          = 1 << 2 | 2;
    }
    else if (tmp->base.is_affine)
    {
        tmp->base.src.scale[0] /= tmp->base.src.transform->matrix[2][2];
        tmp->base.src.scale[1] /= tmp->base.src.transform->matrix[2][2];
        if (!sna_affine_transform_is_rotation(tmp->base.src.transform))
        {
            DBG(("%s: simple (unrotated affine) transform\n", __FUNCTION__));
#if defined(avx2)
            if (sna->cpu_features & AVX2)
            {
                tmp->prim_emit  = emit_span_simple__avx2;
                tmp->emit_boxes = emit_span_boxes_simple__avx2;
            }
            else
#endif
#if defined(sse4_2)
                if (sna->cpu_features & SSE4_2)
            {
                tmp->prim_emit  = emit_span_simple__sse4_2;
                tmp->emit_boxes = emit_span_boxes_simple__sse4_2;
            }
            else
#endif
            {
                tmp->prim_emit  = emit_span_simple;
                tmp->emit_boxes = emit_span_boxes_simple;
            }
        }
        else
        {
            DBG(("%s: affine transform\n", __FUNCTION__));
#if defined(avx2)
            if (sna->cpu_features & AVX2)
            {
                tmp->prim_emit  = emit_span_affine__avx2;
                tmp->emit_boxes = emit_span_boxes_affine__avx2;
            }
            else
#endif
#if defined(sse4_2)
                if (sna->cpu_features & SSE4_2)
            {
                tmp->prim_emit  = emit_span_affine__sse4_2;
                tmp->emit_boxes = emit_span_boxes_affine__sse4_2;
            }
            else
#endif
            {
                tmp->prim_emit  = emit_span_affine;
                tmp->emit_boxes = emit_span_boxes_affine;
            }
        }
        tmp->base.floats_per_vertex = 4;
        vb                          = 1 << 2 | 2;
    }
    else
    {
        DBG(("%s: projective transform\n", __FUNCTION__));
        tmp->prim_emit              = emit_span_primitive;
        tmp->emit_boxes             = emit_span_boxes;
        tmp->base.floats_per_vertex = 5;
        vb                          = 1 << 2 | 3;
    }
    tmp->base.floats_per_rect = 3 * tmp->base.floats_per_vertex;
    return vb;
}
