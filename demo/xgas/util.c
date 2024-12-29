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
 * util.c
 *   Feb. 6, 1990: Larry Medwin
 *   gas: Copyright 1990 Larry Medwin: @(#)util.c	1.2 2/9/90
 */

#include "xgas.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * V EQUILIBRIUM
 * What is magnitude of molecule velocity at wall temperature?
 *   velocity is in mm/microsec
 */
float vEquilibrium( temperature)
    float temperature;
{
    return (float) (1.0e-5 * sqrt( (double)(2.0 * KB * temperature / MASS)));
}

/* CHANGE TEMPERATURE OF ONE CHAMBER */
void changeTemp( w, chamber, sliderpos)	/* ARGSUSED */
    Widget w;
    Box *chamber;
    float *sliderpos;
{
    Arg wargs[1];
    char str[10];
    float chamberTmp = MAXTEMP * (1.0 - *sliderpos);

    /* Make new temperature string */
    chamber->temperature = chamberTmp;
    sprintf( str, "%.1f K", chamberTmp);

    /* Tell the widget */
    XtSetArg( wargs[0], XtNlabel, str);
    XtSetValues( chamber->display, wargs, 1);
}

/*
 *  FRAND -- random number routine
 *  Return a floating point number n such that n >= min and n < max
 *    if (min == max), return min
 */
float frand(min, max)
    float min, max;
{
    float n;

    n = (rand() & 0x7fff) / 32768.0;
/*    n = ((float)rand()) / 32768.0;*/
    return n * (max - min) + min;
}

/*
 * ERROR handler
 *   This is a good place to put a breakpoint.
 */
void
error(char *message, float time)
{
    printf("Error at time = %6.3f msec: %s\n", 1.0e-3 * time, message);
    exit(-1);
}

/*
 * QUIT_CALLBACK
 *   is adapted from Douglas A. Young's
 */
void quit_callback(w, client_data, call_data) /* ARGSUSED */
     Widget     w;
     caddr_t    client_data;
     caddr_t    call_data;
{
   exit(0);
}