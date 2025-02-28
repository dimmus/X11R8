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
XGrabPointer(register Display *dpy,
             Window            grab_window,
             Bool              owner_events,
             unsigned int      event_mask, /* CARD16 */
             int               pointer_mode,
             int               keyboard_mode,
             Window            confine_to,
             Cursor            curs,
             Time              time)
{
    xGrabPointerReply         rep;
    register xGrabPointerReq *req;
    register int              status;
    LockDisplay(dpy);
    GetReq(GrabPointer, req);
    req->grabWindow   = grab_window;
    req->ownerEvents  = owner_events;
    req->eventMask    = event_mask;
    req->pointerMode  = pointer_mode;
    req->keyboardMode = keyboard_mode;
    req->confineTo    = confine_to;
    req->cursor       = curs;
    req->time         = time;

    /* if we ever return, suppress the error */
    if (_XReply(dpy, (xReply *)&rep, 0, xTrue) == 0) rep.status = GrabSuccess;
    status = rep.status;
    UnlockDisplay(dpy);
    SyncHandle();
    return (status);
}
