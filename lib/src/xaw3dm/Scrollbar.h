/*
 * $Id: Scrollbar.h,v 1.3 2000/08/31 17:11:17 falk Exp $
 * Based on Xaw3d v1.3
 * $XConsortium: Scrollbar.h,v 1.7 91/07/26 21:59:31 converse Exp $
 */

/***********************************************************

Copyright (c) 1987, 1988  X Consortium

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _Scrollbar_h
#define _Scrollbar_h

/****************************************************************
 *
 * Scrollbar Widget
 *
 ****************************************************************/

#include <X11/Xmu/Converters.h>
#include <X11/Xfuncproto.h>

/* Scrollbar resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 accelerators	     Accelerators	AcceleratorTable NULL
 ancestorSensitive   AncestorSensitive	Boolean		True
 arrowScrollbar	     ArrowScrollbar	Boolean		True
 background	     Background		Pixel		XtDefaultBackground
 backgroundPixmap    Pixmap		Pixmap		XtUnspecifiedPixmap
 borderColor	     BorderColor	Pixel		XtDefaultForeground
 borderPixmap	     Pixmap		Pixmap		XtUnspecifiedPixmap
 borderWidth	     BorderWidth	Dimension	1
 colormap	     Colormap		Colormap	parent's colormap
 cursor		     Cursor		Cursor		None
 cursorName	     Cursor		String		NULL
 depth		     Depth		int		parent's depth
 destroyCallback     Callback		XtCallbackList	NULL
 foreground	     Foreground		Pixel		XtDefaultForeground
 height		     Height		Dimension	length or thickness
 insensitiveBorder   Insensitive	Pixmap		GreyPixmap
 jumpProc	     Callback		XtCallbackList	NULL
 length		     Length		Dimension	1
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 minimumThumb	     MinimumThumb	Dimension	7
 orientation	     Orientation	XtOrientation	XtorientVertical
 pointerColor	     Foreground		Pixel		XtDefaultForeground
 pointerColorBackground Background	Pixel		XtDefaultBackground
 screen		     Screen		Screen		parent's screen
 scrollDCursor	     Cursor		Cursor		XC_sb_down_arrow
 scrollHCursor	     Cursor		Cursor		XC_sb_h_double_arrow
 scrollLCursor	     Cursor		Cursor		XC_sb_left_arrow
 scrollProc	     Callback		XtCallbackList	NULL
 scrollRCursor	     Cursor		Cursor		XC_sb_right_arrow
 scrollUCursor	     Cursor		Cursor		XC_sb_up_arrow
 scrollVCursor	     Cursor		Cursor		XC_sb_v_double_arrow
 sensitive	     Sensitive		Boolean		True
 shown		     Shown		Float		0.0
 thickness	     Thickness		Dimension	14
 thumb		     Thumb		Bitmap		GreyPixmap
 thumbProc	     Callback		XtCallbackList	NULL
 topOfThumb	     TopOfThumb		Float		0.0
 pickTop	     PickTop		Boolean		False
 translations	     Translations	TranslationTable see source or doc
 width		     Width		Dimension	thickness or length
 x		     Position		Position	0
 y		     Position		Position	0


Notes:
 thumbProc	Called when scroll is complete
 jumpProc	Called as thumb is moved.
 minimumThumb	Minimum length of thumb.
 shown		Portion of scrollbar occupied by thumb.
 topOfThumb	     TopOfThumb		Float		0.0
 pickTop	     PickTop		Boolean		False
 pushThumb	     PushThumb		Boolean		True
 translations	     Translations	TranslationTable see source or doc
 width		     Width		Dimension	thickness or length
 x		     Position		Position	0
 y		     Position		Position	0



Actions:
  The Xaw3d scrollbar widget defines the following actions if
  ARROW_SCROLLBAR is defined:

    NotifyScroll()
	Normally called on button 1 or 3 down.  Determine which part
	of the scroll bar was picked and act accordingly:
	  first arrow:	call scrollProc( -MAX(length/20,5) )
	  first background: call scrollProc(-length)
	  thumb: repaint thumb, begin continuous scrolling.
	  last background: call scrollProc(length)
	  last arrow: call scrollProc( MAX(length/20,5) )
    NotifyScroll(mode)
	New functionality.  Typically called on keypress.
    	Mode is one of:
	  ForwardArrow:		calls scrollProc(5)
	  BackwardArrow:	calls scrollProc(-5)
	  ForwardPage:		calls scrollProc(scrollbar_length)
	  BackwardPage:		calls scrollProc(-scrollbar_length)
	  ForwardHalf:		calls scrollProc(scrollbar_length/2)
	  BackwardHalf:		calls scrollProc(-scrollbar_length/2)
	  Home:			not implemented yet
	  End:			not implemented yet
    NotifyScroll(amount)
    	New functionality.  Amount may be a number, in which case it
	is taken as a number of pixels, or it may be a fraction, in
	which case it is taken as a fraction of scrollbar length.
	Examples:
	  NotifyScroll(5)	forward 5 pixels
	  NotifyScroll(-5)	back 5 pixels
	  NotifyScroll(1/2)	forward 1/2 page
	  NotifyScroll(-1/10)	back 1/10 page.
    NotifyScroll(length)
	Provided for backward compatibility.  See below.
    HandleThumb()
	Normally called on button 1 or 3 motion.
	Handle pointer motion in the thumb.  Call MoveThumb(), NotifyThumb()
	if pointer is in the thumb.  Else, ignore.
    EndScroll()
	Normally called on button up.  Stop scrolling.
    MoveThumb()
	Normally called on button 2 down or motion.  Compute new thumb
	position and repaint.
    NotifyThumb()
	Normally called on button 2 down or motion.  Call notify procs:
		float top ;
		thumbProc( *(XtPointer *)&top ) ;
		jumpProc( (XtPointer)&top ) ;
    KeyScroll(mode)
	New action.  Called on keypress.  Mode is one of ForwardArrow,
	BackwardArrow, ForwardPage, BackwardPage, ForwardHalf,
	BackwardHalf, Home or End.  Computes scroll amount and calls
	scrollProc()

    StartScroll(mode)
	Provided for backwards compatibility.  Mode is one of Forward,
	Continuous or Backward.  Sets scroll direction.
    NotifyScroll(length)
	Provided for backwards compatibility.  Normally called on
	button up.  Length is Proportional or FullLength Compute scroll
	amount based on Length and mode which was passed to StartScroll,
	call scrollProc(int delta).

  The following actions were defined when ARROW_SCROLLBAR is not defined:

    StartScroll(mode)
	Normally called on Button down.  Mode is one of Forward,
	Continuous, or Backward.  Set appropriate cursor.  These modes
	are bound to button 1,2 and 3 respectively.
    MoveThumb()
	Normally called on button 2 down or motion.  Compute new thumb
	position and repaint.
    NotifyThumb()
	Normally called on button 2 down or motion.  Call notify procs.
    NotifyScroll(length)
	Normally called on button up.  Length is Proportional or FullLength
	Compute scroll amount based on Length and mode which was passed
	to StartScroll, call scrollProc(int delta).
    EndScroll()
	Stop scrolling; restore normal cursor.

*/

/* 
 * Most things we need are in StringDefs.h 
 */

#define XtCMinimumThumb "MinimumThumb"
#define XtCShown "Shown"
#define XtCTopOfThumb "TopOfThumb"
#define XtCPickTop "PickTop"

#define XtNminimumThumb "minimumThumb"
#define XtNtopOfThumb "topOfThumb"
#define XtNpickTop "pickTop"

#define XtNarrowScrollbar "arrowScrollbar"
#define XtCArrowScrollbar "ArrowScrollbar"

#ifndef	XtNhighlightThickness
#define XtNhighlightThickness "highlightThickness"
#define XtCHighlightThickness "HighlightThickness"
#endif

typedef struct _ScrollbarRec	  *ScrollbarWidget;
typedef struct _ScrollbarClassRec *ScrollbarWidgetClass;

extern WidgetClass scrollbarWidgetClass;

_XFUNCPROTOBEGIN

extern void XawScrollbarSetThumb(
#if NeedFunctionPrototypes
    Widget		/* scrollbar */,
#if NeedWidePrototypes
    /* float */ double	/* top */,
    /* float */	double	/* shown */
#else
    float		/* top */,
    float		/* shown */
#endif
#endif		 
);

_XFUNCPROTOEND

#endif /* _Scrollbar_h */
