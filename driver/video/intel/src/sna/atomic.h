/*
 * Copyright 2009 Intel Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Chris Wilson <chris@chris-wilson.co.uk>
 *
 */

#ifndef ATOMIC_H
#define ATOMIC_H

#ifdef HAVE_ATOMIC_PRIMITIVES

#  define HAS_ATOMIC_OPS 1

typedef struct
{
    int atomic;
} atomic_t;

#  define atomic_read(x)         ((x)->atomic)
#  define atomic_set(x, val)     ((x)->atomic = (val))
#  define atomic_inc(x)          ((void)__sync_fetch_and_add(&(x)->atomic, 1))
#  define atomic_dec_and_test(x) (__sync_fetch_and_add(&(x)->atomic, -1) == 1)
#  define atomic_add(x, v)       ((void)__sync_add_and_fetch(&(x)->atomic, (v)))
#  define atomic_dec(x, v)       ((void)__sync_sub_and_fetch(&(x)->atomic, (v)))
#  define atomic_cmpxchg(x, oldv, newv) \
      __sync_val_compare_and_swap(&(x)->atomic, oldv, newv)

#endif

#ifdef HAVE_LIB_ATOMIC_OPS
#  include <atomic_ops.h>

#  define HAS_ATOMIC_OPS 1

typedef struct
{
    AO_t atomic;
} atomic_t;

#  define atomic_read(x)         AO_load_full(&(x)->atomic)
#  define atomic_set(x, val)     AO_store_full(&(x)->atomic, (val))
#  define atomic_inc(x)          ((void)AO_fetch_and_add1_full(&(x)->atomic))
#  define atomic_add(x, v)       ((void)AO_fetch_and_add_full(&(x)->atomic, (v)))
#  define atomic_dec(x, v)       ((void)AO_fetch_and_add_full(&(x)->atomic, -(v)))
#  define atomic_dec_and_test(x) (AO_fetch_and_sub1_full(&(x)->atomic) == 1)
#  define atomic_cmpxchg(x, oldv, newv) \
      AO_compare_and_swap_full(&(x)->atomic, oldv, newv)

#endif

#if defined(__sun) && !defined(HAS_ATOMIC_OPS)  /* Solaris & OpenSolaris */

#  include <sys/atomic.h>
#  define HAS_ATOMIC_OPS 1

typedef struct
{
    uint_t atomic;
} atomic_t;

#  define atomic_read(x)         (int)((x)->atomic)
#  define atomic_set(x, val)     ((x)->atomic = (uint_t)(val))
#  define atomic_inc(x)          (atomic_inc_uint(&(x)->atomic))
#  define atomic_dec_and_test(x) (atomic_dec_uint_nv(&(x)->atomic) == 1)
#  define atomic_add(x, v)       (atomic_add_int(&(x)->atomic, (v)))
#  define atomic_dec(x, v)       (atomic_add_int(&(x)->atomic, -(v)))
#  define atomic_cmpxchg(x, oldv, newv) \
      atomic_cas_uint(&(x)->atomic, oldv, newv)

#endif

#ifndef HAS_ATOMIC_OPS
#error xf86-video-intel requires atomic operations, please define them for your CPU/compiler.
#endif

#endif
