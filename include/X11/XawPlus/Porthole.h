/*
 * $XTermId: Porthole.h,v 1.3 2025/01/19 15:20:11 tom Exp $
 * $Xorg: Porthole.h,v 1.5 2001/02/09 02:03:45 xorgcvs Exp $
 *
Copyright 2022,2025  Thomas E. Dickey
Copyright 1990, 1998  The Open Group

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
 * This file contains modifications for XawPlus, Roland Krause 2002
 */

#ifndef _XawPorthole_h
#define _XawPorthole_h

#include <X11/Intrinsic.h>
#include <X11/XawPlus/Reports.h>

/*****************************************************************************
 *
 * Porthole Widget (subclass of Composite)
 *
 * This widget is similar to a viewport without scrollbars.  Child movement
 * is done by external panners or scrollbars.
 *
 * Parameters:
 *
 *  Name		Class		Type		Default
 *  ----		-----		----		-------
 *  OBJECT:
 *  destroyCallback	Callback	   Pointer	   NULL
 *
 *  RECTANGLE:
 *  borderWidth		BorderWidth	   Dimension	   1
 *  height		Height		   Dimension	   0
 *  sensitive		Sensitive	   Boolean	   True
 *  width		Width		   Dimension	   0
 *  x			Position	   Position	   0
 *  y			Position	   Position	   0
 *
 *  CORE:
 *  border		BorderColor	   Pixel	   XtDefaultForeground
 *  background		Background	   Pixel	   grey75
 *  mappedWhenManaged  	MappedWhenManaged  Boolean	   True
 *
 *  PORTHOLE:
 *  reportCallback	ReportCallback	   Pointer	   NULL
 *
 *****************************************************************************/

					/* external declarations */

extern WidgetClass portholeWidgetClass;
typedef struct _PortholeClassRec *PortholeWidgetClass;
typedef struct _PortholeRec      *PortholeWidget;

#endif /* _XawPorthole_h */
