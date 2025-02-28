/*
 * Copyright (c) 2011, 2022, Oracle and/or its affiliates.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "X11/Intrinsic.h"

#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>
#include <stdio.h>

/* Test XtAppMainLoop without a display doesn't wait for an XEvent.
   Based on https://bugs.freedesktop.org/show_bug.cgi?id=34715 */
static void
_Tick(XtPointer baton, XtIntervalId *id)
{
    static int   count = 0;
    XtAppContext app   = (XtAppContext)baton;

    count++;
#ifdef DEBUG
    printf("%d beep!\n", count);
#endif

    if (count == 1) /* 1 sec */
        XtAppSetExitFlag(app);
    else XtAppAddTimeOut(app, 1000, _Tick, app);
}

static sigjmp_buf jump_env;

static void
sigalrm(int sig)
{
    siglongjmp(jump_env, 1);
}

static void
test_XtAppMainLoop_34715(void)
{
    XtAppContext     app;
    struct sigaction sa;

    XtToolkitInitialize();
    app = XtCreateApplicationContext();
    XtAppAddTimeOut(app, 1000, _Tick, app);

    /* AppTimeouts should finish and exit in 3 seconds.
       Give them 10 seconds just in case system is busy, then fail. */
    sa.sa_handler = sigalrm;
    sa.sa_flags   = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigsetjmp(jump_env, 1) == 0)
    {
        sigaction(SIGALRM, &sa, NULL);
        alarm(10);

        XtAppMainLoop(app);
        alarm(0); /* cancel alarm */
    }
    else
    {
        printf("test timed out: %s at %d", __FILE__, __LINE__);
    }
    assert(XtAppGetExitFlag(app) == TRUE);
    XtDestroyApplicationContext(app);
}

int
main(int argc, char **argv)
{
    test_XtAppMainLoop_34715();
}
