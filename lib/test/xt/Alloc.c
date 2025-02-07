/*
 * Copyright (c) 2011, 2023, Oracle and/or its affiliates.
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
 */

/* #include <cstddef> */ /* XXX: who use this!? */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "X11/Xfuncproto.h"
#include "X11/Intrinsic.h"
#include "X11/IntrinsicI.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <setjmp.h>
#include <sys/resource.h>
#ifdef HAVE_MALLOC_H
#  include <malloc.h>
#endif

static const char *program_name;

#ifndef assert_no_errno /* defined in glib 2.66 & later*/
#  define assert_no_errno(expr) assert((expr) >= 0)
#endif

/*
 * Check that allocations point to properly aligned memory.
 * For libXt, we consider that to be aligned to an 8-byte (64-bit) boundary.
 */
#define EXPECTED_ALIGNMENT 8

#define CHECK_ALIGNMENT(ptr) assert(((uintptr_t)ptr) % EXPECTED_ALIGNMENT == 0)

/* Check that allocations point to expected amounts of memory, as best we can. */
#ifdef HAVE_MALLOC_USABLE_SIZE
#  define CHECK_SIZE(ptr, size)                \
      do                                       \
      {                                        \
          size_t ps = malloc_usable_size(ptr); \
          assert(ps >= (size));                \
      }                                        \
      while (0)
#else
#  define CHECK_SIZE(ptr, size) *(((char *)ptr) + ((size) - 1)) = 0
#endif

/* Limit we set for memory allocation to be able to test failure cases */
#define ALLOC_LIMIT (INT_MAX / 4)

/* Square root of SIZE_MAX+1 */
#define SQRT_SIZE_MAX ((size_t)1 << (sizeof(size_t) * 4))

/* Just a long string of characters to pull from */
const char test_chars[] =
    "|000 nul|001 soh|002 stx|003 etx|004 eot|005 enq|006 ack|007 bel|"
    "|010 bs |011 ht |012 nl |013 vt |014 np |015 cr |016 so |017 si |"
    "|020 dle|021 dc1|022 dc2|023 dc3|024 dc4|025 nak|026 syn|027 etb|"
    "|030 can|031 em |032 sub|033 esc|034 fs |035 gs |036 rs |037 us |"
    "|040 sp |041  ! |042  \" |043  # |044  $ |045  % |046  & |047  ' |"
    "|050  ( |051  ) |052  * |053  + |054  , |055  - |056  . |057  / |"
    "|060  0 |061  1 |062  2 |063  3 |064  4 |065  5 |066  6 |067  7 |"
    "|070  8 |071  9 |072  : |073  ; |074  < |075  = |076  > |077  ? |"
    "|100  @ |101  A |102  B |103  C |104  D |105  E |106  F |107  G |"
    "|110  H |111  I |112  J |113  K |114  L |115  M |116  N |117  O |"
    "|120  P |121  Q |122  R |123  S |124  T |125  U |126  V |127  W |"
    "|130  X |131  Y |132  Z |133  [ |134  \\ |135  ] |136  ^ |137  _ |"
    "|140  ` |141  a |142  b |143  c |144  d |145  e |146  f |147  g |"
    "|150  h |151  i |152  j |153  k |154  l |155  m |156  n |157  o |"
    "|160  p |161  q |162  r |163  s |164  t |165  u |166  v |167  w |"
    "|170  x |171  y |172  z |173  { |174  | |175  } |176  ~ |177 del|"
    "| 00 nul| 01 soh| 02 stx| 03 etx| 04 eot| 05 enq| 06 ack| 07 bel|"
    "| 08 bs | 09 ht | 0a nl | 0b vt | 0c np | 0d cr | 0e so | 0f si |"
    "| 10 dle| 11 dc1| 12 dc2| 13 dc3| 14 dc4| 15 nak| 16 syn| 17 etb|"
    "| 18 can| 19 em | 1a sub| 1b esc| 1c fs | 1d gs | 1e rs | 1f us |"
    "| 20 sp | 21  ! | 22  \" | 23  # | 24  $ | 25  % | 26  & | 27  ' |"
    "| 28  ( | 29  ) | 2a  * | 2b  + | 2c  , | 2d  - | 2e  . | 2f  / |"
    "| 30  0 | 31  1 | 32  2 | 33  3 | 34  4 | 35  5 | 36  6 | 37  7 |"
    "| 38  8 | 39  9 | 3a  : | 3b  ; | 3c  < | 3d  = | 3e  > | 3f  ? |"
    "| 40  @ | 41  A | 42  B | 43  C | 44  D | 45  E | 46  F | 47  G |"
    "| 48  H | 49  I | 4a  J | 4b  K | 4c  L | 4d  M | 4e  N | 4f  O |"
    "| 50  P | 51  Q | 52  R | 53  S | 54  T | 55  U | 56  V | 57  W |"
    "| 58  X | 59  Y | 5a  Z | 5b  [ | 5c  \\ | 5d  ] | 5e  ^ | 5f  _ |"
    "| 60  ` | 61  a | 62  b | 63  c | 64  d | 65  e | 66  f | 67  g |"
    "| 68  h | 69  i | 6a  j | 6b  k | 6c  l | 6d  m | 6e  n | 6f  o |"
    "| 70  p | 71  q | 72  r | 73  s | 74  t | 75  u | 76  v | 77  w |"
    "| 78  x | 79  y | 7a  z | 7b  { | 7c  | | 7d  } | 7e  ~ | 7f del|";

/* Environment saved by setjmp() */
static jmp_buf jmp_env;

static void _X_NORETURN
xt_error_handler(String message)
{
    if (message && *message) fprintf(stderr, "Caught Error: %s\n", message);
    else fputs("Caught Error.\n", stderr);

    /* Avoid exit() in XtErrorMsg() */
    longjmp(jmp_env, 1);
}

static int
rand_range(int from, int to)
{
    return (rand() % (from - to + 1)) + from;
}

/* Test a simple short string & int */
static void
test_XtAsprintf_short(void)
{
    char  snbuf[1024];
    char *asbuf;
    int   r = rand();
    int   snlen, aslen;

    snlen = snprintf(snbuf, sizeof(snbuf), "%s: %d\n", program_name, r);
    aslen = XtAsprintf(&asbuf, "%s: %d\n", program_name, r);

    assert(asbuf != NULL);
    assert(snlen == aslen);
    assert(strcmp(snbuf, asbuf) == 0);
    assert(asbuf[aslen] == '\0');
}

/* Test a string long enough to be past the 256 character limit that
   makes XtAsprintf re-run snprintf after allocating memory */
static void
test_XtAsprintf_long(void)
{
    char *asbuf;
    int   aslen;
    int   r1 = rand_range(0, 256);
    int   r2 = rand_range(1024, sizeof(test_chars) - r1);

    aslen = XtAsprintf(&asbuf, "%.*s", r2, test_chars + r1);

    assert(asbuf != NULL);
    assert(aslen == r2);
    assert(strncmp(asbuf, test_chars + r1, r2) == 0);
    assert(asbuf[aslen] == '\0');
}

/* Make sure XtMalloc() works for a non-zero amount of memory */
static void
test_XtMalloc_normal(void)
{
    void *p;
    /* Pick a size between 1 & 256K */
    int size = rand_range(1, (256 * 1024));

    errno = 0;

    p = XtMalloc(size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, size);

    /* make sure we can write to all the allocated memory */
    memset(p, 'A', size);

    XtFree(p);
    assert(errno == 0);
}

/* Make sure XtMalloc(0) returns expected results */
static void
test_XtMalloc_zero(void)
{
    void *p;

    errno = 0;

    p = XtMalloc(0);
#if !defined(MALLOC_0_RETURNS_NULL) || defined(XTMALLOC_BC)
    assert(p);
#else
    assert(p == NULL);
#endif
    XtFree(p);
    assert(errno == 0);

    /* __XtMalloc always returns a non-NULL pointer for size == 0 */
    p = __XtMalloc(0);
    assert(p != NULL);
    XtFree(p);
    assert(errno == 0);
}

/* Make sure sizes larger than the limit we set in main() fail */
static void
test_XtMalloc_oversize(void)
{
    void *p;

    if (setjmp(jmp_env) == 0)
    {
        p = XtMalloc(UINT_MAX - 1);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }
}

/* Make sure XtMalloc catches integer overflow if possible, by requesting
 * sizes that are so large that they cause overflows when either adding the
 * malloc data block overhead or aligning.
 *
 * Testing integer overflow cases is limited by the fact that XtMalloc
 * only takes unsigned arguments (typically 32-bit), and relies on
 * the underlying libc malloc to catch overflow, which can't occur if
 * 32-bit arguments are passed to a function taking 64-bit args.
 */
static void
test_XtMalloc_overflow(void)
{
#if UINT_MAX < SIZE_MAX
    /* test_skip("overflow not possible in this config"); */
    return;
#else
    void *p;

    if (setjmp(jmp_env) == 0)
    {
        p = XtMalloc(SIZE_MAX);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        p = XtMalloc(SIZE_MAX - 1);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        p = XtMalloc(SIZE_MAX - 8);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }
#endif
}

/* Make sure XtCalloc() works for a non-zero amount of memory */
static void
test_XtCalloc_normal(void)
{
    char *p;
    /* Pick a number of elements between 1 & 16K */
    int num  = rand_range(1, (16 * 1024));
    /* Pick a size between 1 & 16K */
    int size = rand_range(1, (16 * 1024));

    errno = 0;

    p = XtCalloc(num, size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, num * size);

    /* make sure all the memory was zeroed */
    for (int i = 0; i < (num * size); i++)
    {
        assert(p[i] == 0);
    }

    /* make sure we can write to all the allocated memory */
    memset(p, 'A', num * size);

    XtFree(p);
    assert(errno == 0);
}

/* Make sure XtCalloc() returns the expected results for args of 0 */
static void
test_XtCalloc_zero(void)
{
    void *p;

    errno = 0;

    p = XtCalloc(0, 0);
#if !defined(MALLOC_0_RETURNS_NULL) || defined(XTMALLOC_BC)
    assert(p != NULL);
    XtFree(p);
#else
    assert(p == NULL);
#endif
    assert(errno == 0);

    p = XtCalloc(1, 0);
#if !defined(MALLOC_0_RETURNS_NULL) || defined(XTMALLOC_BC)
    assert(p != NULL);
    XtFree(p);
#else
    assert(p == NULL);
#endif
    assert(errno == 0);

    p = XtCalloc(0, 1);
#if !defined(MALLOC_0_RETURNS_NULL)
    assert(p != NULL);
    XtFree(p);
#else
    assert(p == NULL);
#endif
    assert(errno == 0);

    /* __XtCalloc always returns a non-NULL pointer for size == 0 */
    p = __XtCalloc(1, 0);
    assert(p != NULL);
    XtFree(p);
    assert(errno == 0);
}

/* Make sure sizes larger than the limit we set in main() fail. */
static void
test_XtCalloc_oversize(void)
{
    void *p;

    if (setjmp(jmp_env) == 0)
    {
        p = XtCalloc(2, ALLOC_LIMIT);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }
}

/* Make sure XtCalloc catches integer overflow if possible
 *
 * Testing integer overflow cases is limited by the fact that XtCalloc
 * only takes unsigned arguments (typically 32-bit), and relies on
 * the underlying libc calloc to catch overflow, which can't occur
 * if 32-bit arguments are passed to a function taking 64-bit args.
 */
static void
test_XtCalloc_overflow(void)
{
#if UINT_MAX < SIZE_MAX
    /* g_test_skip("overflow not possible in this config"); */
    return;
#else
    void *p;

    if (setjmp(jmp_env) == 0)
    {
        p = XtCalloc(2, SIZE_MAX);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        /* SQRT_SIZE_MAX * SQRT_SIZE_MAX == 0 due to overflow */
        p = XtCalloc(SQRT_SIZE_MAX, SQRT_SIZE_MAX);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        /* Overflows to a small positive number */
        p = XtCalloc(SQRT_SIZE_MAX + 1, SQRT_SIZE_MAX);
        assert(p == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }
#endif
}

/* Make sure XtRealloc() works for a non-zero amount of memory */
static void
test_XtRealloc_normal(void)
{
    void *p, *p2;
    char *p3;

    errno = 0;

    /* Make sure realloc with a NULL pointer acts as malloc */
    p = XtRealloc(NULL, 814);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, 814);

    /* make sure we can write to all the allocated memory */
    memset(p, 'A', 814);

    /* create another block after the first */
    p2 = XtMalloc(73);
    assert(p2 != NULL);

    /* now resize the first */
    p3 = XtRealloc(p, 7314);
    assert(p3 != NULL);
    CHECK_ALIGNMENT(p3);
    CHECK_SIZE(p3, 7314);

    /* verify previous values are still present */
    for (int i = 0; i < 814; i++)
    {
        assert(p3[i] == 'A');
    }

    XtFree(p3);
    XtFree(p2);
    assert(errno == 0);
}

/* Make sure XtRealloc(0) returns a valid pointer as expected */
static void
test_XtRealloc_zero(void)
{
    void *p, *p2;

    errno = 0;

    p = XtRealloc(NULL, 0);
    assert(p != NULL);

    p2 = XtRealloc(p, 0);
#ifdef MALLOC_0_RETURNS_NULL
    assert(p == NULL);
#else
    assert(p != NULL);
#endif

    XtFree(p2);
    assert(errno == 0);
}

/* Make sure sizes larger than the limit we set in main() fail */
static void
test_XtRealloc_oversize(void)
{
    void *p, *p2;

    /* Pick a size between 1 & 256K */
    int size = rand_range(1, (256 * 1024));

    p = XtRealloc(NULL, size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtRealloc(p, ALLOC_LIMIT + 1);
        assert(p2 == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    errno = 0;
    XtFree(p);
    assert(errno == 0);
}

/* Make sure XtRealloc catches integer overflow if possible, by requesting
 * sizes that are so large that they cause overflows when either adding the
 * realloc data block overhead or aligning.
 *
 * Testing integer overflow cases is limited by the fact that XtRealloc
 * only takes unsigned arguments (typically 32-bit), and relies on
 * the underlying libc realloc to catch overflow, which can't occur if
 * 32-bit arguments are passed to a function taking 64-bit args.
 */
static void
test_XtRealloc_overflow(void)
{
#if UINT_MAX < SIZE_MAX
    /* g_test_skip("overflow not possible in this config"); */
    return;
#else
    void *p, *p2;

    /* Pick a size between 1 & 256K */
    guint32 size = g_test_rand_int_range(1, (256 * 1024));

    p = XtRealloc(NULL, size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtRealloc(p, SIZE_MAX);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtRealloc(p, SIZE_MAX - 1);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtRealloc(p, SIZE_MAX - 8);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    errno = 0;
    XtFree(p);
    g_assert_cmpint(errno, 0);
#endif
}

/* Make sure XtReallocArray() works for a non-zero amount of memory */
static void
test_XtReallocArray_normal(void)
{
    void *p, *p2;
    char *p3;

    errno = 0;

    /* Make sure reallocarray with a NULL pointer acts as malloc */
    p = XtReallocArray(NULL, 8, 14);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, 8 * 14);

    /* make sure we can write to all the allocated memory */
    memset(p, 'A', 8 * 14);

    /* create another block after the first */
    p2 = XtMalloc(73);
    assert(p2 != NULL);

    /* now resize the first */
    p3 = XtReallocArray(p, 73, 14);
    assert(p3 != NULL);
    CHECK_ALIGNMENT(p3);
    CHECK_SIZE(p3, 73 * 14);
    /* verify previous values are still present */
    for (int i = 0; i < (8 * 14); i++)
    {
        assert(p3[i] == 'A');
    }

    XtFree(p3);
    XtFree(p2);
    assert(errno == 0);
}

/* Make sure XtReallocArray(0) returns a valid pointer as expected */
static void
test_XtReallocArray_zero(void)
{
    void *p, *p2;

    errno = 0;

    p = XtReallocArray(NULL, 0, 0);
    assert(p != NULL);

    p2 = XtReallocArray(p, 0, 0);
#ifdef MALLOC_0_RETURNS_NULL
    assert(p == NULL);
#else
    assert(p != NULL);
#endif

    XtFree(p2);
    assert(errno == 0);
}

/* Make sure sizes larger than the limit we set in main() fail */
static void
test_XtReallocArray_oversize(void)
{
    void *p, *p2;

    /* Pick a number of elements between 1 & 16K */
    int num  = rand_range(1, (16 * 1024));
    /* Pick a size between 1 & 16K */
    int size = rand_range(1, (16 * 1024));

    p = XtReallocArray(NULL, num, size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, num * size);

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtReallocArray(p, 2, ALLOC_LIMIT);
        assert(p2 == NULL);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    errno = 0;
    XtFree(p);
    assert(errno == 0);
}

/* Make sure XtReallocArray catches integer overflow if possible, by requesting
 * sizes that are so large that they cause overflows when either adding the
 * reallocarray data block overhead or aligning.
 *
 * Testing integer overflow cases is limited by the fact that XtReallocArray
 * only takes unsigned arguments (typically 32-bit), and relies on
 * the underlying libc reallocarray to catch overflow, which can't occur if
 * 32-bit arguments are passed to a function taking 64-bit args.
 */
static void
test_XtReallocArray_overflow(void)
{
#if UINT_MAX < SIZE_MAX
    /* g_test_skip("overflow not possible in this config"); */
    return;
#else
    void *p, *p2;

    /* Pick a number of elements between 1 & 16K */
    guint32 num  = g_test_rand_int_range(1, (16 * 1024));
    /* Pick a size between 1 & 16K */
    guint32 size = g_test_rand_int_range(1, (16 * 1024));

    p = XtReallocArray(NULL, num, size);
    assert(p != NULL);
    CHECK_ALIGNMENT(p);
    CHECK_SIZE(p, num * size);

    if (setjmp(jmp_env) == 0)
    {
        p2 = XtReallocArray(p, 1, SIZE_MAX);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        /* SQRT_SIZE_MAX * SQRT_SIZE_MAX == 0 due to overflow */
        p2 = XtReallocArray(p, SQRT_SIZE_MAX, SQRT_SIZE_MAX);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    if (setjmp(jmp_env) == 0)
    {
        /* Overflows to a small positive number */
        p2 = XtReallocArray(p, SQRT_SIZE_MAX + 1, SQRT_SIZE_MAX);
        g_assert_null(p2);
    }
    else
    {
        /*
         * We jumped here from error handler as expected.
         * We cannot verify errno here, as the Xt error handler makes
         * calls that override errno, when trying to load error message
         * files from different locations.
         */
    }

    errno = 0;
    XtFree(p);
    g_assert_cmpint(errno, 0);
#endif
}

int
main(int argc, char **argv)
{
    struct rlimit lim;

    program_name = argv[0];

    /* Set a memory limit so we can test allocations over that size fail */
    assert_no_errno(getrlimit(RLIMIT_AS, &lim));
    if (lim.rlim_cur > ALLOC_LIMIT)
    {
        lim.rlim_cur = ALLOC_LIMIT;
        assert_no_errno(setrlimit(RLIMIT_AS, &lim));
    }

    /* Install xt_error_handler to avoid exit on allocation failure */
    XtSetErrorHandler(xt_error_handler);

    test_XtAsprintf_short();
    test_XtAsprintf_long();

    test_XtMalloc_normal();
    test_XtMalloc_zero();
    test_XtMalloc_oversize();
    test_XtMalloc_overflow();

    test_XtCalloc_normal();
    test_XtCalloc_zero();
    test_XtCalloc_oversize();
    test_XtCalloc_overflow();

    test_XtRealloc_normal();
    test_XtRealloc_zero();
    test_XtRealloc_oversize();
    test_XtRealloc_overflow();

    test_XtReallocArray_normal();
    test_XtReallocArray_zero();
    test_XtReallocArray_oversize();
    test_XtReallocArray_overflow();
}
