/*
 * $Id: Toggle.c,v 1.5 2000/08/31 17:06:58 falk Exp $
 * Based on Xaw3d v1.3
 * $XConsortium: Toggle.c,v 1.28 94/04/17 20:13:17 kaleb Exp $
 *
 * This version adds code from Ed Falk's "Checkbox" and "Radio"
 * widgets, and corresponding resource names from the neXtaw toolkit.
 */

/*

Copyright (c) 1989, 1994  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

 */

/*
 * Toggle.c - Toggle button widget
 *
 * Author: Chris D. Peterson
 *         MIT X Consortium 
 *         kit@expo.lcs.mit.edu
 *  
 * Date:   January 12, 1989
 *
 */

#include <stdio.h>

#include <X11/IntrinsicP.h>
#include <X11/StringDefs.h>
#include "XawInit.h"
#include <X11/Xmu/Converters.h>
#include <X11/Xmu/Misc.h>
#include <X11/Xmu/CharSet.h>
#include "ToggleP.h"
#include "TraversalP.h"

#define	BOX_SIZE	11
#define	DIAMOND_SIZE	11

/****************************************************************
 *
 * Full class record constant
 *
 ****************************************************************/

/* Private Data */

/* 
 * The order of toggle and notify are important, as the state has
 * to be set when we call the notify proc.
 */

static char defaultTranslations[] =
    "<EnterWindow>:	    FocusEnterWindow()	\n\
     <FocusIn>:		    highlight(Always)	\n\
     <LeaveWindow>:	    FocusLeaveWindow()	\n\
     <FocusOut>:	    unhighlight()	\n\
     <Btn1Down>,<Btn1Up>:   FocusTake() toggle() notify()	\n\
     Shift<Key>Tab:	    FocusPrevious()	\n\
     <Key>Tab:		    FocusNext()		\n\
     <Key>Home:		    FocusHome()		\n\
     <Key>End:		    FocusEnd()		\n\
     <Key>Up:		    FocusPreviousGroup() \n\
     <Key>Down:		    FocusNextGroup()	\n\
     <Key>KP_Home:	    FocusHome()		\n\
     <Key>KP_End:	    FocusEnd()		\n\
     <Key>KP_Up:	    FocusPreviousGroup() \n\
     <Key>KP_Down:	    FocusNextGroup()	\n\
     <KeyDown>space,<KeyUp>space: toggle() notify()";

#ifdef	COMMENT
static char defaultTranslations[] =
    "<EnterWindow>:	    FocusEnterWindow() highlight(Always)	\n\
     <FocusIn>:		    highlight(Always)	\n\
     <LeaveWindow>:	    FocusLeaveWindow() unhighlight()	\n\
     <FocusOut>:	    unhighlight()	\n\
     <Btn1Down>,<Btn1Up>:   FocusTake() toggle() notify()	\n\
     Shift<Key>Tab:	    FocusPrevious()	\n\
     <Key>Tab:		    FocusNext()		\n\
     <Key>Home:		    FocusHome()		\n\
     <Key>End:		    FocusEnd()		\n\
     <Key>Up:		    FocusPreviousGroup() \n\
     <Key>Down:		    FocusNextGroup()	\n\
     <Key>KP_Home:	    FocusHome()		\n\
     <Key>KP_End:	    FocusEnd()		\n\
     <Key>KP_Up:	    FocusPreviousGroup() \n\
     <Key>KP_Down:	    FocusNextGroup()	\n\
     <KeyDown>space,<KeyUp>space: toggle() notify()";
#endif	/* COMMENT */

#define offset(field) XtOffsetOf(ToggleRec, field)

static XtResource resources[] = { 
   {XtNstate, XtCState, XtRBoolean, sizeof(Boolean), 
      offset(command.set), XtRString, "off"},
   {XtNradioGroup, XtCWidget, XtRWidget, sizeof(Widget), 
      offset(toggle.widget), XtRWidget, (XtPointer) NULL },
   {XtNradioData, XtCRadioData, XtRPointer, sizeof(XtPointer), 
      offset(toggle.radio_data), XtRPointer, (XtPointer) NULL },
   {XtNtoggleStyle, XtCToggleStyle, XtRToggleStyle, sizeof(XtToggleStyle), 
      offset(toggle.toggle_style), XtRImmediate, (XtPointer) XtToggleSimple },
};

#undef offset


static void Toggle(), Initialize(), Notify(), ToggleSet(), ToggleUnset() ;
static void ToggleDestroy(), ClassInit();
static Boolean SetValues();
static void ToggleExpose(), ToggleResize();
static void ToggleSize() ;
static void ToggleHighlight() ;
static void ToggleUnhighlight() ;
static void DrawCheck(), DrawDiamond(), DrawButton() ;
static XtGeometryResult ToggleQueryGeometry() ;
static Boolean	_CvtStringToToggleStyle() ;

/* Functions for handling the Radio Group. */

static RadioGroup * GetRadioGroup();
static void CreateRadioGroup(), AddToRadioGroup(), TurnOffRadioSiblings();
static void RemoveFromRadioGroup();

static XtActionsRec actionsList[] =
{
  {"toggle",	        Toggle},
  {"notify",	        Notify},
  {"set",	        ToggleSet},
  {"unset",	        ToggleUnset},
  {"highlight",		ToggleHighlight},
  {"unhighlight",	ToggleUnhighlight},
};

#define SuperClass ((CommandWidgetClass)&commandClassRec)
#define	XtToggleClass(w)	(((ToggleWidgetClass)XtClass(w))->toggle_class)

static ToggleClassExtension toggleExtension ;

ToggleClassRec toggleClassRec = {
  {
    (WidgetClass) SuperClass,		/* superclass		  */	
    "Toggle",				/* class_name		  */
    sizeof(ToggleRec),			/* size			  */
    ClassInit,				/* class_initialize	  */
    NULL,				/* class_part_initialize  */
    FALSE,				/* class_inited		  */
    Initialize,				/* initialize		  */
    NULL,				/* initialize_hook	  */
    XtInheritRealize,			/* realize		  */
    actionsList,			/* actions		  */
    XtNumber(actionsList),		/* num_actions		  */
    resources,				/* resources		  */
    XtNumber(resources),		/* resource_count	  */
    NULLQUARK,				/* xrm_class		  */
    FALSE,				/* compress_motion	  */
    TRUE,				/* compress_exposure	  */
    TRUE,				/* compress_enterleave    */
    FALSE,				/* visible_interest	  */
    NULL,				/* destroy		  */
    ToggleResize,			/* resize		  */
    ToggleExpose,			/* expose		  */
    SetValues,				/* set_values		  */
    NULL,				/* set_values_hook	  */
    XtInheritSetValuesAlmost,		/* set_values_almost	  */
    NULL,				/* get_values_hook	  */
    XtInheritAcceptFocus,		/* accept_focus		  */
    XtVersion,				/* version		  */
    NULL,				/* callback_private	  */
    defaultTranslations,		/* tm_table		  */
    ToggleQueryGeometry,		/* query_geometry	  */
    XtInheritDisplayAccelerator,	/* display_accelerator	  */
    NULL				/* extension		  */
  },  /* CoreClass fields initialization */
  {
    XtInheritChangeSensitive		/* change_sensitive	  */ 
  },  /* SimpleClass fields initialization */
  {
    XtInheritXaw3dShadowDraw            /* shadowdraw          */
  },  /* ThreeDClass fields initialization */
  {
    0                                     /* field not used    */
  },  /* LabelClass fields initialization */
  {
    0                                     /* field not used    */
  },  /* CommandClass fields initialization */
  {
      ToggleSet,		        /* Set Procedure. */
      ToggleUnset,		        /* Unset Procedure. */
      ToggleHighlight,
      ToggleUnhighlight,
      (XtPointer)&toggleExtension,	/* extension. */
  }  /* ToggleClass fields initialization */
};

  /* for public consumption */
WidgetClass toggleWidgetClass = (WidgetClass) &toggleClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

static void
ClassInit()
{
  XtActionList actions;
  Cardinal num_actions;
  Cardinal i;
  ToggleWidgetClass class = (ToggleWidgetClass) toggleWidgetClass;
  static XtConvertArgRec parentCvtArgs[] = {
      {XtBaseOffset, (XtPointer)XtOffsetOf(WidgetRec, core.parent),
	   sizeof(Widget)}
  };

  XawInitializeWidgetSet();
  XtSetTypeConverter(XtRString, XtRWidget, XmuNewCvtStringToWidget,
		     parentCvtArgs, XtNumber(parentCvtArgs), XtCacheNone,
		     (XtDestructor)NULL);

  XtSetTypeConverter(XtRString, XtRToggleStyle,
	_CvtStringToToggleStyle, NULL, 0, XtCacheNone, NULL) ;

/* 
 * Find the set and unset actions in the command widget's action table. 
 * Also: highlight & unhighlight
 */

  XtGetActionList(commandWidgetClass, &actions, &num_actions);

  for (i = 0 ; i < num_actions ; i++) {
#ifdef	COMMENT
    if (streq(actions[i].string, "set"))
	class->toggle_class.Set = actions[i].proc;
    else if (streq(actions[i].string, "unset")) 
	class->toggle_class.Unset = actions[i].proc;
#endif	/* COMMENT */
    if (streq(actions[i].string, "set"))
	toggleExtension.Set = actions[i].proc;
    else if (streq(actions[i].string, "unset")) 
	toggleExtension.Unset = actions[i].proc;
    else if (streq(actions[i].string, "highlight")) 
	toggleExtension.Highlight = actions[i].proc;
    else if (streq(actions[i].string, "unhighlight")) 
	toggleExtension.Unhighlight = actions[i].proc;

    if ( (class->toggle_class.Set != NULL) &&
	 (class->toggle_class.Unset != NULL) &&
	 (toggleExtension.Highlight != NULL) &&
	 (toggleExtension.Unhighlight != NULL) ) {
	XtFree((char *) actions);
	return;
    }
  }  

/* We should never get here. */
  XtError("Aborting, due to errors resolving bindings in the Toggle widget.");
}

static void Initialize(request, new, args, num_args)
 Widget request, new;
 ArgList args;
 Cardinal *num_args;
{
    ToggleWidget tw = (ToggleWidget) new;
    ToggleWidget tw_req = (ToggleWidget) request;

    tw->toggle.radio_group = NULL;

    if (tw->toggle.radio_data == NULL) 
      tw->toggle.radio_data = (XtPointer) new->core.name;

    if (tw->toggle.widget != NULL) {
      if ( GetRadioGroup(tw->toggle.widget) == NULL) 
	CreateRadioGroup(new, tw->toggle.widget);
      else
	AddToRadioGroup( GetRadioGroup(tw->toggle.widget), new);
    }      
    XtAddCallback(new, XtNdestroyCallback, ToggleDestroy, (XtPointer)NULL);

/*
 * Command widget assumes that the widget is unset, so we only 
 * have to handle the case where it needs to be set.
 *
 * If this widget is in a radio group then it may cause another
 * widget to be unset, thus calling the notify proceedure.
 *
 * I want to set the toggle if the user set the state to "On" in 
 * the resource group, reguardless of what my ancestors did.
 */

    if (tw_req->command.set)
      XtToggleClass(new).Set(new, (XEvent *)NULL,
		(String *)NULL, (Cardinal *)0);

    /* Select initial size for the widget */
    if( tw->toggle.toggle_style != XtToggleSimple  &&
        (tw_req->core.width == 0  ||  tw_req->core.height == 0) )
    {
      Dimension w,h ;
      ToggleSize(tw, &w,&h) ;
      if( tw_req->core.width == 0 ) tw->core.width = w ;
      if( tw_req->core.height == 0 ) tw->core.height = h ;
      tw->core.widget_class->core_class.resize(new) ;
    }
}


/* React to size change from parent.  Label widget will compute some internal
 * stuff, but we need to override.  This code requires knowledge of the
 * internals of the Label widget.
 */

static	void
ToggleResize(w)
    Widget w ;
{
    ToggleWidget tw = (ToggleWidget)w ;
    Dimension	bs ;

    /* call parent resize proc */
    SuperClass->core_class.resize(w) ;
    if( tw->toggle.toggle_style == XtToggleSimple )
      return ;

    /* override label & bitmap offset */

    bs = BOX_SIZE + tw->label.internal_width ;

    switch( tw->label.justify ) {
      case XtJustifyLeft: break ;
      case XtJustifyRight: bs = 0 ; break ;
      case XtJustifyCenter: default: bs /= 2 ; break ;
    }

    tw->label.label_x += bs ;
    tw->label.lbm_x += bs ;
}


/*
 * Repaint the widget window.
 */

static	void
ToggleExpose(w, event, region)
    Widget	w ;
    XEvent	*event ;
    Region	region ;
{
    ToggleWidget tw = (ToggleWidget) w ;
    extern WidgetClass labelWidgetClass ;

    if( tw->toggle.toggle_style == XtToggleSimple )
    {
      /* call parent redraw proc */
      SuperClass->core_class.expose(w, event,region) ;
      return ;
    }

    /* Note: the Label widget examines the region to decide if anything
     * needs to be drawn.  I'm not sure that this is worth the effort,
     * but it bears thinking on.
     */

    /* Let label widget draw the label & bitmap.  */

    labelWidgetClass->core_class.expose(w,event,region) ;

    /* Finally, the button itself */

    DrawButton(w, region) ;
}




/************************************************************
 *
 *  Action Procedures
 *
 ************************************************************/

static void 
ToggleSet(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
    ToggleWidget	tw = (ToggleWidget) w ;
    /* ToggleWidgetClass	class = (ToggleWidgetClass) w->core.widget_class; */

    TurnOffRadioSiblings(w);

    if( tw->command.set )
      return ;

    if( tw->toggle.toggle_style == XtToggleSimple )
	toggleExtension.Set(w, event, NULL, 0) ;

    else
    {
	tw->command.set = TRUE ;
	if( XtIsRealized(w) )
	  DrawButton(w, NULL) ;
    }
}

static void 
ToggleUnset(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
    ToggleWidget	tw = (ToggleWidget) w ;
    /* ToggleWidgetClass	class = (ToggleWidgetClass) w->core.widget_class; */

    if( !tw->command.set )
      return ;

    if( tw->toggle.toggle_style == XtToggleSimple )
	toggleExtension.Unset(w, event, NULL, 0);

    else
    {
	tw->command.set = FALSE ;
	if( XtIsRealized(w) )
	  DrawButton(w, NULL) ;
    }
}

static void 
Toggle(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
  ToggleWidget tw = (ToggleWidget)w;

  if (tw->command.set) 
    XtToggleClass(w).Unset(w, event, params, num_params);
  else 
    XtToggleClass(w).Set(w, event, params, num_params);
}

static void Notify(w,event,params,num_params)
Widget w;
XEvent *event;
String *params;		/* unused */
Cardinal *num_params;	/* unused */
{
  ToggleWidget tw = (ToggleWidget) w;
  long antilint = tw->command.set;

  XtCallCallbacks( w, XtNcallback, (XtPointer) antilint );
}

/************************************************************
 *
 * Set specified arguments into widget
 *
 ***********************************************************/

static Boolean 
SetValues (current, request, new, args, num_args)
Widget current, request, new;
ArgList args;
Cardinal *num_args;
{
    ToggleWidget oldtw = (ToggleWidget) current;
    ToggleWidget tw = (ToggleWidget) new;
    ToggleWidget rtw = (ToggleWidget) request;

    if (oldtw->toggle.widget != tw->toggle.widget)
      XawToggleChangeRadioGroup(new, tw->toggle.widget);

    if (!tw->core.sensitive && oldtw->core.sensitive && rtw->command.set)
	tw->command.set = True;

    if (oldtw->command.set != tw->command.set) {
	tw->command.set = oldtw->command.set;
	Toggle(new, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
    }
    return(FALSE);
}


static XtGeometryResult
ToggleQueryGeometry(w, intended, preferred)
    Widget	w ;
    XtWidgetGeometry *intended, *preferred ;
{
    ToggleWidget tw = (ToggleWidget) w ;
    XtGeometryResult rval ;

    rval = SuperClass->core_class.query_geometry(w, intended, preferred) ;

    if( tw->toggle.toggle_style == XtToggleSimple )
      return rval ;

    /* override superclass's preferred size to allow room for the
     * checkbox.
     */

    preferred->width += BOX_SIZE + tw->label.internal_width ;
    preferred->height = Max(BOX_SIZE, preferred->height) ;

    if( (!(intended->request_mode & CWWidth) ||
	intended->width == preferred->width)	&&
	(!(intended->request_mode & CWHeight) ||
	intended->height == preferred->height) )
      return XtGeometryYes;

    else if (preferred->width == w->core.width &&
	     preferred->height == w->core.height)
      return XtGeometryNo;

    else
      return XtGeometryAlmost;
}

/*	Function Name: ToggleDestroy
 *	Description: Destroy Callback for toggle widget.
 *	Arguments: w - the toggle widget that is being destroyed.
 *                 junk, grabage - not used.
 *	Returns: none.
 */

static void
ToggleDestroy(w, junk, garbage)
Widget w;
XtPointer junk, garbage;
{
  RemoveFromRadioGroup(w);
}

/************************************************************
 *
 * Below are all the private procedures that handle 
 * radio toggle buttons.
 *
 ************************************************************/

/*	Function Name: GetRadioGroup
 *	Description: Gets the radio group associated with a give toggle
 *                   widget.
 *	Arguments: w - the toggle widget who's radio group we are getting.
 *	Returns: the radio group associated with this toggle group.
 */

static RadioGroup *
GetRadioGroup(w)
Widget w;
{
  ToggleWidget tw = (ToggleWidget) w;

  if (tw == NULL) return(NULL);
  return( tw->toggle.radio_group );
}

/*	Function Name: CreateRadioGroup
 *	Description: Creates a radio group. give two widgets.
 *	Arguments: w1, w2 - the toggle widgets to add to the radio group.
 *	Returns: none.
 * 
 *      NOTE:  A pointer to the group is added to each widget's radio_group
 *             field.
 */

static void
CreateRadioGroup(w1, w2)
Widget w1, w2;
{
  char error_buf[BUFSIZ];
  ToggleWidget tw1 = (ToggleWidget) w1;
  ToggleWidget tw2 = (ToggleWidget) w2;

  if ( (tw1->toggle.radio_group != NULL) || (tw2->toggle.radio_group != NULL) ) 
  {
    (void) sprintf(error_buf, "%s %s", "Toggle Widget Error - Attempting",
	    "to create a new toggle group, when one already exists.");
    XtWarning(error_buf);
  }

  AddToRadioGroup( (RadioGroup *)NULL, w1 );
  AddToRadioGroup( GetRadioGroup(w1), w2 );
}

/*	Function Name: AddToRadioGroup
 *	Description: Adds a toggle to the radio group.
 *	Arguments: group - any element of the radio group the we are adding to.
 *                 w - the new toggle widget to add to the group.
 *	Returns: none.
 */

static void
AddToRadioGroup(group, w)
RadioGroup * group;
Widget w;
{
  ToggleWidget tw = (ToggleWidget) w;
  RadioGroup * local;

  local = (RadioGroup *) XtMalloc( sizeof(RadioGroup) );
  local->widget = w;
  tw->toggle.radio_group = local;

  if (group == NULL) {		/* Creating new group. */
    group = local;
    group->next = NULL;
    group->prev = NULL;
    return;
  }
  local->prev = group;		/* Adding to previous group. */
  if ((local->next = group->next) != NULL)
      local->next->prev = local;
  group->next = local;
}

/*	Function Name: TurnOffRadioSiblings
 *	Description: Deactivates all radio siblings.
 *	Arguments: widget - a toggle widget.
 *	Returns: none.
 */

static void
TurnOffRadioSiblings(w)
Widget w;
{
  RadioGroup * group;
  /* ToggleWidgetClass class ; */

  if ( (group = GetRadioGroup(w)) == NULL)  /* Punt if there is no group */
    return;

  /* Go to the top of the group. */

  for ( ; group->prev != NULL ; group = group->prev );

  while ( group != NULL ) {
    ToggleWidget local_tog = (ToggleWidget) group->widget;
    if ( local_tog->command.set ) {
      /* class = (ToggleWidgetClass) group->widget->core.widget_class; */
      XtToggleClass(w).Unset(group->widget, NULL, NULL, 0);
      Notify( group->widget, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
    }
    group = group->next;
  }
}

/*	Function Name: RemoveFromRadioGroup
 *	Description: Removes a toggle from a RadioGroup.
 *	Arguments: w - the toggle widget to remove.
 *	Returns: none.
 */

static void
RemoveFromRadioGroup(w)
Widget w;
{
  RadioGroup * group = GetRadioGroup(w);
  if (group != NULL) {
    if (group->prev != NULL)
      (group->prev)->next = group->next;
    if (group->next != NULL)
      (group->next)->prev = group->prev;
    XtFree((char *) group);
  }
}

/************************************************************
 *
 * Public Routines
 *
 ************************************************************/
   
/*	Function Name: XawToggleChangeRadioGroup
 *	Description: Allows a toggle widget to change radio groups.
 *	Arguments: w - The toggle widget to change groups.
 *                 radio_group - any widget in the new group.
 *	Returns: none.
 */

void
#if NeedFunctionPrototypes
XawToggleChangeRadioGroup(Widget w, Widget radio_group)
#else
XawToggleChangeRadioGroup(w, radio_group)
Widget w, radio_group;
#endif
{
  ToggleWidget tw = (ToggleWidget) w;
  RadioGroup * group;

  RemoveFromRadioGroup(w);

/*
 * If the toggle that we are about to add is set then we will 
 * unset all toggles in the new radio group.
 */

  if ( tw->command.set && radio_group )
    XawToggleUnsetCurrent(radio_group);

  if (radio_group) {
      if ((group = GetRadioGroup(radio_group)) == NULL)
	      CreateRadioGroup(w, radio_group);
      else 
        AddToRadioGroup(group, w);
}

/*	Function Name: XawToggleGetCurrent
 *	Description: Returns the RadioData associated with the toggle
 *                   widget that is currently active in a toggle group.
 *	Arguments: w - any toggle widget in the toggle group.
 *	Returns: The XtNradioData associated with the toggle widget.
 */

XtPointer
#if NeedFunctionPrototypes
XawToggleGetCurrent(Widget w)
#else
XawToggleGetCurrent(w)
Widget w;
#endif
{
  RadioGroup * group;

  if ( (group = GetRadioGroup(w)) == NULL) return(NULL);
  for ( ; group->prev != NULL ; group = group->prev);

  while ( group != NULL ) {
    ToggleWidget local_tog = (ToggleWidget) group->widget;
    if ( local_tog->command.set )
      return( local_tog->toggle.radio_data );
    group = group->next;
  }
  return(NULL);
}

/*	Function Name: XawToggleSetCurrent
 *	Description: Sets the Toggle widget associated with the
 *                   radio_data specified.
 *	Arguments: radio_group - any toggle widget in the toggle group.
 *                 radio_data - radio data of the toggle widget to set.
 *	Returns: none.
 */

void
#if NeedFunctionPrototypes
XawToggleSetCurrent(Widget radio_group, XtPointer radio_data)
#else
XawToggleSetCurrent(radio_group, radio_data)
Widget radio_group;
XtPointer radio_data;
#endif
{
  RadioGroup * group;
  ToggleWidget local_tog; 

/* Special case of no radio group. */

  if ( (group = GetRadioGroup(radio_group)) == NULL) {
    local_tog = (ToggleWidget) radio_group;
    if ( (local_tog->toggle.radio_data == radio_data) )     
      if (!local_tog->command.set) {
	XtToggleClass(local_tog).Set((Widget) local_tog, (XEvent *)NULL,
				(String *)NULL, (Cardinal *)0);
	Notify((Widget) local_tog, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
      }
    return;
  }

/*
 * find top of radio_roup 
 */

  for ( ; group->prev != NULL ; group = group->prev);

/*
 * search for matching radio data.
 */

  while ( group != NULL ) {
    local_tog = (ToggleWidget) group->widget;
    if ( (local_tog->toggle.radio_data == radio_data) ) {
      if (!local_tog->command.set) { /* if not already set. */
	XtToggleClass(local_tog).Set((Widget) local_tog, (XEvent *)NULL,
			(String *)NULL, (Cardinal *)0);
	Notify((Widget) local_tog, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
      }
      return;			/* found it, done */
    }
    group = group->next;
  }
}
 
/*	Function Name: XawToggleUnsetCurrent
 *	Description: Unsets all Toggles in the radio_group specified.
 *	Arguments: radio_group - any toggle widget in the toggle group.
 *	Returns: none.
 */

void
#if NeedFunctionPrototypes
XawToggleUnsetCurrent(Widget radio_group)
#else
XawToggleUnsetCurrent(radio_group)
Widget radio_group;
#endif
{
  ToggleWidgetClass class;
  ToggleWidget local_tog = (ToggleWidget) radio_group;

  /* Special Case no radio group. */

  if (local_tog->command.set) {
    class = (ToggleWidgetClass) local_tog->core.widget_class;
    class->toggle_class.Unset(radio_group, NULL, NULL, 0);
    Notify(radio_group, (XEvent *)NULL, (String *)NULL, (Cardinal *)0);
  }
  if ( GetRadioGroup(radio_group) == NULL) return;
  TurnOffRadioSiblings(radio_group);
}






	/* New procedures added by Ed Falk to handle checkbox and radio
	 * styles
	 */


/*
 * Draw the highlight border around the widget.  The Command widget
 * did this by drawing through a mask.  We do it by just drawing the
 * border.
 */

static void 
DrawHighlight(w,gc)
    Widget w;
    GC gc ;
{
	ToggleWidget	tw = (ToggleWidget)w;
	XRectangle	rects[4] ;
	Dimension	ht = tw->command.highlight_thickness ;

	if( ht <= 0 || ht > tw->core.width/2  || ht > tw->core.height/2 )
	  return ;

	if( ! XtIsRealized(w) )
	  return ;

	rects[0].x = 0 ; rects[0].y = 0 ;
	rects[0].width = tw->core.width ; rects[0].height = ht ;
	rects[1].x = 0 ; rects[1].y = tw->core.height - ht ;
	rects[1].width = tw->core.width ; rects[1].height = ht ;
	rects[2].x = 0 ; rects[2].y = ht ;
	rects[2].width = ht ; rects[2].height = tw->core.height - ht*2 ;
	rects[3].x = tw->core.width - ht ; rects[3].y = ht ;
	rects[3].width = ht ; rects[3].height = tw->core.height - ht*2 ;
	XFillRectangles( XtDisplay(w), XtWindow(w), gc, rects, 4) ;
}

static	void
ToggleHighlight(w,event,params,num_params)
    Widget	w ;
    XEvent	*event ;
    String	*params ;
    Cardinal	*num_params ;
{
    ToggleWidget	tw = (ToggleWidget)w;
    if( tw->toggle.toggle_style == XtToggleSimple )
      toggleExtension.Highlight(w,event,params,num_params) ;
    else
      DrawHighlight(w, tw->command.normal_GC) ;
}


static	void
ToggleUnhighlight(w,event,params,num_params)
    Widget	w ;
    XEvent	*event ;
    String	*params ;
    Cardinal	*num_params ;
{
    ToggleWidget	tw = (ToggleWidget)w;
    if( tw->toggle.toggle_style == XtToggleSimple )
      toggleExtension.Unhighlight(w,event,params,num_params) ;
    else
      DrawHighlight(w, tw->command.inverse_GC) ;
}



static	void
DrawDiamond(w)
    Widget	w ;
{
	ToggleWidget	tw = (ToggleWidget) w ;
	Display		*dpy = XtDisplay(w) ;
	Window		win = XtWindow(w) ;

	XPoint		pts[5] ;
	Dimension	del = DIAMOND_SIZE/2 ;
	Dimension	s = tw->threeD.shadow_width ;
	int		i ;
	Position	x,y ;		/* diamond center */
	GC		top, bot, ctr ;

	x = tw->label.internal_width + DIAMOND_SIZE/2 ;
	y = tw->core.height/2 ;

	if( ! tw->command.set ) {
	  top = tw->threeD.top_shadow_GC ;
	  bot = tw->threeD.bot_shadow_GC ;
	  ctr = tw->command.inverse_GC ;
	} else {
	  top = tw->threeD.bot_shadow_GC ;
	  bot = tw->threeD.top_shadow_GC ;
	  ctr = tw->threeD.arm_GC ;
	}

	pts[0].x = x - del ;
	pts[0].y = y ;
	pts[1].x = x ;
	pts[1].y = y - del ;
	pts[2].x = x + del ;
	pts[2].y = y ;
	pts[3].x = x ;
	pts[3].y = y + del ;
	pts[4] = pts[0] ;
	XFillPolygon(dpy,win,ctr, pts,4, Convex, CoordModeOrigin) ;

	for(i=0; i<s; ++i) {
	  XDrawLine(dpy,win,bot, x-i-del,y, x,y+del+i) ;
	  XDrawLine(dpy,win,bot, x+del+i,y, x,y+del+i) ;
	}
	for(i=0; i<s; ++i) {
	  XDrawLine(dpy,win,top, x-del-i,y, x,y-del-i) ;
	  XDrawLine(dpy,win,top, x+del+i,y, x,y-del-i) ;
	}
}


	/* Draw a checkbox */

static	void
DrawCheck(w, region)
    Widget	w ;
    Region	region ;
{
	ToggleWidget	tw = (ToggleWidget) w ;
	Display		*dpy = XtDisplay(w) ;
	Window		win = XtWindow(w) ;
	Dimension	s = Min(tw->threeD.shadow_width, BOX_SIZE/2) ;
	Position	bx,by ;		/* Check upper-left */
	Dimension	bw,bh ;
	GC		ctr ;

	bw = bh = BOX_SIZE - 2*s ;
	bx = tw->label.internal_width + s ;
	by = tw->core.height/2 - BOX_SIZE/2 + s ;

	ctr = tw->command.set ? tw->threeD.arm_GC : tw->command.inverse_GC ;

	XFillRectangle(dpy,win,ctr, bx,by, bw,bh) ;

	Xaw3dDrawThreeDRectangle(w, &tw->threeD, region,
		bx,by, bx+bw, by+bh, s, !tw->command.set) ;
}


static	void
DrawButton(w, region)
    Widget w ;
    Region	region ;
{
    ToggleWidget	tw = (ToggleWidget) w ;

    if( tw->toggle.toggle_style == XtToggleRadio ||
	      (tw->toggle.toggle_style == XtToggleAuto &&
	      tw->toggle.radio_group != NULL) )
      DrawDiamond(w) ;
    else
      DrawCheck(w, region) ;
}


/* Size of widget.  Width is size of box plus width of border around
 * box plus width of label plus three margins plus the size of the left
 * bitmap, if any.  Height is max(box,bitmap,label) plus two margins.
 */

static	void
ToggleSize(tw, w,h)
    ToggleWidget	tw ;
    Dimension	*w, *h ;
{
    Dimension bs = BOX_SIZE ;

    *w = tw->label.label_width + bs + LEFT_OFFSET(tw) +
	    3 * tw->label.internal_width ;
    *h = Max( tw->label.label_height, bs) +
	    2 * tw->label.internal_width ;
}


static	Boolean
_CvtStringToToggleStyle(dpy, args, num_args, fromVal, toVal, converter_data)
	Display		*dpy ;
	XrmValuePtr	args ;
	Cardinal	*num_args ;
	XrmValuePtr	fromVal ;
	XrmValuePtr	toVal ;
	XtPointer	*converter_data ;
{
	String		str = (String) fromVal->addr ;

	if( XmuCompareISOLatin1(str,"ToggleSimple") == 0  ||
	    XmuCompareISOLatin1(str,"Simple") == 0 )
	  *(XtToggleStyle *)toVal->addr = XtToggleSimple ;
	else if( XmuCompareISOLatin1(str,"ToggleCheck") == 0  ||
		 XmuCompareISOLatin1(str,"Check") == 0 )
	  *(XtToggleStyle *)toVal->addr = XtToggleCheck ;
	else if( XmuCompareISOLatin1(str,"ToggleRadio") == 0  ||
		 XmuCompareISOLatin1(str,"Radio") == 0 ||
		 XmuCompareISOLatin1(str,"ToggleDiamond") == 0 ||
		 XmuCompareISOLatin1(str,"Diamond") == 0 )
	  *(XtToggleStyle *)toVal->addr = XtToggleRadio ;
	else if( XmuCompareISOLatin1(str,"ToggleAuto") == 0  ||
		 XmuCompareISOLatin1(str,"Auto") == 0 )
	  *(XtToggleStyle *)toVal->addr = XtToggleAuto ;
	else {
	  XtStringConversionWarning(fromVal->addr, "toggleStyle");
	  return False ;
	}
	return True ;
}
