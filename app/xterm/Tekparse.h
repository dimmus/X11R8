/* $XTermId: Tekparse.h,v 1.8 2016/10/06 00:32:30 tom Exp $ */

/*
 * Copyright 1998-2006,2016 by Thomas E. Dickey
 *
 *                         All Rights Reserved
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE ABOVE LISTED COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization.
 */

#ifndef included_Tekparse_h
#define included_Tekparse_h 1

#ifndef Const
#  if defined(__STDC__) && !defined(__cplusplus)
#    define Const const
#  else
#    define Const /**/
#  endif
#endif

extern Const int Talptable[];
extern Const int Tbestable[];
extern Const int Tbyptable[];
extern Const int Tesctable[];
extern Const int Tipltable[];
extern Const int Tplttable[];
extern Const int Tpttable[];
extern Const int Tspttable[];

#define CASE_REPORT 0
#define CASE_VT_MODE 1
#define CASE_SPT_STATE 2
#define CASE_GIN 3
#define CASE_BEL 4
#define CASE_BS 5
#define CASE_PT_STATE 6
#define CASE_PLT_STATE 7
#define CASE_TAB 8
#define CASE_IPL_STATE 9
#define CASE_ALP_STATE 10
#define CASE_UP 11
#define CASE_COPY 12
#define CASE_PAGE 13
#define CASE_BES_STATE 14
#define CASE_BYP_STATE 15
#define CASE_IGNORE 16
#define CASE_ASCII 17
#define CASE_APL 18
#define CASE_CHAR_SIZE 19
#define CASE_BEAM_VEC 20
#define CASE_CURSTATE 21
#define CASE_PENUP 22
#define CASE_PENDOWN 23
#define CASE_IPL_POINT 24
#define CASE_PLT_VEC 25
#define CASE_PT_POINT 26
#define CASE_SPT_POINT 27
#define CASE_CR 28
#define CASE_ESC_STATE 29
#define CASE_LF 30
#define CASE_SP 31
#define CASE_PRINT 32
#define CASE_OSC 33

#endif /* included_Tekparse_h */
