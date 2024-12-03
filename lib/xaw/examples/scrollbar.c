#include <stdlib.h>
#include <stdio.h>
#include <X11/StringDefs.h>
#include <Xaw/Box.h>
#include <Xaw/Label.h>
#include <Xaw/Scrollbar.h>
#include <Xaw/Command.h>

static void
quit_cb(Widget w, XtPointer client_data _X_UNUSED, XtPointer call_data _X_UNUSED)
{
    XtAppSetExitFlag(XtWidgetToApplicationContext(w));
}

#define recur(func) \
	1 + ((value > 1) \
	     ? func(value / 10) \
	     : ((value < 0) \
	        ? func(-value / 10) \
	        : 0))

static size_t long_len(long value)
{
    return recur(long_len);
}

static size_t float_len(float value)
{
    return recur(float_len);
}

static void
scroll_cb(Widget widget _X_UNUSED, XtPointer label_ptr, XtPointer value_ptr)
{
    long value   = (long) value_ptr;
    Widget label = (Widget) label_ptr;
    size_t needs = long_len(value);
    char *msg    = malloc(needs + 1);
    snprintf(msg, needs, "%ld", value);
    XtVaSetValues(label, XtNlabel, msg, NULL);
    free(msg);
}

static void
jump_cb(Widget widget _X_UNUSED, XtPointer label_ptr, XtPointer value_ptr)
{
    float value  = *(float *)value_ptr;
    Widget label = (Widget) label_ptr;
    size_t needs = float_len(value);
    char *msg    = malloc(needs + 1);
    snprintf(msg, needs, "%lf", value);
    XtVaSetValues(label, XtNlabel, msg, NULL);
    free(msg);
}

int main(int argc, char **argv)
{
    Widget toplevel, box, label, scroll, command;
    XtAppContext app_con;

    toplevel = XtAppInitialize(&app_con, "demo", NULL, 0,
                               &argc, argv, NULL,
                               NULL, 0);

    box = XtCreateManagedWidget("box", boxWidgetClass, toplevel, NULL, 0);

    label = XtVaCreateManagedWidget("Label",
                                    labelWidgetClass,
				    box, XtNlabel, "hello", NULL);

    command = XtVaCreateManagedWidget("cmd",
				      commandWidgetClass,  box,
				      XtNlabel, "EXIT",
				      NULL);

    XtAddCallback(command, XtNcallback, quit_cb, NULL);

    scroll = XtVaCreateManagedWidget("scroller",
				     scrollbarWidgetClass, box,
				     XtNorientation, XtorientHorizontal,
				     XtNlength, 500,
				     XtNwidth, 100,
				     NULL);

    XtAddCallback(scroll, XtNscrollProc, scroll_cb, label);
    XtAddCallback(scroll, XtNjumpProc, jump_cb, label);

    XtRealizeWidget(toplevel);

    XtAppMainLoop(app_con);

    exit(0);
}
