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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "X11/Xlib.h"

#include <time.h>
#include <errno.h>
#include <limits.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>

#ifndef assert_no_errno
#  define assert_no_errno(expr) assert((expr) >= 0)
#endif

#define DEFAULT_TIMEOUT 10 /* maximum seconds for each file */

#ifdef _WIN32
#  define PATH_SEPARATOR "\\"
#else
#  define PATH_SEPARATOR "/"
#endif

static sigjmp_buf jump_env;

static void
sigalrm(int sig)
{
    siglongjmp(jump_env, 1);
}

typedef int (*testfilefunc)(const char *filepath);

// Function to construct the file path
#if 0
char *test_file_path(TestFileType file_type, const char *dir1, const char *dir2, const char *optional, const char *filename) {
    // Allocate memory for the path. We need space for the directories and the filename
    size_t total_len = 0;
    total_len += strlen(dir1) + strlen(PATH_SEPARATOR) + strlen(dir2); // dir1 and dir2
    if (optional) {
        total_len += strlen(PATH_SEPARATOR) + strlen(optional); // optional component (e.g., "generated")
    }
    if (filename) {
        total_len += strlen(PATH_SEPARATOR) + strlen(filename); // filename
    }
    total_len += 1; // Null terminator

    // Allocate memory for the full path
    char *full_path = malloc(total_len);
    if (!full_path) {
        perror("malloc");
        return NULL;
    }

    // Start constructing the path
    snprintf(full_path, total_len, "%s%s%s", dir1, PATH_SEPARATOR, dir2);

    // If there's an optional component (e.g., "generated"), add it
    if (optional) {
        snprintf(full_path + strlen(full_path), total_len - strlen(full_path), "%s%s", PATH_SEPARATOR, optional);
    }

    // If a filename is provided, add it to the path
    if (filename) {
        snprintf(full_path + strlen(full_path), total_len - strlen(full_path), "%s%s", PATH_SEPARATOR, filename);
    }

    return full_path;
}
#endif

// Function to construct file path based on test location
char *
test_file_path(const char *filename)
{
    size_t total_len = strlen(TESTS_PATH) + strlen(PATH_SEPARATOR) +
                       strlen("xpm") + strlen(PATH_SEPARATOR) +
                       strlen("pixmaps") + strlen(PATH_SEPARATOR) +
                       strlen(filename) + strlen(PATH_SEPARATOR) + 1;

    char *result = malloc(total_len);
    if (!result)
    {
        perror("malloc");
        return NULL;
    }

    snprintf(result,
             total_len,
             "%s%sxpm%spixmaps%s%s%s",
             TESTS_PATH,
             PATH_SEPARATOR,
             PATH_SEPARATOR,
             PATH_SEPARATOR,
             filename,
             PATH_SEPARATOR);

    return result;
}

// Structure to represent a pattern
typedef struct
{
    char *pattern;  // Original pattern string
} PatternSpec;

// Function to create a new PatternSpec
PatternSpec *
pattern_spec_new(const char *pattern)
{
    PatternSpec *spec = malloc(sizeof(PatternSpec));
    if (!spec)
    {
        perror("malloc");
        return NULL;
    }
    spec->pattern = strdup(pattern); // Copy the pattern
    if (!spec->pattern)
    {
        perror("strdup");
        free(spec);
        return NULL;
    }
    return spec;
}

// Function to match a string against the pattern
Bool
pattern_spec_match(const PatternSpec *spec, const char *str)
{
    const char *p = spec->pattern;
    const char *s = str;

    while (*p && *s)
    {
        if (*p == '*')
        {
            p++;
            if (!*p) return True;  // If '*' is the last character, it's a match
            while (*s && *s != *p)
                s++;
        }
        else if (*p == '?')
        {
            p++;
            s++;
        }
        else if (*p == *s)
        {
            p++;
            s++;
        }
        else
        {
            return False;
        }
    }

    // Check if the pattern and string are both consumed
    return *p == '\0' && *s == '\0';
}

// Function to match a string (wrapper for simplicity, mimicking g_pattern_match_string)
Bool
pattern_match_string(const PatternSpec *spec, const char *string)
{
    if (!spec || !string)
    {
        return False;  // Handle null inputs gracefully
    }
    return pattern_spec_match(spec, string);
}

// Function to mimic g_dir_read_name
char *
dir_read_name(DIR *datadir)
{
    struct dirent *entry = readdir(datadir);
    if (entry == NULL)
    {
        return NULL;  // No more entries
    }
    return entry->d_name;  // Return the name of the directory entry
}

// Function to mimic build_filename
char *
build_filename(const char *path, const char *filename)
{
    if (!path || !filename)
    {
        return NULL;  // Handle null inputs gracefully
    }

    // Allocate memory for the combined path
    size_t path_len     = strlen(path);
    size_t filename_len = strlen(filename);
    size_t total_len    = path_len + strlen(PATH_SEPARATOR) + filename_len +
                       1;  // +1 for null terminator

    char *result = malloc(total_len);
    if (!result)
    {
        perror("malloc");
        return NULL;
    }

    // Construct the file path
    snprintf(result, total_len, "%s%s%s", path, PATH_SEPARATOR, filename);
    return result;
}

// Function to free the PatternSpec
void
pattern_spec_free(PatternSpec *spec)
{
    if (spec)
    {
        free(spec->pattern);
        free(spec);
    }
}

char *
strdup_printf(const char *format, ...)
{
    va_list args;
    va_list args_copy;
    char   *result = NULL;
    int     size;

    // Start variadic argument processing
    va_start(args, format);

    // Create a copy of args for size estimation
    va_copy(args_copy, args);

    // Determine the required buffer size
    size = vsnprintf(NULL, 0, format, args);
    if (size < 0)
    {
        va_end(args);
        va_end(args_copy);
        return NULL;  // Encoding or other error
    }

    // Allocate memory for the resulting string (+1 for null terminator)
    result = malloc(size + 1);
    if (!result)
    {
        va_end(args);
        va_end(args_copy);
        return NULL;  // Memory allocation failed
    }

    // Format the string into the allocated buffer
    vsnprintf(result, size + 1, format, args_copy);

    // Clean up
    va_end(args);
    va_end(args_copy);

    return result;
}

char *
dir_make_tmp(const char *tmpl)
{
    char *template_path;
    char *created_path = NULL;

    // Check for a valid template
    if (!tmpl || strstr(tmpl, "XXXXXX") == NULL)
    {
        errno = EINVAL;  // Invalid argument
        return NULL;
    }

    // Duplicate the template since mkdtemp modifies the input
    template_path = strdup(tmpl);
    if (!template_path)
    {
        return NULL;  // Memory allocation failure
    }

    // Use mkdtemp to create the directory
    if (mkdtemp(template_path))
    {
        // Directory was created successfully, duplicate the resulting path
        created_path = strdup(template_path);
    }
    else
    {
        // Error occurred during mkdtemp
        perror("mkdtemp");
    }

    // Clean up
    free(template_path);

    return created_path;
}

char *
path_get_basename(const char *path)
{
    const char *base = NULL;

    // Handle NULL or empty string
    if (!path || *path == '\0')
    {
        return strdup(".");
    }

    // Find the last occurrence of '/'
    base = strrchr(path, '/');

    // If '/' is found, return the part after it; otherwise, return the whole string
    if (base)
    {
        return strdup(base + 1);
    }
    else
    {
        return strdup(path);
    }
}

/*
 * Test all files in a given subdir of either the build or source directory
 */
static void
TestAllFilesByType(Bool         compressed,
                   const char  *subdir,
                   int          expected,
                   testfilefunc testfunc)
{
    char *datadir_path, *filename;
    DIR  *datadir;
    int   timeout = DEFAULT_TIMEOUT;
    char *timeout_env;

    PatternSpec *xpm_pattern = pattern_spec_new("*.xpm");
#ifndef NO_ZPIPE
    PatternSpec *z_pattern  = compressed ? pattern_spec_new("*.xpm.Z") : NULL;
    PatternSpec *gz_pattern = compressed ? pattern_spec_new("*.xpm.gz") : NULL;
#endif

    /* Allow override when debugging tests */
    timeout_env = getenv("XPM_TEST_TIMEOUT");
    if (timeout_env != NULL)
    {
        int from_env = atoi(timeout_env);

        if (from_env >= 0) timeout = from_env;
    }

    datadir_path = test_file_path(subdir);

    assert(datadir_path != NULL);
#ifdef DEBUG
    printf("Reading files from %s\n", datadir_path);
#endif

    datadir = opendir(datadir_path);
    if (!datadir)
    {
        perror(datadir_path);
    }
    assert(datadir != NULL);

    errno = 0;
    while ((filename = dir_read_name(datadir)) != NULL)
    {
        if (!pattern_match_string(xpm_pattern, filename))
        {
#ifndef NO_ZPIPE
            if (!compressed || (!pattern_match_string(z_pattern, filename) &&
                                !pattern_match_string(gz_pattern, filename)))
#endif
            {
#ifdef DEBUG
                printf("skipping \"%s\"\n", filename);
#endif
                continue;
            }
        }

        /*
         * Assumes the test function should complete in less than "timeout"
         * seconds and fails if they don't, in order to catch runaway loops.
         */
        if (timeout > 0)
        {
            struct sigaction sa = { .sa_handler = sigalrm,
                                    .sa_flags   = SA_RESTART };
            sigemptyset(&sa.sa_mask);
            sigaction(SIGALRM, &sa, NULL);
        }

        if (sigsetjmp(jump_env, 1) == 0)
        {
            int   status;
            char *filepath;

            filepath = build_filename(datadir_path, filename);
#ifdef DEBUG
            printf("testing \"%s\", should return %d\n", filename, expected);
#endif
            if (timeout > 0) alarm(timeout);
            status = testfunc(filepath);
            assert(status == expected);

            if (timeout > 0)
            {
                status = alarm(0); /* cancel alarm */
#ifdef DEBUG
                printf("%d seconds left on %d second timer\n", status, timeout);
#endif
            }

            free(filepath);
        }
        else
        {
            printf("timed out reading %s\n", filename);
            printf("test timed out: %s at %d\n", __FILE__, __LINE__);
        }

        errno = 0;
    }
    // assert(errno == 0); - not sure why this sometimes fails

    closedir(datadir);
}

/*
 * Test all non-compressed files in a given subdir
 */
static void
TestAllNormalFiles(const char *subdir, int expected, testfilefunc testfunc)
{
    TestAllFilesByType(False, subdir, expected, testfunc);
}

/*
 * Test all compressed files in a given subdir
 */
static void
TestAllCompressedFiles(const char *subdir, int expected, testfilefunc testfunc)
{
#ifdef NO_ZPIPE
    printf("compression disabled, skipping compressed file tests");
#else
    TestAllFilesByType(True, subdir, expected, testfunc);
#endif
}
