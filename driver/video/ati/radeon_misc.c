/*
 * Copyright 2000 through 2004 by Marc Aurele La France (TSI @ UQV), tsi@xfree86.org
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of Marc Aurele La France not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Marc Aurele La France makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as-is" without express or implied warranty.
 *
 * MARC AURELE LA FRANCE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN NO
 * EVENT SHALL MARC AURELE LA FRANCE BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "radeon_probe.h"
#include "radeon_version.h"

#include "xf86.h"

/* Module loader interface for subsidiary driver module */

static XF86ModuleVersionInfo RADEONVersionRec = {
    RADEON_DRIVER_NAME,   MODULEVENDORSTRING,   MODINFOSTRING1,
    MODINFOSTRING2,       XORG_VERSION_CURRENT, RADEON_VERSION_MAJOR,
    RADEON_VERSION_MINOR, RADEON_VERSION_PATCH, ABI_CLASS_VIDEODRV,
    ABI_VIDEODRV_VERSION, MOD_CLASS_VIDEODRV,   { 0, 0, 0, 0 }
};

/*
 * RADEONSetup --
 *
 * This function is called every time the module is loaded.
 */
static pointer
RADEONSetup(pointer Module, pointer Options, int *ErrorMajor, int *ErrorMinor)
{
    static Bool Inited = FALSE;

    if (!Inited)
    {
        Inited = TRUE;
        xf86AddDriver(&RADEON, Module, HaveDriverFuncs);
    }

    return (pointer)TRUE;
}

/* The following record must be called radeonModuleData */
_X_EXPORT XF86ModuleData radeonModuleData = { &RADEONVersionRec,
                                              RADEONSetup,
                                              NULL };
