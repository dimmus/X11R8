/***********************************************************

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

******************************************************************/

/*
 * AsciiText.c - Private header file for AsciiText Widget.
 *
 * This Widget is intended to be used as a simple front end to the
 * text widget with an ascii source and ascii sink attached to it.
 *
 * Date:    June 29, 1989
 *
 * By:      Chris D. Peterson
 *          MIT X Consortium
 *          kit@expo.lcs.mit.edu
 */

#ifndef _AsciiTextP_h
#define _AsciiTextP_h

#include "X11/Xaw/TextP.h"
#include "X11/Xaw/AsciiText.h"
#include "X11/Xaw/AsciiSrc.h"
#include "X11/Xaw/MultiSrc.h"

typedef struct
{
    XtPointer extension;
} AsciiClassPart;

typedef struct _AsciiTextClassRec
{
    CoreClassPart   core_class;
    SimpleClassPart simple_class;
    TextClassPart   text_class;
    AsciiClassPart  ascii_class;
} AsciiTextClassRec;

extern AsciiTextClassRec asciiTextClassRec;

typedef struct
{
    int resource;
#ifndef OLDXAW
    XtPointer pad[4]; /* for future use and keep binary compatibility */
#endif
} AsciiPart;

typedef struct _AsciiRec
{
    CorePart   core;
    SimplePart simple;
    TextPart   text;
    AsciiPart  ascii;
} AsciiRec;

/*
 * Ascii String Emulation widget
 */
#ifdef ASCII_STRING
typedef struct
{
    XtPointer extension;
} AsciiStringClassPart;

typedef struct _AsciiStringClassRec
{
    CoreClassPart        core_class;
    SimpleClassPart      simple_class;
    TextClassPart        text_class;
    AsciiClassPart       ascii_class;
    AsciiStringClassPart string_class;
} AsciiStringClassRec;

extern AsciiStringClassRec asciiStringClassRec;

typedef struct
{
    int resource;
#  ifndef OLDXAW
    XtPointer pad[4]; /* for future use and keep binary compatibility */
#  endif
} AsciiStringPart;

typedef struct _AsciiStringRec
{
    CorePart        core;
    SimplePart      simple;
    TextPart        text;
    AsciiPart       ascii;
    AsciiStringPart ascii_str;
} AsciiStringRec;
#endif /* ASCII_STRING */

#ifdef ASCII_DISK
/*
 * Ascii Disk Emulation widget
 */
typedef struct
{
    XtPointer extension;
} AsciiDiskClassPart;

typedef struct _AsciiDiskClassRec
{
    CoreClassPart      core_class;
    SimpleClassPart    simple_class;
    TextClassPart      text_class;
    AsciiClassPart     ascii_class;
    AsciiDiskClassPart disk_class;
} AsciiDiskClassRec;

extern AsciiDiskClassRec asciiDiskClassRec;

typedef struct
{
    char resource;
#  ifndef OLDXAW
    XtPointer pad[4]; /* for future use and keep binary compatibility */
#  endif
} AsciiDiskPart;

typedef struct _AsciiDiskRec
{
    CorePart      core;
    SimplePart    simple;
    TextPart      text;
    AsciiPart     ascii;
    AsciiDiskPart ascii_disk;
} AsciiDiskRec;
#endif /* ASCII_DISK */

#endif /* _AsciiTextP_h */
