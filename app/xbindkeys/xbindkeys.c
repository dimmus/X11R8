/***************************************************************************
        xbindkeys : a program to bind keys to commands under X11.
                           -------------------
    begin                : Sat Oct 13 14:11:34 CEST 2001
    copyright            : (C) 2001 by Philippe Brochard
    email                : hocwp@free.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "xbindkeys.h"
#include "keys.h"
#include "options.h"
#include "get_key.h"
#include "grab_key.h"

#include <X11/XKBlib.h>

void end_it_all(Display *d);

static Display *start(char *);
static void     event_loop(Display *);
static int     *null_X_error(Display *, XErrorEvent *);
static void     reload_rc_file(void);
static void     catch_HUP_signal(int sig);
static void     catch_CHLD_signal(int sig);
static void     start_as_daemon(void);

Display *current_display;

extern char rc_file[512];
extern int  poll_rc;

#define SLEEP_TIME 100

int
main(int argc, char **argv)
{
    Display *d;

    get_options(argc, argv);

    if (!rc_file_exist()) exit(-1);

    if (have_to_start_as_daemon && !have_to_show_binding &&
        !have_to_get_binding)
        start_as_daemon();

    if (!display_name) display_name = XDisplayName(NULL);

    show_options();

    d               = start(display_name);
    current_display = d;

    if (detectable_ar)
    {
        Bool supported_rtrn;
        XkbSetDetectableAutoRepeat(d, True, &supported_rtrn);

        if (!supported_rtrn)
        {
            fprintf(stderr, "Could not set detectable autorepeat\n");
        }
    }

    get_offending_modifiers(d);

    if (have_to_get_binding)
    {
        get_key_binding(d, argv, argc);
        end_it_all(d);
        exit(0);
    }

    if (get_rc_file() != 0)
    {
        end_it_all(d);
        exit(-1);
    }

    if (have_to_show_binding)
    {
        show_key_binding(d);
        end_it_all(d);
        exit(0);
    }

    grab_keys(d);

  /* This: for restarting reading the RC file if get a HUP signal */
    signal(SIGHUP, catch_HUP_signal);
  /* and for reaping dead children */
    signal(SIGCHLD, catch_CHLD_signal);

    if (verbose) printf("starting loop...\n");
    event_loop(d);

    if (verbose) printf("ending...\n");
    end_it_all(d);
}

static Display *
start(char *display)
{
    Display *d;
    int      screen;

    d = XOpenDisplay(display);
    if (!d)
    {
        fprintf(stderr, "Could not open display, check shell DISPLAY variable, \
and export or setenv it!\n");
        exit(1);
    }

    XAllowEvents(d, AsyncBoth, CurrentTime);

    for (screen = 0; screen < ScreenCount(d); screen++)
    {
        XSelectInput(d,
                     RootWindow(d, screen),
                     KeyPressMask | KeyReleaseMask | PointerMotionMask);
    }

    return (d);
}

void
end_it_all(Display *d)
{
    ungrab_all_keys(d);

    close_keys();
    XCloseDisplay(d);
}

static void
adjust_display(XAnyEvent *xany)
{
    size_t envstr_size = strlen(DisplayString(xany->display)) + 8 + 1;
    char  *envstr      = malloc((envstr_size + 2) * sizeof(char));
    XWindowAttributes attr;
    char             *ptr;
    char              buf[16];

    snprintf(envstr, envstr_size, "DISPLAY=%s", DisplayString(xany->display));

    XGetWindowAttributes(xany->display, xany->window, &attr);

    if (verbose)
        printf("got screen %d for window %x\n",
               XScreenNumberOfScreen(attr.screen),
               (unsigned int)xany->window);

    ptr = strchr(strchr(envstr, ':'), '.');
    if (ptr) *ptr = '\0';

    snprintf(buf, sizeof(buf), ".%i", XScreenNumberOfScreen(attr.screen));
    strncat(envstr, buf, 16);

    putenv(envstr);
}

static void
event_loop(Display *d)
{
    XEvent      e;
    int         i;
    struct stat rc_file_info;
    time_t      rc_file_changed = 0;

    XSetErrorHandler((XErrorHandler)null_X_error);

    if (poll_rc)
    {
        stat(rc_file, &rc_file_info);
        rc_file_changed = rc_file_info.st_mtime;
    }

    while (True)
    {
        while (poll_rc && !XPending(d))
        {
      // if the rc file has been modified, reload it
            stat(rc_file, &rc_file_info);

            if (rc_file_info.st_mtime != rc_file_changed)
            {
                reload_rc_file();
                if (verbose)
                {
                    printf("The configuration file has been modified, reload "
                           "it\n");
                }
                rc_file_changed = rc_file_info.st_mtime;
            }

            usleep(SLEEP_TIME * 1000);
        }

        XNextEvent(d, &e);

        switch (e.type)
        {
            case KeyPress:
                if (verbose)
                {
                    printf("Key press !\n");
                    printf("e.xkey.keycode=%d\n", e.xkey.keycode);
                    printf("e.xkey.state=%d\n", e.xkey.state);
                }

                e.xkey.state &=
                    ~(numlock_mask | capslock_mask | scrolllock_mask);

                for (i = 0; i < nb_keys; i++)
                {
                    if (keys[i].type == SYM && keys[i].event_type == PRESS)
                    {
                        if (e.xkey.keycode ==
                                XKeysymToKeycode(d, keys[i].key.sym) &&
                            e.xkey.state == keys[i].modifier)
                        {
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                    else if (keys[i].type == CODE &&
                             keys[i].event_type == PRESS)
                    {
                        if (e.xkey.keycode == keys[i].key.code &&
                            e.xkey.state == keys[i].modifier)
                        {
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                }
                break;

            case KeyRelease:
                if (verbose)
                {
                    printf("Key release !\n");
                    printf("e.xkey.keycode=%d\n", e.xkey.keycode);
                    printf("e.xkey.state=%d\n", e.xkey.state);
                }

                e.xkey.state &=
                    ~(numlock_mask | capslock_mask | scrolllock_mask);

                for (i = 0; i < nb_keys; i++)
                {
                    if (keys[i].type == SYM && keys[i].event_type == RELEASE)
                    {
                        if (e.xkey.keycode ==
                                XKeysymToKeycode(d, keys[i].key.sym) &&
                            e.xkey.state == keys[i].modifier)
                        {
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                    else if (keys[i].type == CODE &&
                             keys[i].event_type == RELEASE)
                    {
                        if (e.xkey.keycode == keys[i].key.code &&
                            e.xkey.state == keys[i].modifier)
                        {
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                }
                break;

            case ButtonPress:
                if (verbose)
                {
                    printf("Button press !\n");
                    printf("e.xbutton.button=%d\n", e.xbutton.button);
                    printf("e.xbutton.state=%d\n", e.xbutton.state);
                }

                e.xbutton.state &=
                    0x1FFF & ~(numlock_mask | capslock_mask | scrolllock_mask |
                               Button1Mask | Button2Mask | Button3Mask |
                               Button4Mask | Button5Mask);

                for (i = 0; i < nb_keys; i++)
                {
                    if (keys[i].type == BUTTON && keys[i].event_type == PRESS)
                    {
                        if (e.xbutton.button == keys[i].key.button &&
                            e.xbutton.state == keys[i].modifier)
                        {
                      //printf("Replay!!!\n");
                      //ungrab_all_keys(d);
                      //XPutBackEvent(d, &e);
                      //sleep(1);
                      //grab_keys(d);
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                }
                break;

            case ButtonRelease:
                if (verbose)
                {
                    printf("Button release !\n");
                    printf("e.xbutton.button=%d\n", e.xbutton.button);
                    printf("e.xbutton.state=%d\n", e.xbutton.state);
                }

                e.xbutton.state &=
                    0x1FFF & ~(numlock_mask | capslock_mask | scrolllock_mask |
                               Button1Mask | Button2Mask | Button3Mask |
                               Button4Mask | Button5Mask);

                for (i = 0; i < nb_keys; i++)
                {
                    if (keys[i].type == BUTTON && keys[i].event_type == RELEASE)
                    {
                        if (e.xbutton.button == keys[i].key.button &&
                            e.xbutton.state == keys[i].modifier)
                        {
                            print_key(d, &keys[i]);
                            adjust_display(&e.xany);
                            start_command_key(&keys[i]);
                        }
                    }
                }
                break;

            default:
                break;
        }
    }    /*  infinite loop */
}

static int *
null_X_error(Display *d, XErrorEvent *e)
{
    static int already = 0;

  /* The warning is displayed only once */
    if (already != 0) return (NULL);
    already = 1;

    printf("\n*** Warning ***\n");
    printf("Please verify that there is not another program running\n");
    printf("which captures one of the keys captured by xbindkeys.\n");
    printf("It seems that there is a conflict, and xbindkeys can't\n");
    printf("grab all the keys defined in its configuration file.\n");

/*   end_it_all (d); */

/*   exit (-1); */

    return (NULL);
}

static void
reload_rc_file(void)
{
    int min, max;
    int screen;

    XDisplayKeycodes(current_display, &min, &max);

    if (verbose) printf("Reload RC file\n");

    for (screen = 0; screen < ScreenCount(current_display); screen++)
    {
        XUngrabKey(current_display,
                   AnyKey,
                   AnyModifier,
                   RootWindow(current_display, screen));
    }
    close_keys();

    if (get_rc_file() != 0)
    {
        end_it_all(current_display);
        exit(-1);
    }
    grab_keys(current_display);
}

static void
catch_HUP_signal(int sig)
{
    reload_rc_file();
}

static void
catch_CHLD_signal(int sig)
{
    pid_t child;

    /*   If more than one child exits at approximately the same time, the signals */
    /*   may get merged. Handle this case correctly. */
    while ((child = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        if (verbose) printf("Catch CHLD signal -> pid %i terminated\n", child);
    }
}

static void
start_as_daemon(void)
{
    pid_t pid;
    int   i;

    pid = fork();
    if (pid < 0)
    {
        perror("Could not fork");
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    setsid();

    pid = fork();
    if (pid < 0)
    {
        perror("Could not fork");
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    for (i = getdtablesize(); i >= 0; i--)
    {
        close(i);
    }

    i = open("/dev/null", O_RDWR);
    dup(i);
    dup(i);

    /*   umask (022); */
    /*   chdir ("/tmp"); */
}
