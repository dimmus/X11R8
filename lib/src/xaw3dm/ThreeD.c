/*
 * $Id: ThreeD.c,v 1.2 1999/12/15 19:04:57 falk Exp $
 * Based on Xaw3d v1.3
 * $KK: ThreeD.c,v 0.3 92/11/04 xx:xx:xx keithley Exp $
 */

/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.
Copyright 1992 by Kaleb Keithley

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital, MIT, or Kaleb 
Keithley not be used in advertising or publicity pertaining to distribution 
of the software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#define	TEST_MONO	0

#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/IntrinsicP.h>
#include "XawInit.h"
#include "ThreeDP.h"
#include <X11/Xosdefs.h>

/* Initialization of defaults */

#define offset(field) XtOffsetOf(ThreeDRec, field)

#define	NOCOLOR	0xa5e9b3eb	/* unlikely to occur in nature */

static XtResource resources[] = {
    {XtNshadowWidth, XtCShadowWidth, XtRDimension, sizeof(Dimension),
	offset(threeD.shadow_width), XtRImmediate, (XtPointer) 2},
    {XtNtopShadowPixel, XtCTopShadowPixel, XtRPixel, sizeof(Pixel),
	offset(threeD.top_shadow_pixel), XtRImmediate, (XtPointer)NOCOLOR},
    {XtNbottomShadowPixel, XtCBottomShadowPixel, XtRPixel, sizeof(Pixel),
	offset(threeD.bot_shadow_pixel), XtRImmediate, (XtPointer)NOCOLOR},
    {XtNarmPixel, XtCArmPixel, XtRPixel, sizeof(Pixel),
	offset(threeD.arm_pixel), XtRImmediate, (XtPointer)NOCOLOR},
    {XtNtopShadowPixmap, XtCTopShadowPixmap, XtRPixmap, sizeof(Pixmap),
	offset(threeD.top_shadow_pxmap), XtRImmediate, (XtPointer) NULL},
    {XtNbottomShadowPixmap, XtCBottomShadowPixmap, XtRPixmap, sizeof(Pixmap),
	offset(threeD.bot_shadow_pxmap), XtRImmediate, (XtPointer) NULL},
    {XtNarmPixmap, XtCArmPixmap, XtRPixmap, sizeof(Pixmap),
	offset(threeD.arm_pxmap), XtRImmediate, (XtPointer) NULL},
    {XtNtopShadowContrast, XtCTopShadowContrast, XtRInt, sizeof(int),
	offset(threeD.top_shadow_contrast), XtRImmediate, (XtPointer) 20},
    {XtNbottomShadowContrast, XtCBottomShadowContrast, XtRInt, sizeof(int),
	offset(threeD.bot_shadow_contrast), XtRImmediate, (XtPointer) 40},
    {XtNarmContrast, XtCArmContrast, XtRInt, sizeof(int),
	offset(threeD.arm_contrast), XtRImmediate, (XtPointer) 10},
    {XtNuserData, XtCUserData, XtRPointer, sizeof(XtPointer),
	offset(threeD.user_data), XtRPointer, (XtPointer) NULL},
    {XtNbeNiceToColormap, XtCBeNiceToColormap, XtRBoolean, sizeof(Boolean),
	offset(threeD.be_nice_to_cmap), XtRImmediate, (XtPointer) True},
    {XtNborderWidth, XtCBorderWidth, XtRDimension, sizeof(Dimension),
	XtOffsetOf(RectObjRec,rectangle.border_width), XtRImmediate,
	(XtPointer)0},
    {XtNinvertBorder, XtCInvertBorder, XtRBoolean, sizeof(Boolean),
	offset(threeD.invert_border), XtRImmediate, (XtPointer) False},
    {XtNridgeShadow, XtCRidgeShadow, XtRBoolean, sizeof(Boolean),
	offset(threeD.ridge_shadow), XtRImmediate, (XtPointer) False},
};

#undef offset

static	void	ClassPartInitialize(), Initialize(), Destroy();
static	void	Redisplay(), Realize();
static	void	_Xaw3dDrawShadows(), _Xaw3dDrawShadowSurroundedBox();
static	Boolean	SetValues();

static	int	getPixmapDepth() ;
static	void	GcMasks3d() ;
static	GC	AllocGC3d() ;
	void	AllocBgGC() ;
static	void	AllocTopShadowGC() ;
static	void	AllocBotShadowGC() ;
static	void	AllocArmGC() ;
static	Pixmap	Alloc50PctPixmap() ;
static	void	AllocShadowPixels() ;
	void	Xaw3dComputeThreeDRGB() ;
	void	Xaw3dComputeTopShadowRGB3d() ;
	void	Xaw3dComputeTopShadowRGB() ;
	void	Xaw3dComputeBotShadowRGB3d() ;
	void	Xaw3dComputeBottomShadowRGB() ;
	void	Xaw3dComputeArmColorRGB3d() ;
	void	Xaw3dComputeArmColorRGB() ;
static	void	AllocTopShadowPixel() ;
static	void	AllocBotShadowPixel() ;
static	void	AllocArmPixel() ;

ThreeDClassRec threeDClassRec = {
    { /* core fields */
    /* superclass		*/	(WidgetClass) &simpleClassRec,
    /* class_name		*/	"ThreeD",
    /* widget_size		*/	sizeof(ThreeDRec),
    /* class_initialize		*/	NULL,
    /* class_part_initialize	*/	ClassPartInitialize,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	NULL,
    /* num_actions		*/	0,
    /* resources		*/	resources,
    /* resource_count		*/	XtNumber(resources),
    /* xrm_class		*/	NULLQUARK,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	XtInheritResize,
    /* expose			*/	Redisplay,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	NULL,
    /* query_geometry           */	XtInheritQueryGeometry,
    /* display_accelerator      */	XtInheritDisplayAccelerator,
    /* extension                */	NULL
    },
    { /* simple fields */
    /* change_sensitive         */      XtInheritChangeSensitive
    },
    { /* threeD fields */
    /* shadow draw              */      _Xaw3dDrawShadows
    }
};

WidgetClass threeDWidgetClass = (WidgetClass) &threeDClassRec;

/****************************************************************
 *
 * Private Procedures
 *
 ****************************************************************/

	/* TODO: are there pre-defined 2x2 patterns? */


#define shadowpm_size 2
static char shadowpm_bits[] = {0x02, 0x01};

#include <stdio.h>



	/* per display.screen.depth cached info. */

typedef	struct pxmap_cache {
	  struct pxmap_cache *next ;
	  Display	*dpy ;
	  Screen	*scn ;
	  int		depth ;
	  Pixmap	pct50 ;		/* cached 50% dither */
	  int		refcnt50 ;
	} PixmapCache ;

static	PixmapCache	*pixmapCache = NULL ;


static PixmapCache *
findCache(w)
    Widget w;
{
    Display	*dpy = XtDisplay(w) ;
    Screen	*scn = XtScreen(w) ;
    int		dp = w->core.depth ;
    PixmapCache	*ptr ;

    for(ptr = pixmapCache;
	ptr != NULL && (ptr->scn != scn || ptr->dpy != dpy || ptr->depth != dp);
	ptr = ptr->next) ;

    if( ptr == NULL ) {
      ptr = (PixmapCache *) XtMalloc(sizeof(PixmapCache)) ;
      if( ptr == NULL )
        return ptr ;
      ptr->next = pixmapCache ;
      pixmapCache = ptr ;
      ptr->dpy = dpy ;
      ptr->scn = scn ;
      ptr->depth = dp ;
      ptr->pct50 = None ;
      ptr->refcnt50 = 0 ;
    }

    return ptr ;
}



#ifndef	MIN
#define MIN(x,y) ((unsigned short) ((x) < (y)) ? (x) : (y))
#define MAX(x,y) ((unsigned short) ((x) > (y)) ? (x) : (y))
#endif



static	int
getPixmapDepth(dpy, pixmap)
	Display	*dpy ;
	Pixmap	pixmap ;
{
      Window	root ;
      int	x,y ;
      u_int	wid,hgt,border,depth ;
      /* TODO: get this info without server round trip? */
      XGetGeometry(dpy, pixmap, &root, &x,&y, &wid,&hgt,&border,&depth) ;

      return depth ;
}



	/* utility: calculate GC values & masks */

static	void
GcMasks3d(w, pixmap, depth, foreground, background,
	gcv, valuemask, dynamic, dontcare)
    Widget w ;
    Pixmap pixmap ;
    int	depth ;
    Pixel foreground, background ;
    XGCValues	*gcv ;
    XtGCMask	*valuemask, *dynamic, *dontcare;
{

    /* If pixmap is a color pixmap, it is used
     * as the tile.  Else, if it is a bitmap, it is used as a stipple along
     * with foreground and background pixels.  Else if there is no
     * pixmap, the foreground pixel is used.
     */

    /* TODO: simplify */
    if( pixmap == None || pixmap == XtUnspecifiedPixmap )
    {
      gcv->foreground = foreground ;
      *valuemask = GCForeground ;
      *dynamic = GCLineWidth ;
      *dontcare = GCTileStipXOrigin|GCTileStipYOrigin|GCFont|GCSubwindowMode|
	  GCClipXOrigin|GCClipYOrigin|GCDashOffset|
	  GCDashList|GCArcMode ;
    }
    else
    {
      if( depth == 0 ) depth = getPixmapDepth(XtDisplay(w), pixmap) ;
      if( depth == 1 )
      {
	gcv->foreground = foreground ;
	gcv->background = background ;
	gcv->fill_style = FillOpaqueStippled ;
	gcv->stipple = pixmap ;
	*valuemask = GCForeground|GCBackground|GCFillStyle|GCStipple ;
	*dynamic = GCLineWidth|GCTileStipXOrigin|GCTileStipYOrigin ;
	*dontcare = GCTile|GCFont|GCDashOffset|GCDashList|GCArcMode ;
      }
      else
      {
	gcv->fill_style = FillTiled ;
	gcv->tile = pixmap ;
	*valuemask = GCTile ;
	*dynamic = GCLineWidth|GCTileStipXOrigin|GCTileStipYOrigin ;
	*dontcare = GCForeground|GCBackground|GCStipple|GCFont|
		GCDashOffset|GCDashList|GCArcMode ;
      }
    }
}

	/* utility: allocate a GC suitable for rectangle fills & lines */

static	GC
AllocGC3d(w, foreground, background, pixmap, depth)
    Widget w ;
    Pixel foreground, background ;
    Pixmap pixmap ;
    int	depth ;
{
    XGCValues	gcv ;
    XtGCMask	valuemask, dynamic, dontcare;

    GcMasks3d(w, pixmap, depth, foreground, background,
    	&gcv, &valuemask, &dynamic, &dontcare) ;

    return XtAllocateGC(w, 0, valuemask, &gcv, dynamic, dontcare) ;
}











	/* This function allocates a background GC for the given ThreeDPart
	 * structure.  Bottom GC is based on: background pixmap, background
	 * pixel and foreground pixel (when background pixmap is a bitmap).
	 *
	 * Note: this function uses the widget's background
	 * color as the *foreground* in the GC.
	 */
void
AllocBgGC(w, threeD)
    Widget w ;
    ThreeDPart *threeD ;
{
    Pixmap	pixmap = w->core.background_pixmap ;
    Pixel	bg = w->core.background_pixel ;
    Pixel	fg ;

    /* TODO: simplify */
    if( pixmap != None && pixmap != XtUnspecifiedPixmap )
    {
      Screen *scn = XtScreen(w) ;
      if( bg == WhitePixelOfScreen(scn) )
	fg = BlackPixelOfScreen(scn) ;
      else
	fg = WhitePixelOfScreen(scn) ;
      if( threeD->bg_pixmap_depth == 0 )
	threeD->bg_pixmap_depth = getPixmapDepth(XtDisplay(w), pixmap) ;
    }

    threeD->bg_GC =  AllocGC3d(w, bg, fg, pixmap, threeD->bg_pixmap_depth) ;
}


	/* This function allocates a topShadow GC for the given ThreeDPart
	 * structure.  TopShadow GC is based on:  be_nice_to_colormap,
	 * screen depth, top_shadow_pixel, top_shadow_pixmap
	 *
	 * TODO: export this?
	 */

static void
AllocTopShadowGC (w, threeD)
    Widget w;
    ThreeDPart *threeD;
{
    Pixmap	pixmap = threeD->top_shadow_pxmap ;
    int		depth = threeD->top_shadow_pixmap_depth ;
    Pixel	fg, bg = w->core.background_pixel ;
    Screen	*scn = XtScreen (w);

    /* Get depth of pixmap if not known */
    if( pixmap != None && pixmap != XtUnspecifiedPixmap && depth == 0 )
      depth = threeD->top_shadow_pixmap_depth =
        getPixmapDepth(XtDisplay(w), pixmap) ;


    /* TODO: test other Xaw3d library with pixmaps to see what it does */

    if( TEST_MONO || w->core.depth == 1 )
    {
      fg = BlackPixelOfScreen (scn);
      bg = WhitePixelOfScreen (scn);
    }
    else if( threeD->be_nice_to_cmap )
    {
      /* TODO: white pixel of this colormap? */
      fg = WhitePixelOfScreen (scn);
      bg = BlackPixelOfScreen (scn);
    }
    else
    {
      if( threeD->top_shadow_pixel == NOCOLOR )
	  AllocTopShadowPixel(w, threeD);
      fg = threeD->top_shadow_pixel ;
      bg = w->core.background_pixel ;
    }

    threeD->top_shadow_GC = AllocGC3d (w, fg, bg, pixmap, depth) ;
}


	/* This function allocates a botShadow GC for the given ThreeDPart
	 * structure.  BotShadow GC is based on:  be_nice_to_colormap,
	 * screen depth, bot_shadow_pixel, bot_shadow_pixmap
	 *
	 * TODO: export this?
	 */

static void
AllocBotShadowGC (w, threeD)
    Widget w;
    ThreeDPart *threeD;
{
    Pixmap	pixmap = threeD->bot_shadow_pxmap ;
    int		depth = threeD->bot_shadow_pixmap_depth ;
    Pixel	fg, bg = w->core.background_pixel ;
    Screen	*scn = XtScreen (w);

    /* Get depth of pixmap if not known */
    /* TODO: simplify */
    if( pixmap != None && pixmap != XtUnspecifiedPixmap && depth == 0 )
      depth = threeD->bot_shadow_pixmap_depth =
        getPixmapDepth(XtDisplay(w), pixmap) ;


    if( TEST_MONO || w->core.depth == 1 )
    {
      fg = BlackPixelOfScreen (scn);
      bg = WhitePixelOfScreen (scn);
    }
    else if( threeD->be_nice_to_cmap )
    {
      /* TODO: use widget's colormap? */
      fg = BlackPixelOfScreen (scn);
      bg = WhitePixelOfScreen (scn);
    }
    else
    {
      if( threeD->bot_shadow_pixel == NOCOLOR )
	  AllocBotShadowPixel (w, threeD);
      fg = threeD->bot_shadow_pixel ;
      bg = w->core.background_pixel ;
    }

    threeD->bot_shadow_GC = AllocGC3d (w, fg, bg, pixmap, depth) ;
}


	/* This function allocates an arm GC for the given ThreeDPart
	 * structure.  Arm GC is based on:  be_nice_to_colormap,
	 * screen depth, arm_pixel, arm_pixmap
	 *
	 * TODO: export this?
	 */

static void
AllocArmGC (w, threeD)
    Widget w;
    ThreeDPart *threeD;
{
    Pixmap	pixmap = threeD->arm_pxmap ;
    int		depth = threeD->arm_pixmap_depth ;
    Pixel	fg, bg = w->core.background_pixel ;
    Screen	*scn = XtScreen (w);

    /* Next, get depth of pixmap if not known */
    /* TODO: simplify */
    if( pixmap != None && pixmap != XtUnspecifiedPixmap && depth == 0 )
      depth = threeD->arm_pixmap_depth =
        getPixmapDepth(XtDisplay(w), pixmap) ;


    if( TEST_MONO || w->core.depth == 1 )
    {
      fg = BlackPixelOfScreen (scn);
      bg = WhitePixelOfScreen (scn);
    }
    else if( threeD->be_nice_to_cmap )
      fg = w->core.background_pixel ;
    else
    {
      if( threeD->arm_pixel == NOCOLOR )
	  AllocArmPixel (w, threeD);
      fg = threeD->arm_pixel ;
      bg = w->core.background_pixel ;
    }

    threeD->arm_GC = AllocGC3d (w, fg, bg, pixmap, depth) ;
}


	/* General Utility:  Allocate a foreground GC */
GC
_XawAllocFgGC(w, fg, font)
    Widget	w ;
    Pixel	fg ;
    Font	font ;
{
    XGCValues	gcv ;
    XtGCMask	valuemask, dontcare;

    gcv.foreground = fg ;
    gcv.font = font ;
    gcv.graphics_exposures = False ;

    valuemask = GCForeground|GCGraphicsExposures ;
    dontcare =  GCBackground|GCStipple|GCTile|
		GCGraphicsExposures|GCDashOffset|GCDashList|GCArcMode|
		GCTileStipXOrigin|GCTileStipYOrigin ;

    if( font != None )
      valuemask |= GCFont ;
    else
      dontcare |= GCFont ;

    return XtAllocateGC(w, 0, valuemask, &gcv, 0L, dontcare) ;
}




	/* General Utility:  Allocate an "insensitive" GC */
GC
_XawAllocGreyGC(w, fg, font, cnt, be_nice_to_cmap)
    Widget	w ;
    Pixel	fg ;
    Font	font ;
    int		cnt ;		/* contrast: 0-100 */
    int		be_nice_to_cmap ;
{
    XGCValues	gcv ;
    XtGCMask	valuemask, dontcare;

    gcv.graphics_exposures = False ;

    if( TEST_MONO || w->core.depth == 1 || be_nice_to_cmap ||
	!_XawAllocGrayPixel(w, fg, cnt, &gcv.foreground) )
    {
      gcv.foreground = fg ;
      gcv.background = w->core.background_pixel ;
      gcv.fill_style = FillOpaqueStippled ;
      gcv.stipple = XmuCreateStippledPixmap(XtScreen(w), 1L,0L,1) ;

      valuemask = GCForeground|GCBackground|GCFillStyle|
      		  GCStipple|GCGraphicsExposures ;
      dontcare =  GCTile|GCDashOffset|GCDashList|GCArcMode|
		  GCTileStipXOrigin|GCTileStipYOrigin ;
    }
    else
    {
      valuemask = GCForeground|GCGraphicsExposures ;
      dontcare =  GCBackground|GCStipple|GCTile|
		  GCDashOffset|GCDashList|GCArcMode|
		  GCTileStipXOrigin|GCTileStipYOrigin ;
    }

    gcv.font = font ;

    if( font != None )
      valuemask |= GCFont ;
    else
      dontcare |= GCFont ;

    return XtAllocateGC(w, 0, valuemask, &gcv, 0L, dontcare) ;
}



Status
_XawAllocGrayPixel(w, fg, cnt, pixel)
    Widget	w ;
    Pixel	fg ;
    int		cnt ;		/* contrast: 0-100 */
    Pixel	*pixel ;	/* returned pixel value */
{
    Colormap cmap = w->core.colormap ;
    XColor fgc, bgc, greyc ;

    fgc.pixel = fg ;
    bgc.pixel = w->core.background_pixel ;
    XQueryColor(XtDisplay(w),cmap, &fgc) ;
    XQueryColor(XtDisplay(w),cmap, &bgc) ;
    greyc.red =   (fgc.red * cnt +   bgc.red * (100-cnt)) / 100 ;
    greyc.green = (fgc.green * cnt + bgc.green * (100-cnt)) / 100 ;
    greyc.blue =  (fgc.blue * cnt +  bgc.blue * (100-cnt)) / 100 ;
    greyc.flags = DoRed|DoGreen|DoBlue ;
    if( !XAllocColor(XtDisplay(w),cmap, &greyc) )
      return False ;

    *pixel = greyc.pixel ;
    return True ;
}




	/* Allocate 50% pixmap for cases where the shadow
	 * must be made with a dither pattern.  TODO: cache these.
	 *
	 * TODO: use XmuCreateStippledPixmap
	 */

static Pixmap
Alloc50PctPixmap(w)
    Widget w;
{
static char bits[] = {0x02, 0x01};
    PixmapCache	*ptr = findCache(w) ;

    /*
     * TODO: doesn't the server have this in storage somewhere?
     */

    if( ptr == NULL )
      return XCreateBitmapFromData( XtDisplay(w), XtWindow(w), bits, 2, 2) ;

    if( ptr->pct50 == None )
      ptr->pct50 =
      	XCreateBitmapFromData( XtDisplay(w), XtWindow(w), bits, 2, 2) ;

    ++ptr->refcnt50 ;
    return ptr->pct50 ;
}






#ifdef	COMMENT

	/* Utility: allocate shadow & arm pixels if needed. */
	/* If top & bottom shadow colors are the same, we assume that
	 * they haven't been set and need to be computed from the
	 * contrast values.  For this reason, we compute all shadow
	 * colors together.   This isn't really the right way to do
	 * it -- we should really find out if the pixel values were
	 * specified in the defaults database or not.
	 */

static	void
AllocShadowPixels(w, threeD)
    Widget	w ;
    ThreeDPart	*threeD ;
{
    if( !TEST_MONO && w->core.depth != 1  &&
	!threeD->be_nice_to_cmap  &&
	threeD->top_shadow_pixel == threeD->bot_shadow_pixel )
    {
	/* 
	    Eeek.  We're probably going to XQueryColor() three times
	    for each widget.  Necessary because you can set the
	    top and bottom shadows independent of each other in
	    SetValues.  Some caching would certainly help...
	*/
	AllocTopShadowPixel (w, threeD);
	AllocBotShadowPixel (w, threeD);
	AllocArmPixel (w, threeD);
    }
}
#endif	/* COMMENT */



	/* this function takes the widget's background pixel, multiplies
	 * the color by scale/100, and returns the resulting color.
	 *
	 * If the background color is WhitePixel or BlackPixel, use
	 * the alternate scale with color white.
	 *
	 * TODO: replace this with a Motif look-alike?
	 * TODO: cache this info to reduce server turn-arounds?
	 */
void
Xaw3dComputeThreeDRGB(w, scale, xcol_out, altScale)
	Widget	w ;
	int	scale ;
	XColor	*xcol_out ;
	int	altScale ;
{
	XColor get_c ;
	Display *dpy = XtDisplay (w);
	Screen *scn = XtScreen (w);
	Colormap cmap = DefaultColormapOfScreen (scn);
	int maxComponent ;

	get_c.pixel = w->core.background_pixel;
	if (get_c.pixel == WhitePixelOfScreen (scn) ||
	    get_c.pixel == BlackPixelOfScreen (scn)) {
	    xcol_out->red   =
	    xcol_out->green =
	    xcol_out->blue  = 65535 * altScale / 100 ;
	} else {
	  XQueryColor (dpy, cmap, &get_c);

	  maxComponent = MAX(get_c.red, MAX(get_c.green,get_c.blue)) ;
	  if( scale*maxComponent > 65535*100 )
	    scale = 65535*100/maxComponent ;

	  xcol_out->red   = get_c.red * scale / 100 ;
	  xcol_out->green   = get_c.green * scale / 100 ;
	  xcol_out->blue   = get_c.blue * scale / 100 ;
	}
}


	/* Compute a top-shadow color given a ThreeD structure */
void
Xaw3dComputeTopShadowRGB3d (new, threeD, xcol_out)
    Widget new;
    ThreeDPart *threeD ;
    XColor *xcol_out;
{
    int  contrast = threeD->top_shadow_contrast ;
    Xaw3dComputeThreeDRGB(new, 100 + contrast, xcol_out, 100-contrast ) ;
}


	/* Compute a top-shadow color given a ThreeD class widget */
void
Xaw3dComputeTopShadowRGB (new, xcol_out)
    Widget new;
    XColor *xcol_out;
{
    ThreeDWidget tdw = (ThreeDWidget) new;
    Xaw3dComputeTopShadowRGB3d(new, &tdw->threeD, xcol_out) ;
}

	/* Allocate a top-shadow pixel for a ThreeD widget */
static void
AllocTopShadowPixel (new)
    Widget new;
{
    XColor set_c;
    ThreeDWidget tdw = (ThreeDWidget) new;
    Display *dpy = XtDisplay (new);
    Screen *scn = XtScreen (new);
    Colormap cmap = DefaultColormapOfScreen (scn);

    Xaw3dComputeTopShadowRGB (new, &set_c);
    (void) XAllocColor (dpy, cmap, &set_c);
    tdw->threeD.top_shadow_pixel = set_c.pixel;
}

	/* Compute a bottom-shadow color given a ThreeD structure */
void
Xaw3dComputeBotShadowRGB3d (new, threeD, xcol_out)
    Widget new;
    ThreeDPart *threeD ;
    XColor *xcol_out;
{
    int  contrast = threeD->bot_shadow_contrast ;
    Xaw3dComputeThreeDRGB(new, 100 - contrast, xcol_out, contrast ) ;
}

	/* Compute a bottom-shadow color given a ThreeD class widget */
void
Xaw3dComputeBottomShadowRGB (new, xcol_out)
    Widget new;
    XColor *xcol_out;
{
    ThreeDWidget tdw = (ThreeDWidget) new;
    Xaw3dComputeBotShadowRGB3d(new, &tdw->threeD, xcol_out) ;
}

	/* Allocate a bottom-shadow pixel for a ThreeD widget */
static void
AllocBotShadowPixel (new)
    Widget new;
{
    XColor set_c;
    ThreeDWidget tdw = (ThreeDWidget) new;
    Display *dpy = XtDisplay (new);
    Screen *scn = XtScreen (new);
    Colormap cmap = DefaultColormapOfScreen (scn);

    Xaw3dComputeBottomShadowRGB (new, &set_c);
    (void) XAllocColor (dpy, cmap, &set_c);
    tdw->threeD.bot_shadow_pixel = set_c.pixel;
}

	/* Compute an arm color given a ThreeD structure */
void
Xaw3dComputeArmColorRGB3d (new, threeD, xcol_out)
    Widget new;
    ThreeDPart *threeD ;
    XColor *xcol_out;
{
    int  contrast = threeD->arm_contrast ;
    Xaw3dComputeThreeDRGB(new, 100 - contrast, xcol_out, 100-contrast ) ;
}

	/* Compute an arm color given a ThreeD class widget */
void
Xaw3dComputeArmColorRGB (new, xcol_out)
    Widget new;
    XColor *xcol_out;
{
    ThreeDWidget tdw = (ThreeDWidget) new;
    Xaw3dComputeArmColorRGB3d(new, &tdw->threeD, xcol_out) ;
}

	/* Allocate an arm pixel for a ThreeD widget */
static void
AllocArmPixel (new)
    Widget new;
{
    XColor set_c;
    ThreeDWidget tdw = (ThreeDWidget) new;
    Display *dpy = XtDisplay (new);
    Screen *scn = XtScreen (new);
    Colormap cmap = DefaultColormapOfScreen (scn);

    Xaw3dComputeArmColorRGB (new, &set_c);
    (void) XAllocColor (dpy, cmap, &set_c);
    tdw->threeD.arm_pixel = set_c.pixel;
}

	/* END OF UTILITIES */






	/* START OF CLASS METHODS */

static void
ClassPartInitialize (wc)
    WidgetClass	wc;
{
    ThreeDClassRec *tdwc = (ThreeDClassRec*) wc;
    ThreeDClassRec *super = (ThreeDClassRec*) tdwc->core_class.superclass;

    if (tdwc->threeD_class.shadowdraw == XtInheritXaw3dShadowDraw)
	tdwc->threeD_class.shadowdraw = super->threeD_class.shadowdraw;
}


	/* This is the main initialization function for ThreeD Part
	 * structures.  It is exported so that other widgets may
	 * incorporate ThreeDParts without being actual subclasses
	 * of ThreeD.
	 */
void
Xaw3dInitThreeDPart (w, threeD)
    Widget w ;
    ThreeDPart *threeD ;
{
    /* nothing to do at present; defer everything until realize time */
    threeD->bg_GC =
    threeD->top_shadow_GC =
    threeD->bot_shadow_GC =
    threeD->arm_GC = None ;
    threeD->user_data = NULL ;
    threeD->pxmap_cache = NULL ;
}


/* ARGSUSED */
static void Initialize (request, new, args, num_args)
    Widget request, new;
    ArgList args;
    Cardinal *num_args;
{
    ThreeDWidget 	tdw = (ThreeDWidget) new;

    Xaw3dInitThreeDPart(new, &tdw->threeD) ;
}

static void Realize (w, valueMask, attrs)
    Widget w;
    XtValueMask *valueMask;
    XSetWindowAttributes *attrs;
{
    ThreeDWidget tdw = (ThreeDWidget) w;
 /* 
  * This is necessary because Simple doesn't have a realize method
  * XtInheritRealize in the ThreeD class record doesn't work.  This
  * daisychains through Simple to the Core class realize method
  *
  * This could have been specified as NULL.
  */

    (*threeDWidgetClass->core_class.superclass->core_class.realize)
	 (w, valueMask, attrs);
    AllocBgGC(w, &tdw->threeD) ;
    AllocTopShadowGC (w, &tdw->threeD);
    AllocBotShadowGC (w, &tdw->threeD);
    AllocArmGC (w, &tdw->threeD);
}

void
Xaw3dDestroyThreeDPart (w, threeD)
    Widget w;
    ThreeDPart *threeD ;
{
    XtReleaseGC (w, threeD->bg_GC);
    XtReleaseGC (w, threeD->top_shadow_GC);
    XtReleaseGC (w, threeD->bot_shadow_GC);
    XtReleaseGC (w, threeD->arm_GC);

    /* TODO: is this right?  What if the pixmap was allocated by the
     * program?
     */
    if (threeD->top_shadow_pxmap)
	XFreePixmap (XtDisplay (w), threeD->top_shadow_pxmap);
    if (threeD->bot_shadow_pxmap)
	XFreePixmap (XtDisplay (w), threeD->bot_shadow_pxmap);
    if (threeD->arm_pxmap)
	XFreePixmap (XtDisplay (w), threeD->arm_pxmap);

    /* TODO: free 50% pixmaps?  Conversely, preserve them? */
}

static void Destroy (w)
     Widget w;
{
    ThreeDWidget tdw = (ThreeDWidget) w;
    Xaw3dDestroyThreeDPart (w, &tdw->threeD) ;
}

static void Redisplay (w, event, region)
    Widget w;
    XEvent *event;		/* unused */
    Region region;		/* unused */
{
    _Xaw3dDrawShadows (w, event, region, True);
}

	/* React to changes in resources in a ThreeDPart structure. */

Boolean
Xaw3dSetValuesThreeD (current, request, new, tdCurrent, tdRequest, tdNew)
    Widget current, request, new;
    ThreeDPart *tdCurrent, *tdRequest, *tdNew ;
{
    Boolean redisplay = FALSE;
    Boolean alloc_bg_GC = FALSE;
    Boolean alloc_top_GC = FALSE;
    Boolean alloc_bot_GC = FALSE;
    Boolean alloc_arm_GC = FALSE;
    Boolean alloc_top_pixel = FALSE;
    Boolean alloc_bot_pixel = FALSE;
    Boolean alloc_arm_pixel = FALSE;
    Boolean new_nice = tdNew->be_nice_to_cmap != tdCurrent->be_nice_to_cmap ;
    Boolean new_bg =
    	new->core.background_pixel != current->core.background_pixel ;
    Boolean alloc_ok =
	!tdNew->be_nice_to_cmap && new->core.depth != 1 && !TEST_MONO ;


    if( tdNew->shadow_width != tdCurrent->shadow_width )
      redisplay = TRUE ;

    if( tdNew->top_shadow_pixel != tdCurrent->top_shadow_pixel )
      alloc_top_GC = TRUE ;
    else if( alloc_ok &&
      ( tdNew->top_shadow_contrast != tdCurrent->top_shadow_contrast  ||
	     new_nice || new_bg ) )
      alloc_top_GC = alloc_top_pixel = TRUE ;
    else if( tdNew->top_shadow_pxmap != tdCurrent->top_shadow_pxmap )
      alloc_top_GC = TRUE ;

    if( tdNew->bot_shadow_pixel != tdCurrent->bot_shadow_pixel )
      alloc_bot_GC = TRUE ;
    else if( alloc_ok &&
      ( tdNew->bot_shadow_contrast != tdCurrent->bot_shadow_contrast  ||
	     new_nice || new_bg ) )
      alloc_bot_GC = alloc_bot_pixel = TRUE ;
    else if( tdNew->bot_shadow_pxmap != tdCurrent->bot_shadow_pxmap )
      alloc_bot_GC = TRUE ;

    if( tdNew->arm_pixel != tdCurrent->arm_pixel )
      alloc_arm_GC = TRUE ;
    else if( alloc_ok &&
      ( tdNew->arm_contrast != tdCurrent->arm_contrast  ||
	     new_nice || new_bg ) )
      alloc_arm_GC = alloc_arm_pixel = TRUE ;
    else if( tdNew->arm_pxmap != tdCurrent->arm_pxmap )
      alloc_arm_GC = TRUE ;

    if( new->core.background_pixel != current->core.background_pixel  ||
	new->core.background_pixmap != current->core.background_pixmap )
      alloc_bg_GC = TRUE ;


    if (alloc_top_pixel)
	AllocTopShadowPixel (new, tdNew);
    if (alloc_bot_pixel)
	AllocBotShadowPixel (new, tdNew);
    if (alloc_arm_pixel)
	AllocArmPixel (new, tdNew);

    if( alloc_bg_GC ) {
	XtReleaseGC (current, tdCurrent->bg_GC);
	AllocBgGC (new, tdNew);
	redisplay = True;
    }

    if( alloc_top_pixel || alloc_top_GC ) {
	XtReleaseGC (current, tdCurrent->top_shadow_GC);
	AllocTopShadowGC (new, tdNew);
	redisplay = True;
    }

    if( alloc_bot_pixel || alloc_bot_GC ) {
	XtReleaseGC (current, tdCurrent->bot_shadow_GC);
	AllocBotShadowGC (new, tdNew);
	redisplay = True;
    }

    if( alloc_arm_pixel || alloc_arm_GC ) {
	XtReleaseGC (current, tdCurrent->arm_GC);
	AllocArmGC (new, tdNew);
	redisplay = True;
    }

    return (redisplay);
}


static Boolean
SetValues (gcurrent, grequest, gnew, args, num_args)
    Widget gcurrent, grequest, gnew;
    ArgList args;
    Cardinal *num_args;
{
    ThreeDWidget current = (ThreeDWidget) gcurrent;
    ThreeDWidget request = (ThreeDWidget) grequest;
    ThreeDWidget new = (ThreeDWidget) gnew;
    Boolean redisplay ;

#ifdef	COMMENT
    /* TODO: get rid of this???  The superclass set_values function
     * has already been called! */

    (*threeDWidgetClass->core_class.superclass->core_class.set_values)
	(gcurrent, grequest, gnew, NULL, 0);
#endif	/* COMMENT */

    redisplay = Xaw3dSetValuesThreeD (gcurrent, grequest, gnew,
    	&current->threeD, &request->threeD, &new->threeD) ;

    return (redisplay);
}


void
Xaw3dDrawThreeDRectangle (w, threeD, region, xtl, ytl, xbr, ybr, s, out)
    Widget w;
    ThreeDPart *threeD;
    Region region;
    int  xtl, ytl, xbr, ybr; /* inner corners */
    int	s ;	/* shadow width */
    int out;
{
    XPoint	 pt[6];

    /* 
     *	no point to do anything if the shadow_width is 0 or the
     *	widget has not been realized.
     */ 
    if((s > 0) && XtIsRealized (w)){

	Dimension	xms = xtl - s;
	Dimension	yms = ytl - s;
	Dimension	xps = xbr + s;
	Dimension	yps = ybr + s;
	Display		*dpy = XtDisplay (w);
	Window		win = XtWindow (w);
	GC		top, bot;

	if (out) {
	    top = threeD->top_shadow_GC;
	    bot = threeD->bot_shadow_GC;
	} else {
	    top = threeD->bot_shadow_GC;
	    bot = threeD->top_shadow_GC;
	}
	/* Draw shadows. Points are numbered as follows:
	 *
	 *   1_________________________________ 2
	 *   |                               / /|
	 *   |                              / / |
	 *   |   4_________________________/ /  |
	 *   |   |                         3|   |
	 *   |   |                          |   |
	 *   |   |                          |   |
	 *   |   |                          |   |
	 *   |   |5_________________________|   |
	 *   |  / /                         4   |
	 *   | / /                              |
	 *   |/ /_______________________________|
	 *   0                                  1
	 */

	/* points common to top and bottom shadow */
	pt[0].x = xms;	pt[0].y = yps;
	pt[2].x = xps;	pt[2].y = yms;
	pt[3].x = xbr;	pt[3].y = ytl;
	pt[5].x = xtl;	pt[5].y = ybr;

	/* top-left shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, xms, yms, xps, ytl) != RectangleOut) ||
	    (XRectInRegion (region, xms, yms, xtl, yps) != RectangleOut)) {

	    pt[1].x = xms;	pt[1].y = yms;
	    pt[4].x = xtl;	pt[4].y = ytl;
	    XFillPolygon (dpy, win, top, pt, 6,Complex,CoordModeOrigin);
	}

	/* bottom-right shadow */
	if ((region == NULL) ||
	    (XRectInRegion (region, xms, ybr, xps, yps) != RectangleOut) ||
	    (XRectInRegion (region, xbr, yms, xps, yps) != RectangleOut)) {

	    /* swap points from top left to bottom right */
	    pt[1].x = xps;	pt[1].y = yps;
	    pt[4].x = xbr;	pt[4].y = ybr;
	    XFillPolygon (dpy, win, bot, pt,6, Complex,CoordModeOrigin);
	}
    }
}

void
Xaw3dDrawThreeDBorder (w, threeD, region, xtl, ytl, xbr, ybr, out)
    Widget w;
    ThreeDPart *threeD;
    Region region;
    int  xtl, ytl, xbr, ybr; /* inner corners */
    int out;
{
    Dimension	 s = threeD->shadow_width;

    if( !threeD->ridge_shadow )
      Xaw3dDrawThreeDRectangle (w, threeD, region, xtl, ytl, xbr, ybr, s, out) ;
    else
    {
      s = (s+1)/2 ;
      Xaw3dDrawThreeDRectangle (w, threeD, region, xtl, ytl, xbr, ybr, s, out) ;
      Xaw3dDrawThreeDRectangle (w, threeD, region,
      	xtl+s, ytl+s, xbr-s, ybr-s, threeD->shadow_width - s, !out) ;
    }
}

static void
_Xaw3dDrawShadowSurroundedBox (w, event, region, xtl, ytl, xbr, ybr, out)
    Widget w;
    XEvent *event;
    Region region;
    Dimension  xtl, ytl, xbr, ybr; /* inner corners */
    Boolean out;
{
    ThreeDWidget tdw = (ThreeDWidget) w;
    Xaw3dDrawThreeDBorder (w, &tdw->threeD, region, xtl, ytl, xbr, ybr, out);
}

static void
_Xaw3dDrawShadows (gw, event, region, out)
    Widget gw;
    XEvent *event;
    Region region;
    Boolean out;
{
    ThreeDWidget tdw = (ThreeDWidget) gw;
    Dimension	 s   = tdw->threeD.shadow_width;
    /* 
     * draw the shadows using the core part width and height, 
     * and the threeD part shadow_width.
     *
     *	no point to do anything if the shadow_width is 0 or the
     *	widget has not been realized.
     */ 
    if(( s > 0) && XtIsRealized (gw)){
	_Xaw3dDrawShadowSurroundedBox (gw, event, region,
		      s, s,
		      tdw->core.width - s, tdw->core.height - s,
		      (out ^ tdw->threeD.invert_border) );
    }
}
