/*
 * Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.  All Rights Reserved.
 * Copyright (c) 2005 Jesse Barnes <jbarnes@virtuousgeek.org>
 * Copyright 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Jesse Barns <jbarnes@virtuousgeek.org>
 *    Chris Wilson <chris@chris-wilson.co.uk>
 */

#ifdef HAVE_CONFIG_H
#  include "config_intel.h"
#endif

#include "sna.h"

/**
 * Returns whether the provided transform is affine.
 *
 * transform may be null.
 */
bool
sna_transform_is_affine(const PictTransform *t)
{
    if (t == NULL) return true;

    return t->matrix[2][0] == 0 && t->matrix[2][1] == 0;
}

bool
sna_transform_is_translation(const PictTransform *t,
                             pixman_fixed_t      *tx,
                             pixman_fixed_t      *ty)
{
    if (t == NULL)
    {
        *tx = *ty = 0;
        return true;
    }

    if (t->matrix[0][0] != IntToxFixed(1) || t->matrix[0][1] != 0 ||
        t->matrix[1][0] != 0 || t->matrix[1][1] != IntToxFixed(1) ||
        t->matrix[2][0] != 0 || t->matrix[2][1] != 0 ||
        t->matrix[2][2] != IntToxFixed(1))
        return false;

    *tx = t->matrix[0][2];
    *ty = t->matrix[1][2];
    return true;
}

bool
sna_transform_is_integer_translation(const PictTransform *t,
                                     int16_t             *tx,
                                     int16_t             *ty)
{
    if (t == NULL)
    {
        *tx = *ty = 0;
        return true;
    }

    if (t->matrix[0][0] != IntToxFixed(1) || t->matrix[0][1] != 0 ||
        t->matrix[1][0] != 0 || t->matrix[1][1] != IntToxFixed(1) ||
        t->matrix[2][0] != 0 || t->matrix[2][1] != 0 ||
        t->matrix[2][2] != IntToxFixed(1))
        return false;

    if (pixman_fixed_fraction(t->matrix[0][2]) ||
        pixman_fixed_fraction(t->matrix[1][2]))
        return false;

    *tx = pixman_fixed_to_int(t->matrix[0][2]);
    *ty = pixman_fixed_to_int(t->matrix[1][2]);
    return true;
}

bool
sna_transform_is_imprecise_integer_translation(const PictTransform *t,
                                               int                  filter,
                                               bool                 precise,
                                               int16_t             *tx,
                                               int16_t             *ty)
{
    if (t == NULL)
    {
        DBG(("%s: no transform\n", __FUNCTION__));
        *tx = *ty = 0;
        return true;
    }

    DBG(("%s: FilterNearest?=%d, precise?=%d, transform=[%f %f %f, %f %f %f, "
         "%f %f %f]\n",
         __FUNCTION__,
         filter == PictFilterNearest,
         precise,
         t->matrix[0][0] / 65536.,
         t->matrix[0][1] / 65536.,
         t->matrix[0][2] / 65536.,
         t->matrix[1][0] / 65536.,
         t->matrix[1][1] / 65536.,
         t->matrix[1][2] / 65536.,
         t->matrix[2][0] / 65536.,
         t->matrix[2][1] / 65536.,
         t->matrix[2][2] / 65536.));

    if (t->matrix[0][0] != IntToxFixed(1) || t->matrix[0][1] != 0 ||
        t->matrix[1][0] != 0 || t->matrix[1][1] != IntToxFixed(1) ||
        t->matrix[2][0] != 0 || t->matrix[2][1] != 0 ||
        t->matrix[2][2] != IntToxFixed(1))
    {
        DBG(("%s: not unity scaling\n", __FUNCTION__));
        return false;
    }

    if (filter != PictFilterNearest)
    {
        if (precise)
        {
            if (pixman_fixed_fraction(t->matrix[0][2]) ||
                pixman_fixed_fraction(t->matrix[1][2]))
            {
                DBG(("%s: precise, fractional translation\n", __FUNCTION__));
                return false;
            }
        }
        else
        {
            int f;

            f = pixman_fixed_fraction(t->matrix[0][2]);
            if (f > IntToxFixed(1) / 4 && f < IntToxFixed(3) / 4)
            {
                DBG(("%s: imprecise, fractional translation X: %x\n",
                     __FUNCTION__,
                     f));
                return false;
            }

            f = pixman_fixed_fraction(t->matrix[1][2]);
            if (f > IntToxFixed(1) / 4 && f < IntToxFixed(3) / 4)
            {
                DBG(("%s: imprecise, fractional translation Y: %x\n",
                     __FUNCTION__,
                     f));
                return false;
            }
        }
    }

    *tx = pixman_fixed_to_int(t->matrix[0][2] + IntToxFixed(1) / 2);
    *ty = pixman_fixed_to_int(t->matrix[1][2] + IntToxFixed(1) / 2);
    return true;
}

/**
 * Returns the floating-point coordinates transformed by the given transform.
 */
void
sna_get_transformed_coordinates(int                  x,
                                int                  y,
                                const PictTransform *transform,
                                float               *x_out,
                                float               *y_out)
{
    if (transform == NULL)
    {
        *x_out = x;
        *y_out = y;
    }
    else _sna_get_transformed_coordinates(x, y, transform, x_out, y_out);
}

/**
 * Returns the un-normalized floating-point coordinates transformed by the given transform.
 */
void
sna_get_transformed_coordinates_3d(int                  x,
                                   int                  y,
                                   const PictTransform *transform,
                                   float               *x_out,
                                   float               *y_out,
                                   float               *w_out)
{
    if (transform == NULL)
    {
        *x_out = x;
        *y_out = y;
        *w_out = 1;
    }
    else
    {
        int64_t result[3];

        if (_sna_transform_point(transform, x, y, result))
        {
            *x_out = result[0] / 65536.;
            *y_out = result[1] / 65536.;
            *w_out = result[2] / 65536.;
        }
        else
        {
            *x_out = *y_out = 0;
            *w_out          = 1.;
        }
    }
}
