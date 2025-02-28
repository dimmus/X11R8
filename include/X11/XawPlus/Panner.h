/*
 * $XTermId: Panner.h,v 1.3 2025/01/19 15:20:11 tom Exp $
 * $Xorg: Panner.h,v 1.5 2001/02/09 02:03:45 xorgcvs Exp $
 *
Copyright 2022,2025  Thomas E. Dickey
Copyright 1989, 1998  The Open Group

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
 *
 * Author:  Jim Fulton, MIT X Consortium
 *
 * This file contains modifications for XawPlus, Roland Krause 2000
 */

#ifndef _XawPanner_h
#define _XawPanner_h

#include <X11/Intrinsic.h>
#include <X11/XawPlus/Reports.h>

/*****************************************************************************

 Panner Widget (subclass of Simple)

 This widget is used to represent navigation in a 2d coordinate system.

 Resources:

 Name		     Class		Type		Default
 ----		     -----		----		-------
 OBJECT:
 destroyCallback     Callback		Pointer		NULL

 RECTANGLE:
 borderWidth	     BorderWidth	Dimension	1
 height		     Height		Dimension	0
 sensitive	     Sensitive		Boolean		True
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0

 CORE:
 border		     BorderColor	Pixel		XtDefaultForeground
 background	     Background		Pixel		grey75
 mappedWhenManaged   MappedWhenManaged	Boolean		True

 SIMPLE:
 cursor		     Cursor		Cursor		None
 cursorName	     Cursor		String		NULL
 pointerColor        Foreground         Pixel           XtDefaultForeground
 pointerColorBackground Background      Pixel           XtDefaultBackground
 insensitiveBorder   Insensitive	Pixmap		Gray
 international	     International      Boolean		False
 highlightColor	     Background		Pixel		grey90
 shadowColor	     Background		Pixel		grey40
 buttonBorderWidth   Width		Dimension	2

 PANNER:
 allowOff	     AllowOff		Boolean		FALSE
 canvasWidth	     CanvasWidth	Dimension	0
 canvasHeight	     CanvasHeight	Dimension	0
 defaultScale	     DefaultScale	Dimension	8 percent
 internalSpace	     InternalSpace	Dimension	4
 reportCallback	     ReportCallback	XtCallbackList	NULL
 resize		     Resize		Boolean		TRUE
 sliderX	     SliderX		Position	0
 sliderY	     SliderY		Position	0
 sliderWidth	     SliderWidth	Dimension	0
 sliderHeight	     SliderHeight	Dimension	0

*****************************************************************************/

					/* new instance and class names */
#ifndef _XtStringDefs_h_
#define XtNresize "resize"
#define XtCResize "Resize"
#endif

#define XtNallowOff "allowOff"
#define XtCAllowOff "AllowOff"
#define XtNbackgroundStipple "backgroundStipple"
#define XtCBackgroundStipple "BackgroundStipple"
#define XtNdefaultScale "defaultScale"
#define XtCDefaultScale "DefaultScale"
#define XtNcanvasWidth "canvasWidth"
#define XtCCanvasWidth "CanvasWidth"
#define XtNcanvasHeight "canvasHeight"
#define XtCCanvasHeight "CanvasHeight"
#define XtNinternalSpace "internalSpace"
#define XtCInternalSpace "InternalSpace"
#define XtNlineWidth "lineWidth"
#define XtCLineWidth "LineWidth"
#define XtNrubberBand "rubberBand"
#define XtCRubberBand "RubberBand"
#define XtNshadowThickness "shadowThickness"
#define XtCShadowThickness "ShadowThickness"
#define XtNshadowColor "shadowColor"
#define XtCShadowColor "ShadowColor"
#define XtNsliderX "sliderX"
#define XtCSliderX "SliderX"
#define XtNsliderY "sliderY"
#define XtCSliderY "SliderY"
#define XtNsliderWidth "sliderWidth"
#define XtCSliderWidth "SliderWidth"
#define XtNsliderHeight "sliderHeight"
#define XtCSliderHeight "SliderHeight"

					/* external declarations */
extern WidgetClass pannerWidgetClass;

typedef struct _PannerClassRec *PannerWidgetClass;
typedef struct _PannerRec      *PannerWidget;

#endif /* _XawPanner_h */
