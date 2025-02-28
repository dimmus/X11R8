/*
 * Copyright 2000 SuSE, Inc.
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2012 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of SuSE not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  SuSE makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * SuSE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL SuSE
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Keith Packard, SuSE, Inc.
 */

#include <string.h>

#include "fb.h"
#include "fbpict.h"

static void
SourceValidateOnePicture(PicturePtr picture)
{
    DrawablePtr drawable = picture->pDrawable;

    if (!drawable) return;

    SourceValidate(drawable,
                   0,
                   0,
                   drawable->width,
                   drawable->height,
                   picture->subWindowMode);
}

static void
fbCompositeSourceValidate(PicturePtr picture)
{
    SourceValidateOnePicture(picture);
    if (picture->alphaMap) SourceValidateOnePicture(picture->alphaMap);
}

void
fbComposite(CARD8      op,
            PicturePtr pSrc,
            PicturePtr pMask,
            PicturePtr pDst,
            INT16      xSrc,
            INT16      ySrc,
            INT16      xMask,
            INT16      yMask,
            INT16      xDst,
            INT16      yDst,
            CARD16     width,
            CARD16     height)
{
    pixman_image_t *src, *mask, *dest;
    int             src_xoff, src_yoff;
    int             msk_xoff, msk_yoff;
    int             dst_xoff, dst_yoff;

    fbCompositeSourceValidate(pSrc);
    if (pMask) fbCompositeSourceValidate(pMask);

    src  = image_from_pict(pSrc, FALSE, &src_xoff, &src_yoff);
    mask = image_from_pict(pMask, FALSE, &msk_xoff, &msk_yoff);
    dest = image_from_pict(pDst, TRUE, &dst_xoff, &dst_yoff);

    if (src && dest && !(pMask && !mask))
    {
        pixman_image_composite(op,
                               src,
                               mask,
                               dest,
                               xSrc + src_xoff,
                               ySrc + src_yoff,
                               xMask + msk_xoff,
                               yMask + msk_yoff,
                               xDst + dst_xoff,
                               yDst + dst_yoff,
                               width,
                               height);
    }

    free_pixman_pict(pSrc, src);
    free_pixman_pict(pMask, mask);
    free_pixman_pict(pDst, dest);
}

static pixman_image_t *
create_solid_fill_image(PicturePtr pict)
{
    PictSolidFill *solid = &pict->pSourcePict->solidFill;
    pixman_color_t color;
    CARD32         a, r, g, b;

    a = (solid->color & 0xff000000) >> 24;
    r = (solid->color & 0x00ff0000) >> 16;
    g = (solid->color & 0x0000ff00) >> 8;
    b = (solid->color & 0x000000ff) >> 0;

    color.alpha = (a << 8) | a;
    color.red   = (r << 8) | r;
    color.green = (g << 8) | g;
    color.blue  = (b << 8) | b;

    return pixman_image_create_solid_fill(&color);
}

static pixman_image_t *
create_linear_gradient_image(PictGradient *gradient)
{
    PictLinearGradient  *linear = (PictLinearGradient *)gradient;
    pixman_point_fixed_t p1;
    pixman_point_fixed_t p2;

    p1.x = linear->p1.x;
    p1.y = linear->p1.y;
    p2.x = linear->p2.x;
    p2.y = linear->p2.y;

    return pixman_image_create_linear_gradient(
        &p1,
        &p2,
        (pixman_gradient_stop_t *)gradient->stops,
        gradient->nstops);
}

static pixman_image_t *
create_radial_gradient_image(PictGradient *gradient)
{
    PictRadialGradient  *radial = (PictRadialGradient *)gradient;
    pixman_point_fixed_t c1;
    pixman_point_fixed_t c2;

    c1.x = radial->c1.x;
    c1.y = radial->c1.y;
    c2.x = radial->c2.x;
    c2.y = radial->c2.y;

    return pixman_image_create_radial_gradient(
        &c1,
        &c2,
        radial->c1.radius,
        radial->c2.radius,
        (pixman_gradient_stop_t *)gradient->stops,
        gradient->nstops);
}

static pixman_image_t *
create_conical_gradient_image(PictGradient *gradient)
{
    PictConicalGradient *conical = (PictConicalGradient *)gradient;
    pixman_point_fixed_t center;

    center.x = conical->center.x;
    center.y = conical->center.y;

    return pixman_image_create_conical_gradient(
        &center,
        conical->angle,
        (pixman_gradient_stop_t *)gradient->stops,
        gradient->nstops);
}

static inline bool
picture_has_clip(PicturePtr p)
{
#if XORG_VERSION_CURRENT >= XORG_VERSION_NUMERIC(1, 16, 99, 1, 0)
    return p->clientClip;
#else
    return p->clientClipType != CT_NONE;
#endif
}

static pixman_image_t *
create_bits_picture(PicturePtr pict, Bool has_clip, int *xoff, int *yoff)
{
    PixmapPtr       pixmap;
    FbBits         *bits;
    FbStride        stride;
    int             bpp;
    pixman_image_t *image;

    fbGetDrawablePixmap(pict->pDrawable, pixmap, *xoff, *yoff);
    fbGetPixmapBitsData(pixmap, bits, stride, bpp);

    image = pixman_image_create_bits((pixman_format_code_t)pict->format,
                                     pixmap->drawable.width,
                                     pixmap->drawable.height,
                                     (uint32_t *)bits,
                                     stride * sizeof(FbStride));

    if (!image) return NULL;

    /* pCompositeClip is undefined for source pictures, so
	 * only set the clip region for pictures with drawables
	 */
    if (has_clip)
    {
        if (picture_has_clip(pict))
            pixman_image_set_has_client_clip(image, TRUE);

        if (*xoff || *yoff)
            pixman_region_translate(pict->pCompositeClip, *xoff, *yoff);

        pixman_image_set_clip_region(image, pict->pCompositeClip);

        if (*xoff || *yoff)
            pixman_region_translate(pict->pCompositeClip, -*xoff, -*yoff);
    }

    /* Indexed table */
    if (pict->pFormat->index.devPrivate)
        pixman_image_set_indexed(image, pict->pFormat->index.devPrivate);

    /* Add in drawable origin to position within the image */
    *xoff += pict->pDrawable->x;
    *yoff += pict->pDrawable->y;

    return image;
}

static pixman_image_t *image_from_pict_internal(PicturePtr pict,
                                                Bool       has_clip,
                                                int       *xoff,
                                                int       *yoff,
                                                Bool       is_alpha_map);

static void
set_image_properties(pixman_image_t *image,
                     PicturePtr      pict,
                     Bool            has_clip,
                     int            *xoff,
                     int            *yoff,
                     Bool            is_alpha_map)
{
    pixman_repeat_t repeat;
    pixman_filter_t filter;

    if (pict->transform)
    {
        /* For source images, adjust the transform to account
		 * for the drawable offset within the pixman image,
		 * then set the offset to 0 as it will be used
		 * to compute positions within the transformed image.
		 */
        if (!has_clip)
        {
            struct pixman_transform adjusted;

            adjusted = *pict->transform;
            pixman_transform_translate(&adjusted,
                                       NULL,
                                       pixman_int_to_fixed(*xoff),
                                       pixman_int_to_fixed(*yoff));
            pixman_image_set_transform(image, &adjusted);
            *xoff = 0;
            *yoff = 0;
        }
        else pixman_image_set_transform(image, pict->transform);
    }

    switch (pict->repeatType)
    {
        default:
        case RepeatNone:
            repeat = PIXMAN_REPEAT_NONE;
            break;

        case RepeatPad:
            repeat = PIXMAN_REPEAT_PAD;
            break;

        case RepeatNormal:
            repeat = PIXMAN_REPEAT_NORMAL;
            break;

        case RepeatReflect:
            repeat = PIXMAN_REPEAT_REFLECT;
            break;
    }

    pixman_image_set_repeat(image, repeat);

    /* Fetch alpha map unless 'pict' is being used
	 * as the alpha map for this operation
	 */
    if (pict->alphaMap && !is_alpha_map)
    {
        int             alpha_xoff, alpha_yoff;
        pixman_image_t *alpha_map = image_from_pict_internal(pict->alphaMap,
                                                             FALSE,
                                                             &alpha_xoff,
                                                             &alpha_yoff,
                                                             TRUE);

        pixman_image_set_alpha_map(image,
                                   alpha_map,
                                   pict->alphaOrigin.x,
                                   pict->alphaOrigin.y);

        free_pixman_pict(pict->alphaMap, alpha_map);
    }

    pixman_image_set_component_alpha(image, pict->componentAlpha);

    switch (pict->filter)
    {
        default:
        case PictFilterNearest:
        case PictFilterFast:
            filter = PIXMAN_FILTER_NEAREST;
            break;

        case PictFilterBilinear:
        case PictFilterGood:
            filter = PIXMAN_FILTER_BILINEAR;
            break;

        case PictFilterConvolution:
            filter = PIXMAN_FILTER_CONVOLUTION;
            break;
    }

    pixman_image_set_filter(image,
                            filter,
                            (pixman_fixed_t *)pict->filter_params,
                            pict->filter_nparams);
    pixman_image_set_source_clipping(image, TRUE);
}

static pixman_image_t *
image_from_pict_internal(PicturePtr pict,
                         Bool       has_clip,
                         int       *xoff,
                         int       *yoff,
                         Bool       is_alpha_map)
{
    pixman_image_t *image = NULL;

    if (!pict)
    {
        *xoff = *yoff = 0;
        return NULL;
    }

    if (pict->pDrawable)
    {
        image = create_bits_picture(pict, has_clip, xoff, yoff);
    }
    else if (pict->pSourcePict)
    {
        SourcePict *sp = pict->pSourcePict;

        if (sp->type == SourcePictTypeSolidFill)
        {
            image = create_solid_fill_image(pict);
        }
        else
        {
            PictGradient *gradient = &pict->pSourcePict->gradient;

            if (sp->type == SourcePictTypeLinear)
                image = create_linear_gradient_image(gradient);
            else if (sp->type == SourcePictTypeRadial)
                image = create_radial_gradient_image(gradient);
            else if (sp->type == SourcePictTypeConical)
                image = create_conical_gradient_image(gradient);
        }
        *xoff = *yoff = 0;
    }
    else
    {
        *xoff = *yoff = 0;
    }

    if (image)
        set_image_properties(image, pict, has_clip, xoff, yoff, is_alpha_map);

    return image;
}

pixman_image_t *
image_from_pict(PicturePtr pict, Bool has_clip, int *xoff, int *yoff)
{
    return image_from_pict_internal(pict, has_clip, xoff, yoff, FALSE);
}

void
free_pixman_pict(PicturePtr pict, pixman_image_t *image)
{
    if (image) pixman_image_unref(image);
}
