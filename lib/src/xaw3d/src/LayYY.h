#include <X11/Xfuncproto.h>

/*
 * Some versions of byacc and flex declare yylex().  This chunk fixes that.
 */
/* #if !(defined(YYBYACC) || defined(YYLEX_DECL))
#define YY_DECL int yylex (void)
YY_DECL;
#endif */

/* Functions autogenerated from laygram.y into laygram.c */
extern _X_HIDDEN void LayYYsetsource (char *);
extern _X_HIDDEN void LayYYsetdest (LayoutPtr *);
extern _X_HIDDEN int  LayYYparse (void);
extern _X_HIDDEN int  LayYYwrap (void);

/* Functions autogenerated from laylex.l into laylex.c */
extern _X_HIDDEN int  LayYYlex (void);
extern _X_HIDDEN void LayYYerror (char *s);
