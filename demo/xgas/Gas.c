/* $XConsortium: Gas.c,v 1.3 94/04/17 20:45:25 rws Exp $ */
/*

Copyright (c) 1987, 1988  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include "GasP.h"

static XtResource resources[] = {
#define offset(field) XtOffset(GasWidget, gas.field)
    /* {name, class, type, size, offset, default_type, default_addr}, */
/*    { XtNgasResource, XtCGasResource, XtRGasResource, sizeof(char*),*/
/*	  offset(resource), XtRString, "default" },*/
    { XtNresize, XtCCallback, XtRCallback, sizeof(char*),
	  offset(resource), XtRPointer, NULL },
#undef offset
};

static void GasAction(/* Widget, XEvent*, String*, Cardinal* */);
static void Resize();

static XtActionsRec actions[] =
{
  /* {name, procedure}, */
    {"gas",	GasAction},
};

static char translations[] =
"<Key>:		gas()	\n\
";

GasClassRec gasClassRec = {
  { /* core fields */
    /* superclass		*/	(WidgetClass) &widgetClassRec,
    /* class_name		*/	"Gas",
    /* widget_size		*/	sizeof(GasRec),
    /* class_initialize		*/	NULL,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	NULL,
    /* initialize_hook		*/	NULL,
    /* realize			*/	XtInheritRealize,
    /* actions			*/	actions,
    /* num_actions		*/	XtNumber(actions),
    /* resources		*/	resources,
    /* num_resources		*/	XtNumber(resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	NULL,
    /* resize			*/	Resize,
    /* expose			*/	NULL,
    /* set_values		*/	NULL,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	translations,
    /* query_geometry		*/	XtInheritQueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
  },
  { /* gas fields */
    /* empty			*/	0
  }
};

WidgetClass gasWidgetClass = (WidgetClass)&gasClassRec;

static void
GasAction(w, event, params, num_params)			/* ARGSUSED */
     Widget w;
     XEvent *event;
     String *params;		/* unused */
     Cardinal *num_params;	/* unused */
{
  XtCallCallbacks(w, XtNcallback, (caddr_t)event);
}

static void
Resize(w)
Widget w;
{
  XtCallCallbacks(w, XtNresize, NULL);
}