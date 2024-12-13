---
title: X Window System Extension Libraries
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

<!-- ./extensions/xf86vm -->

## Xxf86vm - Extension library for the XFree86-VidMode X extension

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXxf86vm


<!-- ./extensions/xdamage -->

## Xdamage - X Damage Extension library

This package contains the library for the X Damage extension.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXdamage


<!-- ./extensions/xvmc -->

## XvMC - X-Video Motion Compensation API

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXvMC


<!-- ./extensions/xrender -->

## Xrender - library for the Render Extension to the X11 protocol

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXrender


<!-- ./extensions/xinerama -->

## Xinerama - API for Xinerama extension to X11 Protocol

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXinerama


<!-- ./extensions/dmx -->

## dmx - Distributed Multihead X extension library

This library allows X11 clients to use the Distributed Multihead X (DMX)
Extension, as previously implemented in the Xdmx server.  X.Org removed
support for the Xdmx server from the xorg-server releases in the version 21
release in 2021.   This library is thus now considered deprecated and the
version 1.1.5 release is the last release X.Org plans to make of libdmx.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libdmx


<!-- ./extensions/xi -->

## Xi - library for the X Input Extension

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXi


<!-- ./extensions/xext -->

## Xext - library for common extensions to the X11 protocol

libXext is the historical libX11-based catchall library for the X11
extensions without their own libraries.

No new extensions should be added to this library - it is now instead
preferred to make per-extension libraries that can be evolved as needed
without breaking compatibility of this core library.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXext


<!-- ./extensions/xrandr -->

## Xrandr - X Resize, Rotate and Reflection extension library

libXrandr is the libX11-based library for the X Resize, Rotate and
Reflection (RandR) extension.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXrandr


<!-- ./extensions/xtst -->

## Xtst - library for XTEST & RECORD extensions

libXtst provides the Xlib-based client API for the XTEST & RECORD extensions.

The XTEST extension is a minimal set of client and server extensions
required to completely test the X11 server with no user intervention.
This extension is not intended to support general journaling and
playback of user actions.

The RECORD extension supports the recording and reporting of all
core X protocol and arbitrary X extension protocol.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXtst


<!-- ./extensions/xkbfile -->

## xkbfile - XKB file handling routines

libxkbfile is used by the X servers and utilities to parse the XKB
configuration data files.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libxkbfile


<!-- ./extensions/xss -->

## Xss - X11 Screen Saver extension client library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXScrnSaver


<!-- ./extensions/xfixes -->

## Xfixes - XFIXES Extension library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXfixes


<!-- ./extensions/xf86dga -->

## Xxf86dga - Client library for the XFree86-DGA extension.

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXxf86dga


<!-- ./extensions/xv -->

## Xv - library for the X Video (Xv) extension to the X Window System

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXv


<!-- ./extensions/xcomposite -->

## Xcomposite - client library for the Composite extension to the X11 protocol

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXcomposite


<!-- ./extensions/xres -->

## XRes - X-Resource extension client library

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXRes

## P.S.

All questions regarding this software should be directed at the
Xorg mailing list: https://lists.x.org/mailman/listinfo/xorg

Please submit bug reports and requests to merge patches there.

For patch submission instructions, see: 
https://www.x.org/wiki/Development/Documentation/SubmittingPatches