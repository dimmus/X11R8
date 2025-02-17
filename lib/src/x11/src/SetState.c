/*

Copyright 1986, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "Xlibint.h"

int
XSetState(register Display *dpy,
          GC                gc,
          unsigned long     foreground,
          unsigned long     background,
          int               function,
          unsigned long     planemask)
{
    XGCValues *gv = &gc->values;

    LockDisplay(dpy);

    if (function != gv->function)
    {
        gv->function = function;
        gc->dirty |= GCFunction;
    }
    if (planemask != gv->plane_mask)
    {
        gv->plane_mask = planemask;
        gc->dirty |= GCPlaneMask;
    }
    if (foreground != gv->foreground)
    {
        gv->foreground = foreground;
        gc->dirty |= GCForeground;
    }
    if (background != gv->background)
    {
        gv->background = background;
        gc->dirty |= GCBackground;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}
