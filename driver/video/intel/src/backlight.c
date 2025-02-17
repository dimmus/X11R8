/***************************************************************************

 Copyright 2014 Intel Corporation.  All Rights Reserved.
 Copyright 2014 Red Hat, Inc.

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sub license, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice (including the
 next paragraph) shall be included in all copies or substantial portions
 of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 IN NO EVENT SHALL INTEL, AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 **************************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config_intel.h"
#endif

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#ifdef MAJOR_IN_MKDEV
#  include <sys/mkdev.h>
#elif MAJOR_IN_SYSMACROS
#  include <sys/sysmacros.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include <xorg-server.h>
#include <xf86.h>
#include <pciaccess.h>
#include <os/osdep.h>

#include "backlight.h"
#include "fd.h"

#define BACKLIGHT_CLASS "/sys/class/backlight"

/* Enough for 10 digits of backlight + '\n' + '\0' */
#define BACKLIGHT_VALUE_LEN 12

#ifndef ARRAY_SIZE
#  define ARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))
#endif

/*
 * Unfortunately this is not as simple as I would like it to be. If selinux is
 * dropping dbus messages pkexec may block *forever*.
 *
 * Backgrounding pkexec by doing System("pkexec ...&") does not work because
 * that detaches pkexec from its parent at which point its security checks
 * fail and it refuses to execute the helper.
 *
 * So we're left with spawning a helper child which gets levels to set written
 * to it through a pipe. This turns the blocking forever problem from a hung
 * machine problem into a simple backlight control not working problem.
 *
 * If only things were as simple as on OpenBSD! :)
 */

void
backlight_init(struct backlight *b)
{
    b->type      = BL_NONE;
    b->iface     = NULL;
    b->fd        = -1;
    b->pid       = -1;
    b->max       = -1;
    b->has_power = 0;
}

#ifdef HAVE_DEV_WSCONS_WSCONSIO_H

#  include <dev/wscons/wsconsio.h>
#  include <xf86Priv.h>

int
backlight_set(struct backlight *b, int level)
{
    struct wsdisplay_param param;

    if (b->iface == NULL) return -1;

    if ((unsigned)level > b->max) level = b->max;

    memset(&param, 0, sizeof(param));
    param.param  = WSDISPLAYIO_PARAM_BRIGHTNESS;
    param.curval = level;

    return ioctl(xf86Info.consoleFd, WSDISPLAYIO_SETPARAM, &param);
}

int
backlight_get(struct backlight *b)
{
    struct wsdisplay_param param;

    if (b->iface == NULL) return -1;

    memset(&param, 0, sizeof(param));
    param.param = WSDISPLAYIO_PARAM_BRIGHTNESS;

    if (ioctl(xf86Info.consoleFd, WSDISPLAYIO_GETPARAM, &param)) return -1;

    return param.curval;
}

char *
backlight_find_for_device(struct pci_device *pci)
{
    return NULL;
}

int
backlight_open(struct backlight *b, char *iface)
{
    struct wsdisplay_param param;

    if (iface != NULL) return -1;

    memset(&param, 0, sizeof(param));
    param.param = WSDISPLAYIO_PARAM_BRIGHTNESS;

    if (ioctl(xf86Info.consoleFd, WSDISPLAYIO_GETPARAM, &param) == -1)
        return -1;

    b->iface = strdup("wscons");
    if (b->iface == NULL) return -1;

    b->max  = param.max;
    b->fd   = -1;
    b->type = BL_PLATFORM;

    return param.curval;
}

int
backlight_exists(const char *iface)
{
    return iface == NULL;
}

int
backlight_on(struct backlight *b)
{
    return 0;
}

int
backlight_off(struct backlight *b)
{
    return 0;
}

#else

static int
is_sysfs_fd(int fd)
{
    struct stat st;
    return fstat(fd, &st) == 0 && major(st.st_dev) == 0;
}

static int
__backlight_open(const char *iface, const char *file, int mode)
{
    char buf[1024];
    int  fd;

    snprintf(buf, sizeof(buf), BACKLIGHT_CLASS "/%s/%s", iface, file);
    fd = open(buf, mode);
    if (fd == -1) return -1;

    if (!is_sysfs_fd(fd))
    {
        close(fd);
        return -1;
    }

    return fd;
}

static int
__backlight_read(const char *iface, const char *file)
{
    char buf[BACKLIGHT_VALUE_LEN];
    int  fd, val;

    fd = __backlight_open(iface, file, O_RDONLY);
    if (fd < 0) return -1;

    val = read(fd, buf, BACKLIGHT_VALUE_LEN - 1);
    if (val > 0)
    {
        buf[val] = '\0';
        val      = atoi(buf);
    }
    else val = -1;
    close(fd);

    return val;
}

static int
writen(int fd, const char *value, int len)
{
    int ret;

    do
    {
        ret = write(fd, value, len);
        if (ret < 0)
        {
            if (errno == EAGAIN || errno == EINTR) continue;

            return ret;
        }
    }
    while (value += ret, len -= ret);

    return 0;
}

static int
__backlight_write(const char *iface, const char *file, const char *value)
{
    int fd, ret;

    fd = __backlight_open(iface, file, O_WRONLY);
    if (fd < 0) return -1;

    ret = writen(fd, value, strlen(value) + 1);
    close(fd);

    return ret;
}

/* List of available kernel interfaces in priority order */
static const char *known_interfaces[] = {
    "dell_backlight",  "gmux_backlight", "asus-laptop",
    "asus-nb-wmi",     "eeepc",          "thinkpad_screen",
    "mbp_backlight",   "fujitsu-laptop", "sony",
    "samsung",         "acpi_video1",    "acpi_video0",
    "intel_backlight",
};

static int
__backlight_type(const char *iface)
{
    char buf[1024];
    int  fd, v, i;

    v  = -1;
    fd = __backlight_open(iface, "type", O_RDONLY);
    if (fd >= 0)
    {
        v = read(fd, buf, sizeof(buf) - 1);
        close(fd);
    }
    if (v > 0)
    {
        while (v > 0 && isspace(buf[v - 1]))
            v--;
        buf[v] = '\0';

        if (strcmp(buf, "raw") == 0) v = BL_RAW << 8;
        else if (strcmp(buf, "platform") == 0) v = BL_PLATFORM << 8;
        else if (strcmp(buf, "firmware") == 0) v = BL_FIRMWARE << 8;
        else v = BL_NAMED << 8;
    }
    else v = BL_NAMED << 8;

    for (i = 0; i < ARRAY_SIZE(known_interfaces); i++)
    {
        if (strcmp(iface, known_interfaces[i]) == 0) break;
    }
    v += i;

    return v;
}

static int
__backlight_exists(const char *iface)
{
    if (__backlight_read(iface, "brightness") < 0) return -1;

    if (__backlight_read(iface, "max_brightness") <= 0) return -1;

    return __backlight_type(iface);
}

int
backlight_exists(const char *iface)
{
    return __backlight_exists(iface) != -1;
}

static int
__backlight_init(struct backlight *b, char *iface, int fd)
{
    b->fd    = fd_move_cloexec(fd_set_nonblock(fd));
    b->iface = iface;
    return 1;
}

static int
__backlight_direct_init(struct backlight *b, char *iface)
{
    int fd;

    fd = __backlight_open(iface, "brightness", O_RDWR);
    if (fd < 0) return 0;

    if (__backlight_read(iface, "bl_power") != -1) b->has_power = 1;

    return __backlight_init(b, iface, fd);
}

static int
__backlight_helper_init(struct backlight *b, char *iface)
{
#  ifdef USE_BACKLIGHT_HELPER
    struct stat st;
    char       *env[]      = { NULL };
    int         use_pkexec = 0;
    int         fds[2];

    /*
	 * Some systems may prefer using PolicyKit's pkexec over
	 * making the helper suid root, since the suid option will allow
	 * anyone to control the backlight.  However, as pkexec
	 * is quite troublesome and not universally available, we
	 * still try the old fashioned and simple method first.
	 * Either way, we have to trust that it is our backlight-helper
	 * that is run and that we have scrutinised it carefully.
	 */
    if (stat(LIBEXEC_PATH "/xf86-video-intel-backlight-helper", &st)) return 0;

    if ((st.st_mode & (S_IFREG | S_ISUID | S_IXUSR)) !=
        (S_IFREG | S_ISUID | S_IXUSR))
    {
        if (system("pkexec --version")) return 0;

        use_pkexec = 1;
    }

    if (pipe(fds)) return 0;

    switch ((b->pid = fork()))
    {
        case 0:
            if (setgid(getgid()) || setuid(getuid())) _exit(127);

            close(fds[1]);
            if (dup2(fds[0], 0)) _exit(127);
            close(fds[0]);

            if (use_pkexec)
            {
                execlp("pkexec",
                       "pkexec",
                       LIBEXEC_PATH "/xf86-video-intel-backlight-helper",
                       iface,
                       (char *)0);
            }
            else
            {
                execle(LIBEXEC_PATH "/xf86-video-intel-backlight-helper",
                       "xf86-video-intel-backlight-helper",
                       iface,
                       (char *)0,
                       env);
            }
            _exit(1);
        /* unreachable fallthrough */
        case -1:
            close(fds[1]);
            close(fds[0]);
            return 0;

        default:
            close(fds[0]);
            return __backlight_init(b, iface, fds[1]);
    }
#  else
    return 0;
#  endif
}

static char *
__backlight_find(void)
{
    char          *best_iface = NULL;
    unsigned       best_type  = INT_MAX;
    DIR           *dir;
    struct dirent *de;

    dir = opendir(BACKLIGHT_CLASS);
    if (dir == NULL) return NULL;

    while ((de = readdir(dir)))
    {
        int v;

        if (*de->d_name == '.') continue;

        /* Fallback to priority list of known iface for old kernels */
        v = __backlight_exists(de->d_name);
        if (v < 0) continue;

        if (v < best_type)
        {
            char *copy = strdup(de->d_name);
            if (copy)
            {
                free(best_iface);
                best_iface = copy;
                best_type  = v;
            }
        }
    }
    closedir(dir);

    return best_iface;
}

char *
backlight_find_for_device(struct pci_device *pci)
{
    char           path[200];
    unsigned       best_type  = INT_MAX;
    char          *best_iface = NULL;
    DIR           *dir;
    struct dirent *de;

    snprintf(path,
             sizeof(path),
             "/sys/bus/pci/devices/%04x:%02x:%02x.%d/backlight",
             pci->domain,
             pci->bus,
             pci->dev,
             pci->func);

    dir = opendir(path);
    if (dir == NULL) return NULL;

    while ((de = readdir(dir)))
    {
        int v;

        if (*de->d_name == '.') continue;

        v = __backlight_exists(de->d_name);
        if (v < 0) continue;

        if (v < best_type)
        {
            char *copy = strdup(de->d_name);
            if (copy)
            {
                free(best_iface);
                best_iface = copy;
                best_type  = v;
            }
        }
    }
    closedir(dir);

    return best_iface;
}

int
backlight_open(struct backlight *b, char *iface)
{
    int level, type;

    if (iface == NULL) iface = __backlight_find();
    if (iface == NULL) goto err;

    type = __backlight_type(iface);
    if (type < 0) goto err;
    b->type = type >> 8;

    b->max = __backlight_read(iface, "max_brightness");
    if (b->max <= 0) goto err;

    level = __backlight_read(iface, "brightness");
    if (level < 0) goto err;

    if (!__backlight_direct_init(b, iface) &&
        !__backlight_helper_init(b, iface))
        goto err;

    return level;

err:
    backlight_init(b);
    return -1;
}

int
backlight_set(struct backlight *b, int level)
{
    char val[BACKLIGHT_VALUE_LEN];
    int  len;

    if (b->iface == NULL) return 0;

    if ((unsigned)level > b->max) level = b->max;

    len = snprintf(val, BACKLIGHT_VALUE_LEN, "%d\n", level);
    return writen(b->fd, val, len);
}

int
backlight_get(struct backlight *b)
{
    int level;

    if (b->iface == NULL) return -1;

    level = __backlight_read(b->iface, "brightness");
    if (level > b->max) level = b->max;
    else if (level < 0) level = -1;
    return level;
}

int
backlight_off(struct backlight *b)
{
    if (b->iface == NULL) return 0;

    if (!b->has_power) return 0;

    /* 4 -> FB_BLANK_POWERDOWN */
    return __backlight_write(b->iface, "bl_power", "4");
}

int
backlight_on(struct backlight *b)
{
    if (b->iface == NULL) return 0;

    if (!b->has_power) return 0;

    /* 0 -> FB_BLANK_UNBLANK */
    return __backlight_write(b->iface, "bl_power", "0");
}
#endif

void
backlight_disable(struct backlight *b)
{
    if (b->iface == NULL) return;

    if (b->fd != -1) close(b->fd);

    free(b->iface);
    b->iface = NULL;
}

void
backlight_close(struct backlight *b)
{
    backlight_disable(b);
    if (b->pid > 0) waitpid(b->pid, NULL, 0);
}
