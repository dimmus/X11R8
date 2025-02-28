/*
 * Copyright (C) 1998 The XFree86 Project, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * XFREE86 PROJECT BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the XFree86 Project shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * XFree86 Project.
 */
#ifndef SESSION_H
#define SESSION_H

#include "twm.h"

#include "X11/SM/SMlib.h"

extern void ConnectToSessionManager(char *previous_id, XtAppContext appContext);
extern int  GetWindowConfig(TwmWindow      *theWindow,
                            short          *x,
                            short          *y,
                            unsigned short *width,
                            unsigned short *height,
                            Bool           *iconified,
                            Bool           *icon_info_present,
                            short          *icon_x,
                            short          *icon_y,
                            Bool           *width_ever_changed_by_user,
                            Bool           *height_ever_changed_by_user);
extern void ReadWinConfigFile(char *filename);
extern void DestroySession(void);

extern SmcConn smcConn;

#endif /* SESSION_H */
