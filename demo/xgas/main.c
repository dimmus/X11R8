/*

Copyright (c) 1989  X Consortium

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
/*
 * main.c
 *   xgas: Copyright 1990 Larry Medwin: @(#)xgas.c	1.9 2/9/90
 *   Larry Medwin -- Dec 18, 1989
 *   Dave Sternlicht -- Dec 18 1990, ported from Xw to Xaw widget set.
 *   Dave Sternlicht -- Dec 20 1990, creation of the Gas widget.
 *   Larry Medwin -- April 5, 1991, added help stuff.
 */

#include "xgas.h"
#include "xgas.icon"
#include <X11/Shell.h>

#include <stdlib.h>
#include <stdio.h>

static String FallbackResources[] = {
"*lab.height: 300",
"*lab.width: 300",
"*Scrollbar.height: 300",
"*help.label: Missing app-defaults!",
NULL
};

#define Offset(field) XtOffsetOf(LabData, field)
static XtResource resources[] = {
  { "autoStart", "AutoStart", XtRBoolean, sizeof(Boolean),
      Offset(autoStart), XtRImmediate, (XtPointer)False},
  { "timestepSize", "TimestepSize", XtRFloat, sizeof(float),
      Offset(timestepSize), XtRString, "3.0" },
  { "delay", "Delay", XtRInt, sizeof(int),
      Offset(delay), XtRImmediate, (XtPointer) 50 },
  { "randomBounce", "RandomBounce", XtRFloat, sizeof(float),
      Offset(randomBounce), XtRString, "0.1" },
  { "equilibrium", "Equilibrium", XtRFloat, sizeof(float),
      Offset(equilibrium), XtRString, "0.5" },
  { "maxMolecules", "MaxMolecules", XtRInt, sizeof(int),
      Offset(maxMolecules), XtRImmediate, (XtPointer) 100 },
  { XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
      Offset(foreground), XtRString, XtDefaultForeground },
  { XtNbackground, XtCBackground, XtRPixel, sizeof(Pixel),
      Offset(background), XtRString, XtDefaultBackground },
};
#undef Offset

static XrmOptionDescRec optionDesc[] = {
  { "-as", "*autoStart",    XrmoptionNoArg,  (XtPointer)"on"},
  { "-ts", "*timestepSize", XrmoptionSepArg, (XtPointer)NULL },
  { "-d",  "*delay",        XrmoptionSepArg, (XtPointer)NULL },
  { "-rb", "*randomBounce", XrmoptionSepArg, (XtPointer)NULL },
  { "-eq", "*equilibrium",  XrmoptionSepArg, (XtPointer)NULL },
  { "-mm", "*maxMolecules", XrmoptionSepArg, (XtPointer)NULL },
  { "-fg", "*foreground",   XrmoptionSepArg, (XtPointer)NULL },
  { "-bg", "*background",   XrmoptionSepArg, (XtPointer)NULL },
};

/*
 *  Global array describing wall and corner geometry.
 *    wallReflect, toRotate, fromRotate
 *
 * Rotation Matrix is:
 *	[ cos theta	- sin theta ]
 *	[ sin theta	cos theta   ]
 */
WallType WallParam[] =	{
  /* Walls: */
  { 	{1,-1},  {{0,1},{-1,0}},  {{0,-1},{1,0}}},	/* TOP */
  {     {-1,1},  {{-1,0},{0,-1}},  {{-1,0},{0,-1}}},	/* RIGHT */
  { 	{1,-1},  {{0,-1},{1,0}},  {{0,1},{-1,0}}},	/* BOTTOM */
  { 	{-1,1},	 {{1,0},{0,1}},  {{1,0},{0,1}}},	/* LEFT */
  /* Corners: */
  { 	{-1,-1}, {{1,0},{0,1}},  {{1,0},{0,1}}},	/* NW */
  { 	{-1,-1}, {{0,-1},{1,0}},  {{0,1},{-1,0}}},	/* SW */
  { 	{-1,-1}, {{-1,0},{0,-1}},  {{-1,0},{0,-1}}},	/* SE */
  { 	{-1,-1}, {{0,1},{-1,0}},  {{0,-1},{1,0}}},	/* NE */
};

/*
 * Report the syntax for calling xgas.
 */
int
Syntax(char *call)
{
        (void) printf ("Usage: %s [-as] [-ts <microsec>] [-d <time>]\n", call);
        (void) printf ("       [-rb <randomfac>] [-eq <equilibriumfac>]\n");
        (void) printf ("       [-mm <numMolecules>] \n");
	(void) printf ("       [-fg <color>] [-bg <color>]\n");
        exit(1);
}

int
main( argc, argv )
     int argc;
     char *argv[];
{
  XtAppContext app;
  Widget toplevel;
  Widget frame;
  Widget run, pause, step, quit;	/* Push Buttons */
  Widget lab;
  Widget help;
  LabData labData;
  Arg wargs[3];
  int i;
  Pixmap icon;
  
  /* TOPLEVEL */
  toplevel = XtAppInitialize(&app, "XGas", optionDesc, XtNumber(optionDesc),
			     &argc, argv, FallbackResources, NULL, 
			     (Cardinal)0);
  
  /* Check parameters */
  if (argc != 1) Syntax(argv[0]);

  /* Get Resources */
  XtGetApplicationResources( toplevel, (XtPointer) &labData, resources,
			    XtNumber( resources), (ArgList)NULL, 0);
  
  /* Allocate dynamic arrays, now that we have maxMolecules */
  labData.molecules
    = (Molecule*) malloc( (unsigned)labData.maxMolecules
			 *sizeof(Molecule));
  labData.allPos
    = (XRectangle*) malloc((unsigned)labData.maxMolecules
			   *2*sizeof(XRectangle));
  
  /* FRAMEWORK */
  frame = XtCreateManagedWidget("frame", formWidgetClass,
				toplevel, NULL, 0);
  
  /* QUIT BUTTON */
  quit = XtVaCreateManagedWidget("quit", commandWidgetClass, frame,
				 NULL);
  XtAddCallback(quit, XtNcallback, quit_callback, (XtPointer)NULL);
  
  /* RUN BUTTON */
  run = XtVaCreateManagedWidget("run", toggleWidgetClass, frame, 
			        XtNfromHoriz, (XtPointer)quit,
			       XtNhorizDistance, 50,
				NULL);
  XtAddCallback(run, XtNcallback, run_callback, (XtPointer)&labData);
  
  /* PAUSE BUTTON */
  pause = XtVaCreateManagedWidget("pause", toggleWidgetClass, frame, 
				  XtNfromHoriz, (XtPointer)run,
				  XtNradioGroup, (XtPointer)run,
				  NULL);
  XtAddCallback(pause, XtNcallback, pause_callback, (XtPointer)&labData);
  
  /* STEP BUTTON */
  step = XtVaCreateManagedWidget("step", commandWidgetClass, frame,
				 XtNfromHoriz, (XtPointer)pause,
				 NULL);
  XtAddCallback(step, XtNcallback, oneTimestep, (XtPointer)&labData);
  
  /* HELP BUTTON */
  help = XtVaCreateManagedWidget("help", commandWidgetClass, frame,
				XtNfromHoriz, (XtPointer)step,
			       XtNhorizDistance, 50,
			       NULL);
  createHelpWidgets( help );
  
  /* TEMP CONTROL and TEMP DISPLAY */
  labData.chamber[0].control = 
    XtVaCreateManagedWidget("tempControl0", scrollbarWidgetClass, frame, 
			    XtNfromVert, (XtPointer)help,
			    NULL);

  /* LAB */
  lab = XtVaCreateManagedWidget("lab", gasWidgetClass, frame,
			   XtNfromHoriz, (XtPointer)labData.chamber[0].control,
			   XtNfromVert, (XtPointer)help,
			   NULL);
  XtAddCallback(lab, XtNresize, labResize, (XtPointer)&labData);
  
  labData.chamber[1].control = 
    XtVaCreateManagedWidget("tempControl1", scrollbarWidgetClass, frame, 
			    XtNfromHoriz, (XtPointer)lab,
			    XtNfromVert, (XtPointer)help,
			    NULL);

  XtAddCallback( labData.chamber[0].control, XtNjumpProc, 
		changeTemp, (XtPointer)&labData.chamber[0]);
  XtAddCallback( labData.chamber[1].control, XtNjumpProc, 
		changeTemp, (XtPointer)&labData.chamber[1]);


  labData.chamber[0].display = 
    XtVaCreateManagedWidget("tempDisplay0", labelWidgetClass, frame,
			    XtNfromVert, (XtPointer)labData.chamber[0].control,
			    XtNlabel, (XtPointer)" 300.0K ",
			    NULL);

  /* CLOCK DISPLAY */
  labData.clock = XtVaCreateManagedWidget("clock", labelWidgetClass, frame,
			   XtNfromHoriz, (XtPointer)labData.chamber[0].display,
			   XtNfromVert, (XtPointer)lab,
			   XtNlabel, (XtPointer)" 0.000 msec ",
			   NULL);
  
  labData.chamber[1].display = 
    XtVaCreateManagedWidget("tempDisplay1", labelWidgetClass, frame, 
			    XtNfromHoriz, (XtPointer)labData.clock,
			    XtNfromVert, (XtPointer)labData.chamber[1].control,
			    XtNlabel, " 300.0 K ",
			    NULL);

  /* Start things up. */
  
  /*   Need to create GC's before adding callbacks */
  labInit( lab, &labData);
  XtAddEventHandler(lab, ExposureMask, False, labExpose, (XtPointer)&labData);


  /* resize is handled through the resize callback in the gas widget. */
  XtCallCallbacks(lab, XtNresize, (XtPointer)&labData);

  XtAddEventHandler( lab, ButtonPressMask, FALSE,
		    addMolecules, (XtPointer)&labData);
  
  XtRealizeWidget( toplevel);

  /* initialize the scrollbar positions */
  for (i=0; i<2; i++)
    XawScrollbarSetThumb(labData.chamber[i].control, 
			 (float)INITTEMP / (float)MAXTEMP, -1.0);  

  /* Tell wm about icon */
  icon = XCreateBitmapFromData( XtDisplay(frame),
	       XtWindow(frame), (char *)xgas_bits, xgas_width, xgas_height);
  XtSetArg( wargs[0], XtNiconPixmap, icon);
  XtSetValues( toplevel, wargs, 1);
	   
  /* Figure out lab dimensions, create walls */

  /* Initialize temperature */
  XtCallCallbacks( labData.chamber[0].control, XtNscrollProc, (XtPointer)300);
  XtCallCallbacks( labData.chamber[1].control, XtNscrollProc, (XtPointer)300);

  if (labData.autoStart) {
    XEvent ev;
    Arg wargs[2];
    Dimension labW, labH;
    XtSetArg(wargs[0], XtNwidth, &labW);
    XtSetArg(wargs[1], XtNheight, &labH);
    XtGetValues(lab, wargs, 2);
    ev.xbutton.x = labW/2; ev.xbutton.y = labH/2; ev.xbutton.button = 2;
    addMolecules(lab, &labData, &ev);
    XtCallCallbacks( run, XtNcallback, (XtPointer)NULL);
  }
  XtAppMainLoop(app);
}