---
title: X Window System Drivers
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

# X Window System Drivers

## Vesa

xf86-video-vesa - Generic VESA video driver for the Xorg X server
https://gitlab.freedesktop.org/xorg/driver/xf86-video-vesa

## VMWare

Copyright (C) 1999-2009 VMware, Inc.
All Rights Reserved

The code here may be used/distributed under the terms of the standard
XFree86 license.

Documentation on the VMware SVGA Device programming model
has been updated and expanded, and it now lives at:

http://vmware-svga.sourceforge.net/

## VBox

xf86-video-vboxvideo - VirtualBox video driver for the Xorg X server
--------------------------------------------------------------------

This driver is only for use in VirtualBox guests without the
vboxvideo kernel modesetting driver in the guest kernel, and
which are configured to use the VBoxVGA device instead of a
VMWare-compatible video device emulation.

Guests with the vboxvideo kernel modesetting driver should use the
Xorg "modesetting" driver module instead of this one.

https://gitlab.freedesktop.org/xorg/driver/xf86-video-vbox

## FBdev

xf86-video-fbdev - video driver for framebuffer device
https://gitlab.freedesktop.org/xorg/driver/xf86-video-fbdev

## Dummy

xf86-video-dummy - virtual/offscreen frame buffer driver for the Xorg X server
https://gitlab.freedesktop.org/xorg/driver/xf86-video-dummy

## ATI (Radeon)

xf86-video-ati - Xorg driver for ATI/AMD Radeon GPUs using the radeon kernel driver
Questions regarding this software should be directed at: 
https://lists.freedesktop.org/mailman/listinfo/amd-gfx
https://gitlab.freedesktop.org/xorg/driver/xf86-video-ati

## QXL

The QXL virtual GPU is found in the Red Hat Enterprise
Virtualisation system, and also in the spice project.

https://gitlab.freedesktop.org/xorg/driver/xf86-video-qxl