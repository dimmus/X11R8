/*

Copyright 1991, 1998  The Open Group

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

/*
 * Author:  Keith Packard, MIT X Consortium
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "libxfontint.h"
#include "fntfilio.h"
#include "X11/Xos.h"
#ifndef O_BINARY
#  define O_BINARY 0
#endif
#ifndef O_CLOEXEC
#  define O_CLOEXEC 0
#endif

FontFilePtr
FontFileOpenWrite(const char *name)
{
    int fd;

    fd = open(name, O_CREAT | O_TRUNC | O_RDWR | O_BINARY | O_CLOEXEC, 0666);
    if (fd < 0) return 0;
    return (FontFilePtr)BufFileOpenWrite(fd);
}

FontFilePtr
FontFileOpenWriteFd(int fd)
{
    return (FontFilePtr)BufFileOpenWrite(fd);
}

FontFilePtr
FontFileOpenFd(int fd)
{
    return (FontFilePtr)BufFileOpenRead(fd);
}
