/*
 * Copyright (C) 2006-2017 Oracle Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef ___VBox_Graphics_HGSMIContext_h___
#define ___VBox_Graphics_HGSMIContext_h___

#include "HGSMI.h"
#include "HGSMIChSetup.h"
#include "VBoxVideoIPRT.h"

#ifdef VBOX_WDDM_MINIPORT
#  include "wddm/VBoxMPShgsmi.h"
typedef VBOXSHGSMI HGSMIGUESTCMDHEAP;
#  define HGSMIGUESTCMDHEAP_GET(_p) (&(_p)->Heap)
#else
typedef HGSMIHEAP HGSMIGUESTCMDHEAP;
#  define HGSMIGUESTCMDHEAP_GET(_p) (_p)
#endif

RT_C_DECLS_BEGIN

/**
 * Structure grouping the context needed for submitting commands to the host
 * via HGSMI
 */
typedef struct HGSMIGUESTCOMMANDCONTEXT
{
    /** Information about the memory heap located in VRAM from which data
     * structures to be sent to the host are allocated. */
    HGSMIGUESTCMDHEAP heapCtx;
    /** The I/O port used for submitting commands to the host by writing their
     * offsets into the heap. */
    RTIOPORT port;
} HGSMIGUESTCOMMANDCONTEXT, *PHGSMIGUESTCOMMANDCONTEXT;

/**
 * Structure grouping the context needed for receiving commands from the host
 * via HGSMI
 */
typedef struct HGSMIHOSTCOMMANDCONTEXT
{
    /** Information about the memory area located in VRAM in which the host
     * places data structures to be read by the guest. */
    HGSMIAREA areaCtx;
    /** Convenience structure used for matching host commands to handlers. */
    /** @todo handlers are registered individually in code rather than just
     * passing a static structure in order to gain extra flexibility.  There is
     * currently no expected usage case for this though.  Is the additional
     * complexity really justified? */
    HGSMICHANNELINFO channels;
    /** Flag to indicate that one thread is currently processing the command
     * queue. */
    volatile bool fHostCmdProcessing;
    /* Pointer to the VRAM location where the HGSMI host flags are kept. */
    volatile HGSMIHOSTFLAGS *pfHostFlags;
    /** The I/O port used for receiving commands from the host as offsets into
     * the memory area and sending back confirmations (command completion,
     * IRQ acknowlegement). */
    RTIOPORT port;
} HGSMIHOSTCOMMANDCONTEXT, *PHGSMIHOSTCOMMANDCONTEXT;

/** @name HGSMI context initialisation APIs.
 * @{ */

/** @todo we should provide a cleanup function too as part of the API */
DECLHIDDEN(int)
VBoxHGSMISetupGuestContext(PHGSMIGUESTCOMMANDCONTEXT pCtx,
                           void                     *pvGuestHeapMemory,
                           uint32_t                  cbGuestHeapMemory,
                           uint32_t                  offVRAMGuestHeapMemory,
                           const HGSMIENV           *pEnv);
DECLHIDDEN(void)
VBoxHGSMISetupHostContext(PHGSMIHOSTCOMMANDCONTEXT pCtx,
                          void                    *pvBaseMapping,
                          uint32_t                 offHostFlags,
                          void                    *pvHostAreaMapping,
                          uint32_t                 offVRAMHostArea,
                          uint32_t                 cbHostArea);

/** @}  */

RT_C_DECLS_END

#endif
