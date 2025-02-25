/*
 * $XTermId: Form.h,v 1.4 2025/01/19 14:11:32 tom Exp $
 * $Xorg: Form.h,v 1.5 2001/02/09 02:03:43 xorgcvs Exp $
 */

/**************************************************************************

Copyright 2015,2025	Thomas E. Dickey
Copyright 2002  Roland Krause
Copyright 1987, 1988, 1994, 1998  The Open Group

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

***************************************************************************/

#ifndef _XawForm_h
#define _XawForm_h

#include <X11/Intrinsic.h>

/***********************************************************************
 *
 * Form Widget
 *
 ***********************************************************************/

/* Parameters:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 OBJECT:
 destroyCallback     Callback		Pointer	  	NULL

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

 FORM:
 defaultDistance     Thickness		int		4

*/

/* Constraint parameters:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 bottom		     Edge		XtEdgeType	XtRubber
 fromHoriz	     Widget		Widget		(left edge of form)
 fromVert	     Widget		Widget		(top of form)
 horizDistance	     Thickness		int		defaultDistance
 left		     Edge		XtEdgeType	XtRubber
 resizable	     Boolean		Boolean		False
 right		     Edge		XtEdgeType	XtRubber
 top		     Edge		XtEdgeType	XtRubber
 vertDistance	     Thickness		int		defaultDistance

*/


#ifndef _XtStringDefs_h_
#define XtNtop 			"top"
#define XtRWidget		"Widget"
#endif

#define XtNdefaultDistance	"defaultDistance"
#define XtNbottom		"bottom"
#define XtNleft			"left"
#define XtNright		"right"
#define XtNfromHoriz		"fromHoriz"
#define XtNfromVert		"fromVert"
#define XtNhorizDistance	"horizDistance"
#define XtNvertDistance		"vertDistance"
#define XtNresizable		"resizable"

#define XtCEdge			"Edge"
#define XtCWidget		"Widget"

#ifndef _XawEdgeType_e
#define _XawEdgeType_e
typedef enum {
    XawChainTop,		/* Keep this edge a constant distance from
				   the top of the form */
    XawChainBottom,		/* Keep this edge a constant distance from
				   the bottom of the form */
    XawChainLeft,		/* Keep this edge a constant distance from
				   the left of the form */
    XawChainRight,		/* Keep this edge a constant distance from
				   the right of the form */
    XawRubber			/* Keep this edge a proportional distance
				   from the edges of the form*/
} XawEdgeType;
#endif /* _XawEdgeType_e */

/*
 * Unfortunatly I missed this definition for R4, so I cannot
 * protect it with XAW_BC, it looks like this particular problem is
 * one that we will have to live with for a while.
 *
 * Chris D. Peterson - 3/23/90.
 */

#define XtEdgeType	XawEdgeType

#define XtChainTop	XawChainTop
#define XtChainBottom	XawChainBottom
#define XtChainLeft	XawChainLeft
#define XtChainRight	XawChainRight
#define XtRubber	XawRubber

typedef struct _FormClassRec	*FormWidgetClass;
typedef struct _FormRec		*FormWidget;

extern WidgetClass formWidgetClass;

_XFUNCPROTOBEGIN

extern void XawFormDoLayout(
    Widget		/* w */,
    Boolean		/* do_layout */
);

_XFUNCPROTOEND

#endif /* _XawForm_h */
