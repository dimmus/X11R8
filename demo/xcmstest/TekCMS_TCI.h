/* $XConsortum: TekCMS_TCI.h,v 1.1 91/02/11 19:40:54 dave Exp $ */

#ifndef TEKCMS_TCI
#define TEKCMS_TCI

#include <stdio.h>

static char TekCMS_idir[BUFSIZ];
static char TekCMS_vdir[BUFSIZ];
static char TekCMS_rdir[BUFSIZ];

extern int TCI();
extern int TC_CompareResults();
extern int Cmd_ListTC();

#endif
