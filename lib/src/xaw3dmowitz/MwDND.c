/*
Copyright (C) 1996 C�sar Crusius

This file is part of the DND Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* #define DEBUG */

#include "MwDND.h"
#include <X11/cursorfont.h>
#include <X11/Xatom.h>
#include <X11/Xmu/WinUtil.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Local variables */
static Display		*dpy;		/* current display		*/
static XButtonEvent	StartEvent;	/* event that started the drag	*/
static int		DragPrecision;	/* minimum dx,dy to start drag	*/
static int		Dragging;	/* Drag state flag		*/
static int		DataOK;		/* Non-zero if data registered	*/
static Atom		MwDndProtocol;	/* ClientMessage identifier	*/
static Atom		MwDndSelection;	/* For the data transfers	*/
static Atom             OldDndProtocol; /* Version 0 atom               */
static Atom             OldDndSelection;/* Version 0 atom               */
static Atom		WM_STATE;	/* Needed for icon stuff	*/
static Window		Target;		/* Drop window			*/
static Widget		MainWidget;	/* Main widget of application	*/
static int		DataType;	/* Current drag data type	*/
static XtEventHandler	OtherDrop;	/* Drop on non-reg app widget	*/
static XtEventHandler	RootDrop;	/* How to handle root drops	*/
static XtEventHandler	IconDrop;	/* How to handle icon drops	*/
static int		RootFlag;	/* Non-zero if dropped on root	*/
static long             LastDropVersion;/* Last drop protocol version   */
static XColor	        Black,White;    /* For the cursors              */

/*=========================================================================
 * Data for the standard Dnd cursors
 *=========================================================================*/
#include "cursor/file.xbm"
#include "cursor/file_mask.xbm"
#include "cursor/files.xbm"
#include "cursor/files_mask.xbm"
#include "cursor/dir.xbm"
#include "cursor/dir_mask.xbm"
#include "cursor/text.xbm"
#include "cursor/text_mask.xbm"
#include "cursor/grey.xbm"
#include "cursor/grey_mask.xbm"
#include "cursor/link.xbm"
#include "cursor/link_mask.xbm"
#include "cursor/app.xbm"
#include "cursor/app_mask.xbm"
#include "cursor/url.xbm"
#include "cursor/url_mask.xbm"
#include "cursor/mime.xbm"
#include "cursor/mime_mask.xbm"

/*=============================================================== CursorData
 * CursorData contains all the data for the cursors bitmaps 
 *==========================================================================*/ 
typedef struct
{	
    int	Width,Height;
    char	*ImageData,*MaskData;
    int	HotSpotX,HotSpotY;
    Pixmap	ImagePixmap,MaskPixmap;
    Cursor	CursorID;
} CursorData;

static CursorData DndCursor[MW_DndEND]={
  { 0,0,NULL,NULL,0,0,0 },
  { grey_width,	grey_height,(char *)grey_bits,(char *)grey_mask_bits,
    grey_x_hot,grey_y_hot},
  { file_width,file_height,(char *)file_bits,(char *)file_mask_bits,
    file_x_hot,file_y_hot},
  { files_width,files_height,(char *)files_bits,(char *)files_mask_bits,
    files_x_hot,files_y_hot},
  { text_width,text_height,(char *)text_bits,(char *)text_mask_bits,
    text_x_hot,text_y_hot },
  { dir_width,dir_height,(char *)dir_bits,(char *)dir_mask_bits,
    dir_x_hot,dir_y_hot },
  { link_width,link_height,(char *)link_bits,(char *)link_mask_bits,
    link_x_hot,link_y_hot},
  { app_width,app_height,(char *)app_bits,(char *)app_mask_bits,
    app_x_hot,app_y_hot },
  { url_width,url_height,(char *)url_bits,(char *)url_mask_bits,
    url_x_hot,url_y_hot },
  { mime_width,mime_height,(char *)mime_bits,(char *)mime_mask_bits,
    mime_x_hot,mime_y_hot }  
};

/* Local prototypes */
int  MwDndIsDragging(void);
void MwDndSenderWarning(void);
void MwDndStartAction(Widget widget,
		    XtPointer data,
		    XEvent *event,
		    Boolean *p);
void MwDndDispatchEvent(Widget widget,
		      XtPointer data,
		      XEvent *event,
		      Boolean* p);
void MwDndPropertyHandler(Widget widget,
			XtPointer data,
			XEvent *event,
			Boolean *p);
Widget MwDndGetMainWidget(Widget widget);

/*========================================================== DndSenderWarning
 * Issues a warning in Stderr for older versions
 *===========================================================================*/
void MwDndSenderWarning(void)
{
    fprintf(stderr,"DND warning: sender using an old DND protocol.\n"
	    "You should modify/recompile the sender for the new DND\n"
	    "version.\n");
}


/*========================================================== DndStartAction
 * Initializes the drag and drop structures. Binded to ButtonPress event in
 * registered drag widgets.
 *=========================================================================*/
void MwDndStartAction(Widget widget,XtPointer data,XEvent *event,Boolean *p)
{
    StartEvent=*((XButtonEvent *)event);
    Dragging=0; DataOK=0;
}

/*======================================================== DndHandleDragging
 * Takes care of the drag and drop process. Wait until the pointer had moved
 * a little. Then takes control over the pointer until the buttons are
 * released. After that send a Drag And Drop ClientMessage event. Returns
 * non-zero if a drop did take place.
 *===========================================================================*/
int MwDndHandleDragging(Widget widget,XEvent *event)
{
    XEvent Event;
    Window root	= RootWindowOfScreen(XtScreenOfObject(widget));
    XtAppContext app= XtWidgetToApplicationContext(widget);
    Window  DispatchWindow;
    int DropX,DropY;
	
    if(Dragging) return 0;
    if(abs(StartEvent.x_root - event->xmotion.x_root) < DragPrecision && 
       abs(StartEvent.y_root - event->xmotion.y_root) < DragPrecision)
	return 0;
	
    XUngrabPointer(dpy,CurrentTime);
    /* Take control over the pointer */
    XGrabPointer(dpy,root,False,
		 ButtonMotionMask|ButtonPressMask|ButtonReleaseMask,
		 GrabModeSync,GrabModeAsync,root,
		 DndCursor[DataType].CursorID,
		 CurrentTime);

    /* Wait for button release */
    Dragging=1; RootFlag=0;
    while(Dragging)
    {
	XAllowEvents(dpy,SyncPointer,CurrentTime);
	XtAppNextEvent(app,&Event);
	switch(Event.type)
	{
	case ButtonRelease:
	    if(Event.xbutton.subwindow)
		RootFlag=0;
	    else
		RootFlag=1;
	    Dragging=0;
	    break;
	default:
	    XtDispatchEvent(&Event);
	    break;
	}
    }
    DataOK=0;
    /* Now release the pointer */
    XUngrabPointer(dpy,CurrentTime);
    /* Try to guess if the drop occurred in the root window */
    if(!RootFlag)
    {
	Target=XmuClientWindow(dpy,Event.xbutton.subwindow);
	if(Target==Event.xbutton.subwindow)
	    DispatchWindow=Target;
	else
	    DispatchWindow=PointerWindow;
    }
    else
	Target=DispatchWindow=XtWindow(MwDndGetMainWidget(widget));
	
    /* Now build the event structure */
    DropX=Event.xbutton.x_root;
    DropY=Event.xbutton.y_root;
    Event.xclient.type		= ClientMessage;
    Event.xclient.display		= dpy;
    Event.xclient.message_type	= MwDndProtocol;
    Event.xclient.format		= 32;
    Event.xclient.window		= Target;
    Event.xclient.data.l[0]		= DataType;
    Event.xclient.data.l[1]		= (long)event->xbutton.state;
    Event.xclient.data.l[2]		= (long)XtWindow(widget);
    Event.xclient.data.l[3]		= DropX + 65536L*(long)DropY;
    Event.xclient.data.l[4]		= 1;
	
    /* Send the drop message */
    XSendEvent(dpy,DispatchWindow,True,NoEventMask,&Event);
    /* Send an old style version of the message just in case */
    Event.xclient.message_type = OldDndProtocol;
    XSendEvent(dpy,DispatchWindow,True,NoEventMask,&Event);
    
#ifdef DEBUG
    fprintf(stderr,"ClientMessage sent to 0x%x(0x%x).\n",
	    DispatchWindow,Target);
    fprintf(stderr,"The drop coordinates are (%d,%d).\n",DropX,DropY);
    
#endif
    return 1;
}

/*======================================================== DndDispatchEvent
 * This function receives the Dnd ClientMessage event and dispatch it to
 * the correct widget. Binded to the top level widget by DndInitialize.
 *========================================================================*/
void
MwDndDispatchEvent(Widget widget,XtPointer data,XEvent *event,Boolean* p)
{
#ifdef DEBUG
    fprintf(stderr,"Message received! Target 0x%x\n",Target);
#endif
	
    if(!MwDndIsDropMessage(event)) return;
    /* Updates the "LastDropVersion" for our control */
    LastDropVersion=MwDndProtocolVersion(event);
    if(LastDropVersion < __DragAndDropH__)
	MwDndSenderWarning();

    /* So we have a Drop event. Now we must re-dispatch it to
     * the correct window.
     */
#ifdef DEBUG
    fprintf(stderr,"It is a DND protocol message!\n");
#endif
	
    /* Drop in the root window: dispatch to app's rootdrop handler. */
    if(RootFlag)
    {
	if(RootDrop!=NULL) RootDrop(widget,data,event,p);
	RootFlag=0;
	return;
    }
    RootFlag=0;

    /* Drop in the icon or in a widget that is not registered */
    if(!Target)
    {	
	/* Are we iconified ? Take the according action */
	if(MwDndIsIcon(widget) && IconDrop!=NULL)
	    IconDrop(widget,data,event,p);
	if(!MwDndIsIcon(widget) && OtherDrop!=NULL)
	    OtherDrop(widget,data,event,p);
	return;
    }
	
    /* Drop in a registered widget */
    if(XtWindow(widget)==Target)
    {	if(OtherDrop!=NULL) OtherDrop(widget,data,event,p);
    return;
    }
    event->xclient.window = Target;
    XSendEvent(dpy,Target,True,NoEventMask,event);
}

/*=============================================================== DndIsIcon
 * Return non-zero if the application is iconic (widget=toplevel)
 *========================================================================*/
int
MwDndIsIcon(Widget widget)
{
    Atom JunkAtom;
    int JunkInt;
    unsigned long WinState,JunkLong;
    unsigned char *Property;
		
    XGetWindowProperty(dpy,XtWindow(widget),WM_STATE,
		       0L,2L,False,AnyPropertyType,
		       &JunkAtom,&JunkInt,&WinState,&JunkLong,
		       &Property);
    WinState=(unsigned long)(*((long*)Property));
    return (WinState==3);
}

/*============================================================ DndInitialize
 * Must be called anywhere before the top level widget creation and the
 * main loop. Initialize global variables and bind the DndDispatch function
 * to the top level widget. Creates the cursors to be used in drag actions.
 *=========================================================================*/
void
MwDndInitialize(Widget shell)
{
    int	 screen,i;
    Colormap colormap;
    Window	 root;

    dpy	= XtDisplayOfObject(shell);
    screen	= DefaultScreen(dpy);
    colormap= DefaultColormap(dpy,screen);
    root	= DefaultRootWindow(dpy);
		

    Black.pixel=BlackPixel(dpy,screen);
    White.pixel=WhitePixel(dpy,screen);
    XQueryColor(dpy,colormap,&Black);
    XQueryColor(dpy,colormap,&White);
	
    for(i=1;i!=MW_DndEND;i++)
    {
	DndCursor[i].ImagePixmap=
	    XCreateBitmapFromData(dpy,root,
				  DndCursor[i].ImageData,
				  DndCursor[i].Width,
				  DndCursor[i].Height);
	DndCursor[i].MaskPixmap=
	    XCreateBitmapFromData(dpy,root,
				  DndCursor[i].MaskData,
				  DndCursor[i].Width,
				  DndCursor[i].Height);
	DndCursor[i].CursorID=
	    XCreatePixmapCursor(dpy,DndCursor[i].ImagePixmap,
				DndCursor[i].MaskPixmap,
				&Black,&White,
				DndCursor[i].HotSpotX,
				DndCursor[i].HotSpotY);
    }
	
    DndCursor[0].CursorID=XCreateFontCursor(dpy,XC_question_arrow);
	
    /* These two are for older versions */
    OldDndProtocol=XInternAtom(dpy,"DndProtocol",FALSE);
    OldDndSelection=XInternAtom(dpy,"DndSelection",FALSE);
    /* Now the correct stuff */
    MwDndProtocol=XInternAtom(dpy,"_DND_PROTOCOL",FALSE);
    MwDndSelection=XInternAtom(dpy,"_DND_SELECTION",FALSE);
    
    WM_STATE=XInternAtom(dpy,"WM_STATE",True);
    Dragging=0;
    DragPrecision=10;
    XtAddEventHandler(shell,NoEventMask,True,MwDndDispatchEvent,NULL);
    OtherDrop=RootDrop=IconDrop=NULL;
    RootFlag=0;
    MainWidget=shell;
}

/*============ DndRegisterRootDrop, DndRegisterIconDrop, DndRegisterOtherDrop
 * Register the application for "unusual" drops.
 *==========================================================================*/
void MwDndRegisterRootDrop(XtEventHandler handler)   { RootDrop=handler; }
void MwDndRegisterIconDrop(XtEventHandler handler)   { IconDrop=handler; }
void MwDndRegisterOtherDrop(XtEventHandler handler)  { OtherDrop=handler; }

/*======================= DndMultipleShells and DndAddShell (DndGetMainWidget)
 * An attempt to make DND compatible with multiple-window applications.
 * This should be compatible with the "unmapped" top-level approach
 * for multiple-windows (see Xt manual). To use, call DndMultipleShells
 * just one time, after DndInitialize, and register new shells with
 * DndAddShell. Certainly it's not a definitive solution, but works
 * sometimes.
 *==========================================================================*/
void MwDndMultipleShells(void)
{
    MainWidget=0;
}

void MwDndAddShell(Widget widget)
{
    MainWidget=0;
    XtAddEventHandler(widget,NoEventMask,True,MwDndDispatchEvent,NULL);
}

Widget MwDndGetMainWidget(Widget widget)
{
    if(MainWidget) return MainWidget;
#ifdef DEBUG
    fprintf(stderr,"Multiple shells.\n");
#endif /* DEBUG */
	
    while(XtParent(widget) && XtIsRealized(XtParent(widget))==True)
	widget=XtParent(widget);
	
    return widget;
}

/*======================================================== DndUpdateTargetProc
 * Update the Target global variable, so the main handler can dispatch
 * to the correct one. Based on Enter/Leave events. When the pointer leaves,
 * Target=None. When the pointer enter, then update Target to this widget.
 *===========================================================================*/
void MwDndUpdateTargetProc(Widget widget,XtPointer data,XEvent *event,Boolean* p)
{
    if(event->type==EnterNotify)
	Target=XtWindowOfObject(widget);
    else
	Target=None;
}

/*====================================================== DndRegisterDropWidget
 * Each widget that accepts a drop must register within the protocol. This
 * function binds two functions to the widget:
 * 
 * DndUpdateTargetProc : called by EnterWindow and LeaveWindow events.
 * user handler        : called by the Dnd Event sent by DndDispatchEvent.
 *==========================================================================*/
void
MwDndRegisterDropWidget(Widget widget,XtEventHandler handler,XtPointer data)
{
    XtAddEventHandler(widget,EnterWindowMask|LeaveWindowMask,
		      False,MwDndUpdateTargetProc,data);
    XtAddEventHandler(widget,NoEventMask,True,handler,data);
}

/*====================================================== DndRegisterDragWidget
 * Each widget that accepts a drag must register within the protocol. This
 * function binds two functions to the widget:
 * 
 * DndStartAction : called by ButtonPress event.
 * user handler   : called by ButtonMotion events.
 *==========================================================================*/
void
MwDndRegisterDragWidget(Widget widget,XtEventHandler handler,XtPointer data)
{
    XtAddEventHandler(widget,ButtonPressMask,False,MwDndStartAction,data);
    XtAddEventHandler(widget,ButtonMotionMask,False,handler,data);
}

int MwDndIsDragging(void) { return Dragging; }

/*================================================================= DndSetData
 * Updates the selection data.
 *===========================================================================*/
void MwDndSetData(int Type,unsigned char *Data,unsigned long Size)
{
    Window root = DefaultRootWindow(dpy);
    int AuxSize;
    unsigned char *AuxData;
    unsigned long BackSize=Size;

    if(DataOK) return;
	
    /* Set the data type */
    DataType = ( Type>=MW_DndEND ? 0 : Type );
		
    /* Set the data */
    AuxData = Data;
    AuxSize = ( Size <= INT_MAX ? (int)Size : INT_MAX ); 
    XChangeProperty(dpy,root,MwDndSelection,XA_STRING,8,
		    PropModeReplace,Data,AuxSize);
    for(Size-=(unsigned long)AuxSize;Size;Size-=(unsigned long)AuxSize)
    {
	Data+=AuxSize;
	AuxSize = ( (Size<=(INT_MAX)) ? (int)Size : (INT_MAX) );
	XChangeProperty(dpy,root,MwDndSelection,XA_STRING,8,
			PropModeAppend,Data,AuxSize);
    }

    /* Set the data for old DND version */
    Size = BackSize;
    AuxData = Data;
    AuxSize = ( Size <= INT_MAX ? (int)Size : INT_MAX ); 
    XChangeProperty(dpy,root,OldDndSelection,XA_STRING,8,
		    PropModeReplace,Data,AuxSize);
    for(Size-=(unsigned long)AuxSize;Size;Size-=(unsigned long)AuxSize)
    {
	Data+=AuxSize;
	AuxSize = ( (Size<=(INT_MAX)) ? (int)Size : (INT_MAX) );
	XChangeProperty(dpy,root,OldDndSelection,XA_STRING,8,
			PropModeAppend,Data,AuxSize);
    }

    /* Everything is now ok */
    DataOK=1;
}

/*================================================================== DndGetData
 * Return a pointer to the current data. Se HOWTO for more details.
 *===========================================================================*/
void MwDndGetData(unsigned char **Data,unsigned long *Size)
{
    Window root	= DefaultRootWindow(dpy);

    Atom ActualType,ActualDndSelection;
    int	ActualFormat;
    unsigned long RemainingBytes;

    ActualDndSelection=(LastDropVersion == 0L ?
			OldDndSelection :
			MwDndSelection );
      
    XGetWindowProperty(dpy,root,ActualDndSelection,
		       0L,1000000L,
		       FALSE,AnyPropertyType,
		       &ActualType,&ActualFormat,
		       Size,&RemainingBytes,
		       Data);
}	

/*================================== DndDataType DndDragButtons DndSourceWidget
 * 
 * Return information about the Dnd event received. If a non-dnd event is
 * passed, the function DndDataType returns DndNotDnd, and the others
 * return zero.
 *===========================================================================*/
int MwDndDataType(XEvent *event)
{
    int Type;
	
    if(!MwDndIsDropMessage(event)) return MW_DndNotDnd;
    Type=(int)(event->xclient.data.l[0]);
    if(Type>=MW_DndEND) Type=MW_DndUnknown;
    return Type;
}

unsigned int MwDndDragButtons(XEvent *event)
{
    if(!MwDndIsDropMessage(event)) return 0;
    return (unsigned int)(event->xclient.data.l[1]);
}

Widget MwDndSourceWidget(XEvent *event)
{
    fprintf(stderr,"DND warning: MwDndSourceWidget called.\n"
	    "This means the calling program have an old and obsolete\n"
	    "version of DND. Please try to recompile this program using a\n"
	    "new DND library or get a new version of the program that does\n"
	    "not call this routine.\n");
    return 0;
}

Window MwDndSourceWindow(XEvent *event)
{
    if(!MwDndIsDropMessage(event)) return 0;
    if(MwDndProtocolVersion(event)<__DragAndDropH__)
	/* We will try to do something about it, but nothing is certain */
	return XtWindow((Widget)(event->xclient.data.l[2]));
    return (Window)(event->xclient.data.l[2]);
}

void MwDndDropRootCoordinates(XEvent *event,int *x,int *y)
{
    if(!MwDndIsDropMessage(event))
    {
	*x=0; *y=0;
	return;
    }
    
    /* If it is an old protocol version we try to get the coordinates
       using the current pointer position. Of course, the pointer may have
       moved since the drop, but there's nothing we can do about it.
     */
    if(MwDndProtocolVersion(event)<1L)
    {
	Window root_return,child_return;
	int win_x_return,win_y_return;
	unsigned int mask_return;
	
	MwDndSenderWarning();
	XQueryPointer(dpy,DefaultRootWindow(dpy),
		      &root_return,&child_return,x,y,
		      &win_x_return,&win_y_return,&mask_return);
	return;
    }
    /* Thanks god you are using a decent protocol version */
    *x=(int)((long)(event->xclient.data.l[3]) & 0xffff);
    *y=(int)((long)(event->xclient.data.l[3])/65536);
}

void MwDndDropCoordinates(Widget widget,XEvent *event,int *x,int *y)
{
    int root_x,root_y;
    Window child_return;
    
    MwDndDropRootCoordinates(event,&root_x,&root_y);
    XTranslateCoordinates(dpy,DefaultRootWindow(dpy),
			  XtWindow(widget),
			  root_x,root_y,
			  x,y,
			  &child_return);
}

long MwDndProtocolVersion(XEvent *event)
{
    if(!MwDndIsDropMessage(event)) return -1L;
    return event->xclient.data.l[4];
}

int MwDndIsDropMessage(XEvent *event)
{
    if(event->xclient.type != ClientMessage) return 0;
    if(event->xclient.message_type == OldDndProtocol &&
       event->xclient.data.l[4]==0) return 1;
    if(event->xclient.message_type == MwDndProtocol) return 1;
    return 0;
}

void MwDndChangeCursor(int Type,int width,int height,char *image,char *mask,
		     int hot_x,int hot_y)
{
    	DndCursor[Type].ImagePixmap=
	    XCreateBitmapFromData(dpy,DefaultRootWindow(dpy),
				  image,width,height);
	DndCursor[Type].MaskPixmap=
	    XCreateBitmapFromData(dpy,DefaultRootWindow(dpy),
				  mask,width,height);
	DndCursor[Type].CursorID=
	    XCreatePixmapCursor(dpy,DndCursor[Type].ImagePixmap,
				DndCursor[Type].MaskPixmap,
				&Black,&White,
				hot_x,hot_y);
}
