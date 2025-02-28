/*
 * Copyright 2012 Red Hat, Inc.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Dave Airlie <airlied@redhat.com>
 */

#ifndef COMPAT_API_H
#define COMPAT_API_H

typedef void *pointer;

#if ABI_VIDEODRV_VERSION >= SET_ABI_VERSION(22, 0)
#  define HAVE_NOTIFY_FD 1
#endif

#if ABI_VIDEODRV_VERSION >= SET_ABI_VERSION(23, 0)
#  define BLOCKHANDLER_ARGS_DECL ScreenPtr pScreen, pointer pTimeout
#  define BLOCKHANDLER_ARGS      pScreen, pTimeout
#else
#  define BLOCKHANDLER_ARGS_DECL \
      ScreenPtr pScreen, pointer pTimeout, pointer pReadmask
#  define BLOCKHANDLER_ARGS pScreen, pTimeout, pReadmask
#endif

#if ABI_VIDEODRV_VERSION < SET_ABI_VERSION(25, 2)
#  define current_primary     current_master
#  define primary_pixmap      master_pixmap
#  define secondary_dst       slave_dst
#  define secondary_list      slave_list
#  define secondary_head      slave_head
#  define is_output_secondary is_output_slave
#endif

#endif
