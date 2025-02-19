/*
 * $Id: ThreeDP.h,v 1.3 2000/08/31 17:08:07 falk Exp $
 * Based on Xaw3d v1.3
 * $KK: ThreeDP.h,v 0.3 92/11/04 xx:xx:xx keithley Exp $
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


/* Notes:
 *
 * This version (1.06) of ThreeD exports some functionality for the
 * benefit of other classes which may not be direct subclasses of
 * the ThreeD class.  In many cases, it is sufficient for the
 * other class to include a ThreeDPart element in its instance structure.
 *
 * Of particular interest are the four GCs computed and stored in this
 * ThreeDPart structure:
 *
 *	bg_GC		background GC -- plain background (default light grey)
 *	top_shadow_GC	highlight (default lighter grey)
 *	bot_shadow_GC	shadow (default dark grey)
 *	arm_GC		"armed" color (button pressed, etc.) (default grey)
 *
 *
 * These GC's are shared where possible, and even if a child widget does not
 * use all of these, there is minimal waste.
 *
 * The following resources are used in the computation of the GCs:
 *
 *    bg_GC:
 *	backgroundPixmap, background
 *	  If backgroundPixmap is a color pixmap, it is used directly as
 *	  the background, else if it is a bitmap it is used with the
 *	  background and foreground pixels values, else if it is not
 *	  specified, the background pixel is used as a solid color.
 *
 *
 *    top_shadow_GC:
 *	topShadowPixmap, topShadowPixel,
 *	backgroundPixmap, background, topShadowContrast, beNiceToColormap
 *	  If topShadowPixmap is specified, it is used for the GC, else
 *	  If topShadowPixel is specified, it is used for the GC, else
 *	  If backgroundPixmap is specified it is multiplied by
 *	    (100+topShadowContrast,) else
 *	  The GC uses background*(100+topShadowContrast).
 *
 *	If pixmap is a color pixmap, it is used directly, else
 *	If pixmap is a bitmap, it is used with foreground,background colors.
 *
 *	For solid colors:
 *	  If display is monochrome, top shadow GC is foreground color, else
 *	  If beNiceToColormap is set, a grey pixel halfway between
 *	    foreground and background is assigned, and the topshadow color
 *	    is a 50% dither between background and grey.
 *
 *	Default topShadowContrast is 20.
 *
 *    bot_shadow_GC:
 *	botShadowPixmap, botShadowPixel,
 *	backgroundPixmap, background, botShadowContrast,
 *	  Similar rules to top_shadow_GC except that pixel values scaled
 *	  by (100-botShadowContrast).  Default contrast is 40
 *
 *	If display is monochrome, bot shadow GC is foreground color, else
 *	If beNiceToColormap is set, the topshadow color
 *	  is a 50% dither between foreground and grey.
 *
 *
 *    arm_shadow_GC:
 *	armShadowPixmap, armShadowPixel,
 *	backgroundPixmap, background, armShadowContrast,
 *	  Similar rules to top_shadow_GC except that pixel values scaled
 *	  by (100-botShadowContrast).  Default contrast is 10
 *
 *	If display is monochrome, arm shadow GC is unasigned; child
 *	  widgets should swap foreground/background for armed state.
 *	If beNiceToColormap is set, the arm shadow color is grey.
 *
 *	
 *
 * Functions:
 *
 * Xaw3dInitThreeDPart(Widget w, ThreeDPart *part)
 *	This function takes the resource in the ThreeDPart and computes
 *	and allocates topShadowPixel, bottomShadowPixel, armPixel,
 *	topShadowPixmap, bottomShadowPixmap, armPixmap, topShadowGC,
 *	bottomShadowGC, and armGC.
 *
 * Xaw3dDestroyThreeDPart(Widget w, ThreeDPart *part)
 *	This function releases any resources allocated by InitThreeDPart.
 *
 * Boolean
 * Xaw3dSetValuesThreeD (current, request, new, tdCurrent, tdRequest, tdNew)
 *	Widget current, request, new ;
 *	ThreeDPart *tdCurrent, *tdRequest, *tdNew ;
 *
 *	React to changes in resources in a ThreeDPart structure, called
 *	from SetValues.  It computes and re-allocates GCs as neccessary,
 *	returning True if a redraw is needed.
 *
 *
 *	UTILITIES:
 *
 * Xaw3dComputeThreeDRGB(Widget w, int scale, XColor *xcol_out, altScale)
 *	This function multiplies the Widget's background pixel by scale/100,
 *	and returns the resulting color.
 *	Typically, you would call this with (scale = 100+topShadowContrast)
 *	or (scale = 100-bottomShadowContrast), etc.
 *	If the background pixel is WhitePixel or BlackPixel, altScale is
 *	used with white.
 *
 * Xaw3dComputeTopShadowRGB3d(Widget, ThreeDPart *, XColor *xcol_out)
 * Xaw3dComputeBotShadowRGB3d(Widget, ThreeDPart *, XColor *xcol_out)
 * Xaw3dComputeArmColorRGB3d(Widget, ThreeDPart *, XColor *xcol_out)
 *	Compute and return top/bottom/arm color based on
 *	shadow contrast, foreground color and background color.
 *
 *
 * Xaw3dDrawThreeDRectangle(Widget w, ThreeDPart *part, Region,
 * 		xtl,ytl, xbr,ybr, int shadow_width, int out)
 *	This function draws a 3-d rectangle with specified inner corners.
 *
 * Xaw3dDrawThreeDBorder(Widget w, ThreeDPart *part, Region,
 * 		xtl,ytl, xbr,ybr, int out)
 *	Same, but handles ridge shadows, gets shadow width from threeD.
 */

#ifndef _ThreeDP_h
#define _ThreeDP_h

#include "ThreeD.h"
#include "SimpleP.h"

typedef struct {
    Dimension	shadow_width;
    Pixel	top_shadow_pixel;
    Pixel	bot_shadow_pixel;
    Pixel	arm_pixel ;
    Pixmap	top_shadow_pxmap;
    Pixmap	bot_shadow_pxmap;
    Pixmap	arm_pxmap;
    int		bg_pixmap_depth ;
    int		top_shadow_pixmap_depth ;
    int		bot_shadow_pixmap_depth ;
    int		arm_pixmap_depth ;
    int		top_shadow_contrast;
    int		bot_shadow_contrast;
    int		arm_contrast;
    Boolean	be_nice_to_cmap;
    Boolean	invert_border;
    Boolean	ridge_shadow;

    XtPointer	user_data;
    GC		bg_GC ;
    GC		top_shadow_GC;
    GC		bot_shadow_GC;
    GC		arm_GC;
    struct pxmap_cache *pxmap_cache ;
  } ThreeDPart;

/* Full instance record declaration */
typedef struct _ThreeDRec {
    CorePart	core;
    SimplePart	simple;
    ThreeDPart	threeD;
  } ThreeDRec;

typedef struct {
    void (*shadowdraw)();
  } ThreeDClassPart;

#define XtInheritXaw3dShadowDraw ((void (*)())_XtInherit)

/* Full class record declaration. */
typedef struct _ThreeDClassRec {
    CoreClassPart	core_class;
    SimpleClassPart	simple_class;
    ThreeDClassPart	threeD_class;
  } ThreeDClassRec;

/* Class pointer. */
extern ThreeDClassRec threeDClassRec;


	/* Convenience functions for subclasses */

_XFUNCPROTOBEGIN

#if NeedFunctionPrototypes

extern	void	Xaw3dInitThreeDPart(Widget w, ThreeDPart *part) ;
extern	void	Xaw3dDestroyThreeDPart(Widget w, ThreeDPart *part) ;
extern	void	Xaw3dComputeThreeDRGB(Widget w, int scale,
			XColor *xcol_out, int altScale) ;
extern	void	Xaw3dComputeTopShadowRGB3d(Widget, ThreeDPart *, XColor *) ;
extern	void	Xaw3dComputeBotShadowRGB3d(Widget, ThreeDPart *, XColor *) ;
extern	void	Xaw3dComputeArmColorRGB3d(Widget, ThreeDPart *, XColor *) ;
extern	Pixel	Xaw3dAllocThreeDPixel(Widget w, int scale, int altScale) ;
extern	Boolean	Xaw3dSetValuesThreeD(
  Widget current, Widget request, Widget new,
  ThreeDPart *tcurrent, ThreeDPart *trequest, ThreeDPart *tnew) ;

extern	Pixel	_XawAllocShadowPixel(Widget, int scale) ;
extern	Status	_XawAllocGreyPixel(Widget, Pixel fg, int cnt, Pixel *) ;


extern	void	Xaw3dDrawThreeDRectangle(
  Widget	w,
  ThreeDPart	*threeD,
  Region	region,
  int		xtl,
  int		ytl,
  int		xbr,
  int		ybr,
  int		s,
  int		out
  ) ;

extern	void	Xaw3dDrawThreeDBorder(
  Widget	w,
  ThreeDPart	*threeD,
  Region	region,
  int		xtl,
  int		ytl,
  int		xbr,
  int		ybr,
  int		out) ;

#else

extern	void	Xaw3dInitThreeDPart() ;
extern	void	Xaw3dDestroyThreeDPart() ;
extern	Pixel	Xaw3dAllocThreeDPixel() ;
extern	Pixel	Xaw3dComputeThreeDRGB() ;
extern	void	Xaw3dComputeTopShadowRGB3d() ;
extern	void	Xaw3dComputeBotShadowRGB3d() ;
extern	void	Xaw3dComputeArmColorRGB3d() ;
extern	Boolean	Xaw3dSetValuesThreeD() ;
extern	void	Xaw3dDrawThreeDRectangle() ;
extern	void	Xaw3dDrawThreeDBorder() ;

#endif /* NeedFunctionPrototypes */

_XFUNCPROTOEND


#endif /* _ThreeDP_h */
