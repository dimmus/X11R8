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

## VMMouse

The VMMouse driver enables support for the special VMMouse protocol
that is provided by VMware virtual machines to give absolute pointer
positioning. 

Installing the driver will improve the user experience when using the 
mouse to interact with the guest operating system. In particular, use of 
the driver improves mouse "lag", provides mouse speed and acceleration 
consistent with the user's host operating system, and enables the 
auto-grab/ungrab feature in VMware products without requiring the VMware 
toolbox application.

Using the driver
----------------

Assuming you have built and installed the driver in the standard way
for autotools based packages (see INSTALL), or the driver was already
installed by your distro, using it is simply a matter of changing the
driver used for the mouse input device from "mouse" to "vmmouse".

The vmmouse driver is capable of falling back to the standard "mouse"
driver if a VMware virtual machine is not detected. This allows for
dual-booting of an operating system from a virtual machine to real hardware
without having to edit xorg.conf every time.

Implementation
--------------

The following is not necessary reading for anyone who wants to use the
driver, but should help anyone who wants to understand how it works or
who wants to write a driver for a different target, whether it's another
operating system, a linux kernel input driver or even gpm.

The driver is composed of three different layers:

1) The vmmouse protocol layer (vmmouse_proto.[c|h])
   - This provides the call to read and write the port over which 
     the vmmouse packets are transfered.

2) The vmmouse client layer (vmmouse_client.[c|h])
   - This builds on top of the protocol layer to provide higher
     level calls for enabling/disabling the vmmouse mechanism
     and for reading data.
   - A new driver for a different target would use this interface.

3) The Xorg vmmouse driver (vmmouse.c)
   - This is the actual Xorg specific part of the driver.
   - Note that interrupts indicating the presence of mouse data
     are still transmitted on the PS/2 port so it is necessary
     to be set up to receive those interrupts like a standard
     PS/2 driver, but the actual data on the PS/2 port is ignored.

vmmouse_detect
--------------

A simple program to detect whether the vmmouse device is present.
It is used by the HAL callout script to automatically detect a
vmmouse device.

Returns 0 if we are running in a virtual machine where the vmmouse
device is present.

Returns 1 otherwise (either we are not in a VM or the vmmouse device
was disabled).

## xf86-input-evdev

Generic Linux input driver for the Xorg X server

The primary development code repository can be found at:
https://gitlab.freedesktop.org/xorg/driver/xf86-input-evdev

## xf86-input-libinput

A libinput-based X driver

The official repository for this driver is
https://gitlab.freedesktop.org/xorg/driver/xf86-input-libinput

This is an X driver based on libinput. It is a thin wrapper around libinput,
so while it does provide all features that libinput supports it does little
beyond.

***WARNING: misconfiguration of an X input driver may leave you without
usable input devices in your X session. Use with caution.***


Prerequisites
-------------

To build, you'll need the X.Org X server SDK (check your distribution for a
xorg-x11-server-devel package or similar) and libinput (check your
distribution for libinput-devel or similar).

To get libinput from source, see:
https://www.freedesktop.org/wiki/Software/libinput/

To build the X server from source:
https://www.x.org/wiki/Building_the_X_Window_System/

Building
--------

To build this driver:

    autoreconf -vif
    ./configure --prefix=$HOME/build
    make && make install

Note that this assumes the same prefix as used in "Building the X Window
System" above, adjust as required. If you want a system install, use a
prefix of */usr*.

Install the default configuration file:

    cp conf/99-libinput.conf /etc/X11/xorg.conf.d/

This will assign this driver to *all* devices. Use with caution.

Bugs
----

Bugs in libinput go to the Issues section of the libinput gitlab project:
https://gitlab.freedesktop.org/libinput/libinput/issues

Bugs in this driver go to the Issues section of its gitlab project:
https://gitlab.freedesktop.org/xorg/driver/xf86-input-libinput/issues

## xf86-input-void

null input driver for Xorg server

The primary development code repository can be found at:
https://gitlab.freedesktop.org/xorg/driver/xf86-input-void