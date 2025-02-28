
  /*\
   *
   *                          COPYRIGHT 1990
   *                    DIGITAL EQUIPMENT CORPORATION
   *                       MAYNARD, MASSACHUSETTS
   *                        ALL RIGHTS RESERVED.
   *
   * THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE WITHOUT NOTICE AND
   * SHOULD NOT BE CONSTRUED AS A COMMITMENT BY DIGITAL EQUIPMENT CORPORATION.
   * DIGITAL MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THIS SOFTWARE
   * FOR ANY PURPOSE.  IT IS SUPPLIED "AS IS" WITHOUT EXPRESS OR IMPLIED
   * WARRANTY.
   *
   * IF THE SOFTWARE IS MODIFIED IN A MANNER CREATING DERIVATIVE COPYRIGHT
   * RIGHTS, APPROPRIATE LEGENDS MAY BE PLACED ON THE DERIVATIVE WORK IN
   * ADDITION TO THAT SET FORTH ABOVE.
   *
   * Permission to use, copy, modify, and distribute this software and its
   * documentation for any purpose and without fee is hereby granted, provided
   * that the above copyright notice appear in all copies and that both that
   * copyright notice and this permission notice appear in supporting
   * documentation, and that the name of Digital Equipment Corporation not be
   * used in advertising or publicity pertaining to distribution of the
   * software without specific, written prior permission.
   \*/

#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#include <X11/Xlib.h>

#include "utils.h"


/***====================================================================***/

#ifndef HAVE_RECALLOCARRAY
void *
uRecalloc(void *old, size_t nOld, size_t nNew, size_t itemSize)
{
    char *rtrn;

    if (old == NULL)
        rtrn = calloc(nNew, itemSize);
    else
    {
        rtrn = reallocarray(old, nNew, itemSize);
        if ((rtrn) && (nNew > nOld))
        {
            bzero(&rtrn[nOld * itemSize], (nNew - nOld) * itemSize);
        }
    }
    return (void *) rtrn;
}
#endif


/***====================================================================***/
/***			DEBUG FUNCTIONS					***/
/***====================================================================***/

#ifdef DEBUG
static FILE *uDebugFile = NULL;
int uDebugIndentLevel = 0;
static const int uDebugIndentSize = 4;

Boolean
uSetDebugFile(const char *name)
{
    if ((uDebugFile != NULL) && (uDebugFile != stderr))
    {
        fprintf(uDebugFile, "switching to %s\n", name ? name : "stderr");
        fclose(uDebugFile);
    }
    if (name != NullString)
        uDebugFile = fopen(name, "w");
    else
        uDebugFile = stderr;
    if (uDebugFile == NULL)
    {
        uDebugFile = stderr;
        return (False);
    }
    return (True);
}

void
uDebug(const char *s, ...)
{
    va_list args;

    for (int i = (uDebugIndentLevel * uDebugIndentSize); i > 0; i--)
    {
        putc(' ', uDebugFile);
    }
    va_start(args, s);
    vfprintf(uDebugFile, s, args);
    va_end(args);
    fflush(uDebugFile);
}
#endif

/***====================================================================***/

static FILE *errorFile = NULL;
static int outCount = 0;
static const char *preMsg = NULL;
static const char *postMsg = NULL;
static const char *prefix = NULL;

Boolean
uSetErrorFile(const char *name)
{
    if ((errorFile != NULL) && (errorFile != stderr))
    {
        fprintf(errorFile, "switching to %s\n", name ? name : "stderr");
        fclose(errorFile);
    }
    if (name != NullString)
        errorFile = fopen(name, "w");
    else
        errorFile = stderr;
    if (errorFile == NULL)
    {
        errorFile = stderr;
        return (Boolean)0;
    }
    return (Boolean)1;
}

void
uInformation(const char *s, ...)
{
    va_list args;

    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fflush(errorFile);
}

/***====================================================================***/

void
uAction(const char *s, ...)
{
    va_list args;

    if (prefix != NULL)
        fprintf(errorFile, "%s", prefix);
    fprintf(errorFile, "                  ");
    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fflush(errorFile);
}

/***====================================================================***/

void
uWarning(const char *s, ...)
{
    va_list args;

    if ((outCount == 0) && (preMsg != NULL))
        fprintf(errorFile, "%s\n", preMsg);
    if (prefix != NULL)
        fprintf(errorFile, "%s", prefix);
    fprintf(errorFile, "Warning:          ");
    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fflush(errorFile);
    outCount++;
}

/***====================================================================***/

void
uError(const char *s, ...)
{
    va_list args;

    if ((outCount == 0) && (preMsg != NULL))
        fprintf(errorFile, "%s\n", preMsg);
    if (prefix != NULL)
        fprintf(errorFile, "%s", prefix);
    fprintf(errorFile, "Error:            ");
    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fflush(errorFile);
    outCount++;
}

/***====================================================================***/

void
uFatalError(const char *s, ...)
{
    va_list args;

    if ((outCount == 0) && (preMsg != NULL))
        fprintf(errorFile, "%s\n", preMsg);
    if (prefix != NULL)
        fprintf(errorFile, "%s", prefix);
    fprintf(errorFile, "Fatal Error:      ");
    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fprintf(errorFile, "                  Exiting\n");
    fflush(errorFile);
    outCount++;
    exit(1);
    /* NOTREACHED */
}

/***====================================================================***/

void
uInternalError(const char *s, ...)
{
    va_list args;

    if ((outCount == 0) && (preMsg != NULL))
        fprintf(errorFile, "%s\n", preMsg);
    if (prefix != NULL)
        fprintf(errorFile, "%s", prefix);
    fprintf(errorFile, "Internal error:   ");
    va_start(args, s);
    vfprintf(errorFile, s, args);
    va_end(args);
    fflush(errorFile);
    outCount++;
}

void
uSetPreErrorMessage(const char *msg)
{
    outCount = 0;
    preMsg = msg;
    return;
}

void
uSetPostErrorMessage(const char *msg)
{
    postMsg = msg;
    return;
}

void
uSetErrorPrefix(const char *pre)
{
    prefix = pre;
    return;
}

void
uFinishUp(void)
{
    if ((outCount > 0) && (postMsg != NULL))
        fprintf(errorFile, "%s\n", postMsg);
    return;
}
