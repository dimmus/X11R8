/*
 * $XTermId: LabelP.h,v 1.3 2025/01/19 15:20:11 tom Exp $
 * $Xorg: LabelP.h,v 1.4 2001/02/09 02:03:44 xorgcvs Exp $
 */

/************************************************************************

Copyright 2022,2025  Thomas E. Dickey
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

This file contains modifications for XawPlus, Roland Krause 2002

************************************************************************/

/*
 * LabelP.h - Private definitions for Label widget
 *
 */

#ifndef _XawLabelP_h
#define _XawLabelP_h

/***********************************************************************
 *
 * Label Widget Private Data
 *
 ***********************************************************************/

#include <X11/XawPlus/Label.h>
#include <X11/XawPlus/SimpleP.h>

/* New fields for the Label widget class record */

typedef struct {int foo;} LabelClassPart;

/* Full class record declaration */
typedef struct _LabelClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    LabelClassPart	label_class;
} LabelClassRec;

extern LabelClassRec labelClassRec;

/* New fields for the Label widget record */
typedef struct {
    /* resources */
    Boolean	resize;
    XtJustify	justify;
    Boolean	truncLabel;
    Boolean	truncLeftSide;
    Pixel	foreground;
    XFontStruct	*font;
    XFontSet 	fontset;
    unsigned char encoding;
    Dimension	internal_width;
    Dimension	internal_height;
    char	*label;
    Pixmap	pixmap;
    Pixmap      clipMask;
    Pixmap	left_bitmap;
    Pixmap	left_clipMask;

    /* private state */
    char	*label_full_len;	/* saved label string if label was truncated */
    GC		normal_GC;
    GC          gray_GC;		/* for displaying insensitive text labels */
    GC		lgray_GC;
    Position	label_x;
    Position	label_y;
    Dimension	label_width;
    Dimension	label_height;
    Dimension	label_len;
    int		lbm_y, lbm_x;		/* Position of the left bitmap in the label */

    unsigned int lbm_width, lbm_height;	/* size of left bitmap */
    unsigned int label_depth;		/* depth of bitmap or left bitmap */
} LabelPart;


/****************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************/

typedef struct _LabelRec {
    CorePart	 core;
    SimplePart	 simple;
    LabelPart	 label;
} LabelRec;

#define LEFT_OFFSET(lw) ((lw)->label.left_bitmap \
			 ? (lw)->label.lbm_width + (lw)->label.internal_width \
			 : 0)

#endif /* _XawLabelP_h */
