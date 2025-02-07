/*
 * Copyright (c) 2023, Oracle and/or its affiliates.
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
#include "TestAllFiles.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include "CompareXpmImage.h"

#include "X11/xpm.h"

#ifndef O_CLOEXEC
#  define O_CLOEXEC 0
#endif

/*
 * Check if a filename ends in ".Z" or ".gz"
 */
static inline Bool
is_compressed(const char *filepath)
{
    const char *ext = strrchr(filepath, '.');

    if ((ext != NULL) &&
        (((ext[1] == 'Z') && (ext[2] == 0)) ||
         ((ext[1] == 'g') && (ext[2] == 'z') && (ext[3] == 0))))
    {
        return True;
    }

    return False;
}

/*
 * If a filename ends in ".Z" or ".gz", remove that extension to avoid
 * confusing libXpm into applying compression when not desired.
 */
static inline void
strip_compress_ext(char *filepath)
{
    char *ext = strrchr(filepath, '.');

    if ((ext != NULL) &&
        (((ext[1] == 'Z') && (ext[2] == 0)) ||
         ((ext[1] == 'g') && (ext[2] == 'z') && (ext[3] == 0))))
    {
        *ext = '\0';
    }
}

/*
 * XpmWriteFileFromXpmImage - Write XPM files without requiring an X Display
  */
static void
test_WFFXI_helper(const char *newfilepath, XpmImage *imageA, XpmInfo *infoA)
{
    XpmImage imageB;
    XpmInfo  infoB;
    int      status;

    printf("...writing %s", newfilepath);

    status = XpmWriteFileFromXpmImage(newfilepath, imageA, infoA);
    assert(status == XpmSuccess);

    if (is_compressed(newfilepath))
    {
        /* Wait a moment for the compression command to finish writing,
          * since OpenWriteFile() does a double fork so we can't just wait
          * for the child command to exit.
          */
        usleep(10000);
    }

    status = XpmReadFileToXpmImage(newfilepath, &imageB, &infoB);
    assert(status == XpmSuccess);

    CompareXpmImage(imageA, &imageB);
    XpmFreeXpmImage(&imageB);
    XpmFreeXpmInfo(&infoB);

    status = remove(newfilepath);
    assert_no_errno(status);
}

static int
TestWriteFileFromXpmImage(const char *filepath)
{
    XpmImage imageA;
    XpmInfo  infoA;
    int      status;
    char    *testdir, *filename, *newfilepath;

#ifndef NO_ZPIPE
    char *cmpfilepath;
#endif

    status = XpmReadFileToXpmImage(filepath, &imageA, &infoA);
    assert(status == XpmSuccess);

    testdir = dir_make_tmp("XpmWrite-test-XXXXXX");
    assert(testdir != NULL);

    filename = path_get_basename(filepath);
    strip_compress_ext(filename);
    newfilepath = build_filename(testdir, filename);

    test_WFFXI_helper(newfilepath, &imageA, &infoA);

#ifndef NO_ZPIPE
    cmpfilepath = strdup_printf("%s.gz", newfilepath);
    test_WFFXI_helper(cmpfilepath, &imageA, &infoA);
    free(cmpfilepath);

#  ifdef XPM_PATH_COMPRESS
    cmpfilepath = strdup_printf("%s.Z", newfilepath);
    test_WFFXI_helper(cmpfilepath, &imageA, &infoA);
    free(cmpfilepath);
#  endif
#endif

    XpmFreeXpmImage(&imageA);
    XpmFreeXpmInfo(&infoA);

    assert_no_errno(rmdir(testdir));

    free(newfilepath);
    free(filename);
    free(testdir);

    return status;
}

static void
test_XpmWriteFileFromXpmImage(void)
{
    /* Todo: verify trying to write to an unwritable file fails */

    TestAllNormalFiles("good", XpmSuccess, TestWriteFileFromXpmImage);
    /* XpmReadFileToXpmImage supports compressed files */
    TestAllCompressedFiles("good", XpmSuccess, TestWriteFileFromXpmImage);
}

/*
 * XpmWriteFileFromData - wrapper around XpmWriteFileFromXpmImage that
 * converts the image into a list of strings.
 */
static void
test_WFFXD_helper(const char *newfilepath, char **dataA)
{
    char **dataB;
    int    status;

    printf("...writing %s", newfilepath);

    status = XpmWriteFileFromData(newfilepath, dataA);
    assert(status == XpmSuccess);

    if (is_compressed(newfilepath))
    {
        /* Wait a moment for the compression command to finish writing,
          * since OpenWriteFile() does a double fork so we can't just wait
          * for the child command to exit.
          */
        usleep(10000);
    }

    status = XpmReadFileToData(newfilepath, &dataB);
    assert(status == XpmSuccess);

    /* Todo: compare data fields */
    XpmFree(dataB);

    status = remove(newfilepath);
    assert_no_errno(status);
}

static int
TestWriteFileFromData(const char *filepath)
{
    char **data = NULL;
    int    status;
    char  *testdir, *filename, *newfilepath;

#ifndef NO_ZPIPE
    char *cmpfilepath;
#endif

    status = XpmReadFileToData(filepath, &data);
    assert(status == XpmSuccess);

    testdir = dir_make_tmp("XpmWrite-test-XXXXXX");
    assert(testdir != NULL);

    filename = path_get_basename(filepath);
    strip_compress_ext(filename);
    newfilepath = build_filename(testdir, filename);

    test_WFFXD_helper(newfilepath, data);

#ifndef NO_ZPIPE
    cmpfilepath = strdup_printf("%s.gz", newfilepath);
    test_WFFXD_helper(cmpfilepath, data);
    free(cmpfilepath);

#  ifdef XPM_PATH_COMPRESS
    cmpfilepath = strdup_printf("%s.Z", newfilepath);
    test_WFFXD_helper(cmpfilepath, data);
    free(cmpfilepath);
#  endif
#endif

    XpmFree(data);

    assert_no_errno(rmdir(testdir));

    free(newfilepath);
    free(filename);
    free(testdir);

    return status;
}

static void
test_XpmWriteFileFromData(void)
{
    /* Todo - verify trying to write to an unwritable file fails */

    TestAllNormalFiles("good", XpmSuccess, TestWriteFileFromData);
    /* XpmReadFileToData calls XpmReadFileToXpmImage so it
       supports compressed files */
    TestAllCompressedFiles("good", XpmSuccess, TestWriteFileFromData);
}

/*
 * XpmWriteFileFromBuffer - helper function to write files & read them back in
 * XpmWriteFileFromBuffer() does not support compressed files.
 */
static int
TestWriteFileFromBuffer(const char *filepath)
{
    char *buffer = NULL;
    char *testdir, *filename, *newfilepath;
    int   status;

    status = XpmReadFileToBuffer(filepath, &buffer);
    assert(status == XpmSuccess);
    assert(buffer != NULL);

    testdir = dir_make_tmp("XpmWrite-test-XXXXXX");
    assert(testdir != NULL);

    filename = path_get_basename(filepath);
    strip_compress_ext(filename);
    newfilepath = build_filename(testdir, filename);
    printf("...writing %s", newfilepath);

    status = XpmWriteFileFromBuffer(newfilepath, buffer);
    assert(status == XpmSuccess);

    if (status == XpmSuccess)
    {
        char    readbuf[8192];
        char   *b = buffer;
        int     fd;
        ssize_t rd;

        /* Read file ourselves and verify the data matches */
        assert_no_errno(fd = open(newfilepath, O_RDONLY | O_CLOEXEC));
        while ((rd = read(fd, readbuf, sizeof(readbuf))) > 0)
        {
            assert(memcmp(b, readbuf, rd) == 0);
            b += rd;
        }
        /* Verify we're at the end of the buffer */
        assert(b[0] == '\0');

        assert_no_errno(close(fd));
        assert_no_errno(remove(newfilepath));
    }
    XpmFree(buffer);

    assert_no_errno(rmdir(testdir));

    free(newfilepath);
    free(filename);
    free(testdir);

    return status;
}

static void
test_XpmWriteFileFromBuffer(void)
{
    /* Todo: verify trying to write to an unwritable file fails */

    TestAllNormalFiles("good", XpmSuccess, TestWriteFileFromBuffer);
    /* XpmReadFileToBuffer does not support compressed files */
}

int
main(int argc, char **argv)
{
    test_XpmWriteFileFromXpmImage();
    test_XpmWriteFileFromData();
    test_XpmWriteFileFromBuffer();
}
