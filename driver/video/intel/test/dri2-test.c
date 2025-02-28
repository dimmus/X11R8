#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/extensions/Xfixes.h"
#include "X11/extensions/Xrandr.h"
#include "X11/Xlib-xcb.h"
#include <xcb/xcb.h>
#include <xcb/xcbext.h>
#include <xcb/dri2.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#include <xf86drm.h>
#include <drm.h>

#include "dri2.h"

#define COUNT 60

static int prime[] = { 0,  1,  2,  3,  5,  7,   11,  13,  17,  19,  23,  27,
                       29, 31, 37, 41, 43, 47,  51,  53,  59,  61,  67,  71,
                       73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131 };

static inline XRRScreenResources *
_XRRGetScreenResourcesCurrent(Display *dpy, Window window)
{
    XRRScreenResources *res;

    res = XRRGetScreenResourcesCurrent(dpy, window);
    if (res == NULL) res = XRRGetScreenResources(dpy, window);

    return res;
}

static XRRModeInfo *
lookup_mode(XRRScreenResources *res, int id)
{
    int i;

    for (i = 0; i < res->nmode; i++)
    {
        if (res->modes[i].id == id) return &res->modes[i];
    }

    return NULL;
}

static int
dri2_open(Display *dpy)
{
    drm_auth_t auth;
    char      *driver, *device;
    int        fd;

    if (!DRI2Connect(dpy, DefaultRootWindow(dpy), &driver, &device)) return -1;

    printf("Connecting to %s driver on %s\n", driver, device);

    fd = open(device, O_RDWR);
    if (fd < 0) return -1;

    if (drmIoctl(fd, DRM_IOCTL_GET_MAGIC, &auth)) return -1;

    if (!DRI2Authenticate(dpy, DefaultRootWindow(dpy), auth.magic)) return -1;

    return fd;
}

static void
dri2_copy_swap(Display *dpy, Drawable d, int width, int height, int has_front)
{
    XRectangle    rect;
    XserverRegion region;

    rect.x      = 0;
    rect.y      = 0;
    rect.width  = width;
    rect.height = height;

    region = XFixesCreateRegion(dpy, &rect, 1);
    DRI2CopyRegion(dpy, d, region, DRI2BufferFrontLeft, DRI2BufferBackLeft);
    if (has_front)
        DRI2CopyRegion(dpy,
                       d,
                       region,
                       DRI2BufferFakeFrontLeft,
                       DRI2BufferFrontLeft);
    XFixesDestroyRegion(dpy, region);
}

static double
elapsed(const struct timespec *start, const struct timespec *end)
{
    return (end->tv_sec - start->tv_sec) +
           1e-9 * (end->tv_nsec - start->tv_nsec);
}

static uint64_t
check_msc(Display *dpy, Window win, uint64_t last_msc)
{
    uint64_t current_msc, current_ust, current_sbc;
    DRI2GetMSC(dpy, win, &current_ust, &current_msc, &current_sbc);
    if (current_msc < last_msc)
    {
        printf("Invalid MSC: was %llu, now %llu\n",
               (long long)last_msc,
               (long long)current_msc);
    }
    return current_msc;
}

static void
wait_next_vblank(Display *dpy, Window win)
{
    uint64_t msc, ust, sbc;
    DRI2WaitMSC(dpy, win, 0, 1, 0, &ust, &msc, &sbc);
}

static void
swap_buffers(xcb_connection_t *c,
             Window            win,
             unsigned int     *attachments,
             int               nattachments)
{
    unsigned int seq[2];

    seq[0] = xcb_dri2_swap_buffers_unchecked(c, win, 0, 0, 0, 0, 0, 0).sequence;

    seq[1] = xcb_dri2_get_buffers_unchecked(c,
                                            win,
                                            nattachments,
                                            nattachments,
                                            attachments)
                 .sequence;

    xcb_flush(c);
    xcb_discard_reply(c, seq[0]);
    xcb_discard_reply(c, seq[1]);
}

static void
run(Display      *dpy,
    int           width,
    int           height,
    unsigned int *attachments,
    int           nattachments,
    const char   *name)
{
    xcb_connection_t    *c = XGetXCBConnection(dpy);
    Window               win;
    XSetWindowAttributes attr;
    DRI2Buffer          *buffers;
    struct timespec      start, end;
    uint64_t             start_msc, end_msc;
    int                  modulus, remainder, count;

    /* Be nasty and install a fullscreen window on top so that we
	 * can guarantee we do not get clipped by children.
	 */
    attr.override_redirect = 1;
    win                    = XCreateWindow(dpy,
                        DefaultRootWindow(dpy),
                        0,
                        0,
                        width,
                        height,
                        0,
                        DefaultDepth(dpy, DefaultScreen(dpy)),
                        InputOutput,
                        DefaultVisual(dpy, DefaultScreen(dpy)),
                        CWOverrideRedirect,
                        &attr);
    XMapWindow(dpy, win);

    DRI2CreateDrawable(dpy, win);
    DRI2SwapInterval(dpy, win, 1);
    start_msc = check_msc(dpy, win, 0);

    buffers = DRI2GetBuffers(dpy,
                             win,
                             &width,
                             &height,
                             attachments,
                             nattachments,
                             &count);
    if (count != nattachments) return;

    swap_buffers(c, win, attachments, nattachments);
    start_msc = check_msc(dpy, win, start_msc);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (count = 0; count < COUNT; count++)
        swap_buffers(c, win, attachments, nattachments);
    end_msc = check_msc(dpy, win, start_msc);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%d [%ld] %s (%dx%d) swaps in %fs.\n",
           count,
           (long)(end_msc - start_msc),
           name,
           width,
           height,
           elapsed(&start, &end));

    swap_buffers(c, win, attachments, nattachments);
    start_msc = check_msc(dpy, win, end_msc);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (count = 0; count < COUNT; count++)
        dri2_copy_swap(dpy, win, width, height, nattachments == 2);
    end_msc = check_msc(dpy, win, start_msc);
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("%d [%ld] %s (%dx%d) blits in %fs.\n",
           count,
           (long)(end_msc - start_msc),
           name,
           width,
           height,
           elapsed(&start, &end));

    DRI2SwapInterval(dpy, win, 0);
    wait_next_vblank(dpy, win);

    swap_buffers(c, win, attachments, nattachments);
    start_msc = check_msc(dpy, win, end_msc);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (count = 0; count < COUNT; count++)
        swap_buffers(c, win, attachments, nattachments);
    end_msc = check_msc(dpy, win, start_msc);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%d [%ld] %s (%dx%d) vblank=0 swaps in %fs.\n",
           count,
           (long)(end_msc - start_msc),
           name,
           width,
           height,
           elapsed(&start, &end));

    start_msc = check_msc(dpy, win, end_msc);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (count = 0; count < COUNT; count++)
        wait_next_vblank(dpy, win);
    end_msc = check_msc(dpy, win, start_msc);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%d [%ld] %s waits in %fs.\n",
           count,
           (long)(end_msc - start_msc),
           name,
           elapsed(&start, &end));

    printf("Testing past & future waits\n");
    for (modulus = 1; modulus <= 128; modulus <<= 1)
    {
        for (count = 0; prime[count] < modulus; count++)
        {
            uint64_t msc, ust, sbc;
            uint64_t target;

            remainder = prime[count];

            DRI2WaitMSC(dpy, win, 0, 1, 0, &ust, &msc, &sbc);

            target = msc + modulus + 1;
            target &= -modulus;
            target += remainder;

            DRI2WaitMSC(dpy, win, target, modulus, remainder, &ust, &msc, &sbc);
            if (msc != target)
            {
                printf(
                    "Missed future MSC (%d, %d): expected=%lld, found=%lld\n",
                    modulus,
                    remainder,
                    (long long)target,
                    (long long)msc);
            }

            target = msc;
            target &= -modulus;
            target += remainder;
            if (target <= msc) target += modulus;

            DRI2WaitMSC(dpy, win, msc, modulus, remainder, &ust, &msc, &sbc);

            if (msc != target)
            {
                printf("Missed past MSC (%d, %d): expected=%lld, found=%lld\n",
                       modulus,
                       remainder,
                       (long long)target,
                       (long long)msc);
            }
        }
    }

    XDestroyWindow(dpy, win);
    free(buffers);

    XSync(dpy, 1);
}

int
main(void)
{
    Display     *dpy;
    int          i, j, fd;
    unsigned int attachments[] = {
        DRI2BufferBackLeft,
        DRI2BufferFrontLeft,
    };
    XRRScreenResources *res;
    XRRCrtcInfo       **original_crtc;
    Window              root;
    uint64_t            last_msc;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) return 77;

    if (!XRRQueryVersion(dpy, &i, &j)) return 77;

    fd = dri2_open(dpy);
    if (fd < 0) return 1;

    root = DefaultRootWindow(dpy);
    DRI2CreateDrawable(dpy, root);

    res = _XRRGetScreenResourcesCurrent(dpy, root);
    if (res == NULL) return 1;

    original_crtc = malloc(sizeof(XRRCrtcInfo *) * res->ncrtc);
    for (i = 0; i < res->ncrtc; i++)
        original_crtc[i] = XRRGetCrtcInfo(dpy, res, res->crtcs[i]);

    printf("noutput=%d, ncrtc=%d\n", res->noutput, res->ncrtc);
    last_msc = check_msc(dpy, root, 0);
    for (i = 0; i < res->ncrtc; i++)
        XRRSetCrtcConfig(dpy,
                         res,
                         res->crtcs[i],
                         CurrentTime,
                         0,
                         0,
                         None,
                         RR_Rotate_0,
                         NULL,
                         0);
    last_msc = check_msc(dpy, root, last_msc);

    for (i = 0; i < res->noutput; i++)
    {
        XRROutputInfo *output;
        XRRModeInfo   *mode;

        output = XRRGetOutputInfo(dpy, res, res->outputs[i]);
        if (output == NULL) continue;

        mode = NULL;
        if (res->nmode) mode = lookup_mode(res, output->modes[0]);

        for (j = 0; mode && j < 2 * output->ncrtc; j++)
        {
            int c = j;
            if (c >= output->ncrtc) c = 2 * output->ncrtc - j - 1;

            printf("[%d, %d] -- OUTPUT:%ld, CRTC:%ld\n",
                   i,
                   c,
                   (long)res->outputs[i],
                   (long)output->crtcs[c]);
            last_msc = check_msc(dpy, root, last_msc);
            XRRSetCrtcConfig(dpy,
                             res,
                             output->crtcs[c],
                             CurrentTime,
                             0,
                             0,
                             output->modes[0],
                             RR_Rotate_0,
                             &res->outputs[i],
                             1);
            last_msc = check_msc(dpy, root, last_msc);

            run(dpy, mode->width, mode->height, attachments, 1, "fullscreen");
            run(dpy,
                mode->width,
                mode->height,
                attachments,
                2,
                "fullscreen (with front)");

            run(dpy,
                mode->width / 2,
                mode->height / 2,
                attachments,
                1,
                "windowed");
            run(dpy,
                mode->width / 2,
                mode->height / 2,
                attachments,
                2,
                "windowed (with front)");

            last_msc = check_msc(dpy, root, last_msc);
            XRRSetCrtcConfig(dpy,
                             res,
                             output->crtcs[c],
                             CurrentTime,
                             0,
                             0,
                             None,
                             RR_Rotate_0,
                             NULL,
                             0);
            last_msc = check_msc(dpy, root, last_msc);
        }

        XRRFreeOutputInfo(output);
    }

    for (i = 0; i < res->ncrtc; i++)
        XRRSetCrtcConfig(dpy,
                         res,
                         res->crtcs[i],
                         CurrentTime,
                         original_crtc[i]->x,
                         original_crtc[i]->y,
                         original_crtc[i]->mode,
                         original_crtc[i]->rotation,
                         original_crtc[i]->outputs,
                         original_crtc[i]->noutput);
    return 0;
}
