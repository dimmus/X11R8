/*

Copyright 1988, 1998  The Open Group

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
 * This file contains routines to handle common selection targets.
 *
 * Public entry points:
 *
 *	XmuConvertStandardSelection()	return a known selection
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "X11/IntrinsicP.h"
#include "X11/Xatom.h"
#include "X11/ShellP.h"
#ifdef XTHREADS
#  include "X11/Xthreads.h"
#endif
#include <stdio.h>

#ifdef WIN32
#  include "X11/Xwinsock.h"
#else
#  include <sys/socket.h>
#  define XOS_USE_XT_LOCKING
#endif
#include "X11/Xos_r.h"

#include "X11/Xos.h"
#include <stdlib.h>
#include "Atoms.h"
#include "StdSel.h"
#include "SysUtil.h"
#include "X11/Xfuncs.h"

#ifndef OS_NAME
#  ifndef X_OS_FILE
#    ifdef HAVE_UNAME
#      define USE_UNAME
#    endif
#  endif /*X_OS_FILE*/
#  ifdef USE_UNAME
#    include <sys/utsname.h>
#  endif
#endif

/*
 * Prototypes
 */
static char *get_os_name(void);
static Bool  isApplicationShell(Widget);

/*
 * Implementation
 */
static char *
get_os_name(void)
{
#ifdef OS_NAME
    return XtNewString(OS_NAME);
#else
#  if defined(X_OS_FILE) || defined(MOTD_FILE)
    FILE *f = NULL;
#  endif

#  ifdef USE_UNAME
    struct utsname utss;

    if (uname(&utss) >= 0)
    {
        char *os_name;

        XtAsprintf(&os_name, "%s %s", utss.sysname, utss.release);
        return os_name;
    }
#  endif

#  ifdef X_OS_FILE
    f = fopen(X_OS_FILE, "r");
    if (!f)
#  endif
#  ifdef MOTD_FILE
        f = fopen(MOTD_FILE, "r");
#  endif
#  if defined(X_OS_FILE) || defined(MOTD_FILE)
    if (f)
    {
        char motd[512];
        motd[0] = '\0';
        (void)fgets(motd, 511, f);
        fclose(f);
        motd[511] = '\0';
        if (motd[0] != '\0')
        {
            int len = strlen(motd);
            if (motd[len - 1] == '\n') motd[len - 1] = '\0';
            return XtNewString(motd);
        }
    }
#  endif

#  ifdef CSRG_BASED
    return XtNewString("BSD");
#  else
    return NULL;
#  endif

#endif /*OS_NAME*/
}

/* This is a trick/kludge.  To make shared libraries happier (linking
 * against Xmu but not linking against Xt, and apparently even work
 * as we desire on SVR4, we need to avoid an explicit data reference
 * to applicationShellWidgetClass.  XtIsTopLevelShell is known
 * (implementation dependent assumption!) to use a bit flag.  So we
 * go that far.  Then, we test whether it is an applicationShellWidget
 * class by looking for an explicit class name.  Seems pretty safe.
 */
static Bool
isApplicationShell(Widget w)
{
    register WidgetClass c;

    if (!XtIsTopLevelShell(w)) return False;
    for (c = XtClass(w); c; c = c->core_class.superclass)
    {
        if (!strcmp(c->core_class.class_name, "ApplicationShell")) return True;
    }
    return False;
}

Boolean
XmuConvertStandardSelection(Widget         w,
                            Time           time,
                            Atom          *selection,
                            Atom          *target,
                            Atom          *type,
                            XPointer      *value,
                            unsigned long *length,
                            int           *format)
{
    Display *d = XtDisplay(w);
    if (*target == XA_TIMESTAMP(d))
    {
        *value = XtMalloc(4);
        if (sizeof(long) == 4) *(long *)*value = time;
        else
        {
            long temp = time;
            memcpy((char *)*value, ((char *)&temp) + sizeof(long) - 4, 4);
        }
        *type   = XA_INTEGER;
        *length = 1;
        *format = 32;
        return True;
    }
    if (*target == XA_HOSTNAME(d))
    {
        char hostname[1024];
        hostname[0] = '\0';
        *length     = XmuGetHostname(hostname, sizeof hostname);
        *value      = XtNewString(hostname);
        *type       = XA_STRING;
        *format     = 8;
        return True;
    }
    if (*target == XA_USER(d))
    {
        char *name = (char *)getenv("USER");
        if (name == NULL) return False;
        *value  = XtNewString(name);
        *type   = XA_STRING;
        *length = strlen(name);
        *format = 8;
        return True;
    }
    if (*target == XA_CLASS(d))
    {
        Widget parent = XtParent(w);
        String class;
        int len;
        while (parent != NULL && !isApplicationShell(w))
        {
            w      = parent;
            parent = XtParent(w);
        }
        if (isApplicationShell(w))
            class = ((ApplicationShellWidget)w)->application.class;
        else class = XtClass(w)->core_class.class_name;
        *length = (len = strlen(w->core.name)) + strlen(class) + 2;
        *value  = XtMalloc(*length);
        strcpy((char *)*value, w->core.name);
        strcpy((char *)*value + len + 1, class);
        *type   = XA_STRING;
        *format = 8;
        return True;
    }
    if (*target == XA_NAME(d))
    {
        Widget parent = XtParent(w);

        while (parent != NULL && !XtIsWMShell(w))
        {
            w      = parent;
            parent = XtParent(w);
        }
        if (!XtIsWMShell(w)) return False;
        *value  = XtNewString(((WMShellWidget)w)->wm.title);
        *length = strlen(*value);
        *type   = XA_STRING;
        *format = 8;
        return True;
    }
    if (*target == XA_CLIENT_WINDOW(d))
    {
        Widget parent = XtParent(w);
        while (parent != NULL)
        {
            w      = parent;
            parent = XtParent(w);
        }
        *value            = XtMalloc(sizeof(Window));
        *(Window *)*value = w->core.window;
        *type             = XA_WINDOW;
        *length           = 1;
        *format           = 32;
        return True;
    }
    if (*target == XA_OWNER_OS(d))
    {
        *value = get_os_name();
        if (*value == NULL) return False;
        *type   = XA_STRING;
        *length = strlen(*value);
        *format = 8;
        return True;
    }
    if (*target == XA_TARGETS(d))
    {
#if defined(unix)
#  define NUM_TARGETS 7
#else
#  define NUM_TARGETS 6
#endif
        Atom *std_targets = (Atom *)XtMalloc(NUM_TARGETS * sizeof(Atom));
        int   i           = 0;
        std_targets[i++]  = XA_TIMESTAMP(d);
        std_targets[i++]  = XA_HOSTNAME(d);
        std_targets[i++]  = XA_USER(d);
        std_targets[i++]  = XA_CLASS(d);
        std_targets[i++]  = XA_NAME(d);
        std_targets[i++]  = XA_CLIENT_WINDOW(d);
#ifdef unix
        std_targets[i++] = XA_OWNER_OS(d);
#endif
        *value  = (XPointer)std_targets;
        *type   = XA_ATOM;
        *length = NUM_TARGETS;
        *format = 32;
        return True;
    }
    /* else */
    return False;
}
