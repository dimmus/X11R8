/*
Copyright 1989, 1998  The Open Group

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
 * *
 * Author:  Keith Packard, MIT X Consortium
 */

#ifdef WIN32
#  define _WILLWINSOCK_
#endif
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "X11/Xos.h"
#include "X11/X.h"
#include "X11/Xmd.h"
#include "X11/Xdmcp.h"

#ifdef WIN32
#  include "X11/Xwinsock.h"
#else
#  include <sys/socket.h>
#endif

int
XdmcpFlush(int fd, XdmcpBufferPtr buffer, XdmcpNetaddr to, int tolen)
{
    int result;
    result = sendto(fd,
                    (char *)buffer->data,
                    buffer->pointer,
                    0,
                    (struct sockaddr *)to,
                    tolen);
    if (result != buffer->pointer) return FALSE;
    return TRUE;
}
