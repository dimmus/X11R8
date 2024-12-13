---
title: X Window System Libraries
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

# X Window System Libraries

<!-- 
libdmx          X11 Distributed Multihead extension library
libfontenc      X11 font encoding library
libfs           X11 Font Services library
libice          X11 Inter-Client Exchange library
libsm           X11 Session Management library
libx11          X11 client-side library
libxau          X11 authorisation library
libxaw          X11 Athena Widget library
libxcomposite   X11 Composite extension library
libxcursor      X cursor management library
libxdamage      X11 damaged region extension library
libxcvt         X standalone version of VESA CVT standard timing modelines generator
libxdmcp        X11 authorisation library
libxext         X11 miscellaneous extensions library
libxfixes       X11 miscellaneous 'fixes' extension library
libxfont        X11 font rasterisation library
libxft          FreeType-based font drawing library for X
libxi           X11 Input extension library
libxinerama     X11 Xinerama extension library
libxkbfile      X11 keyboard file manipulation library
libxmu          X11 miscellaneous utility library
libxmuu         X11 miscellaneous micro-utility library
libxpm          X11 pixmap library
libxrandr       X11 RandR extension library
libxrender      X Rendering Extension client library
libxres         X11 Resource extension library
libxss          X11 Screen Saver extension library
libxt           X11 toolkit intrinsics library
libxtst         X11 XTEST & RECORD extensions library
libxv           X11 Video extension library
libxvmc         X11 Video extension library
libxxf86dga     X11 Direct Graphics Access extension library
libxxf86vm      X11 XFree86 video mode extension library
x11proto        X11 extension protocols and auxiliary headers
xtrans          X transport library
xserver         Xorg X server
 -->

## ICE - Inter-Client Exchange Library

Documentation for this API can be found in the doc directory of the source
code, or online at: https://www.x.org/releases/current/doc/libICE/

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libICE


## Xtrans - X Network Transport layer shared code

xtrans is a library of code that is shared among various X packages to
handle network protocol transport in a modular fashion, allowing a
single place to add new transport types.  It is used by the X server,
libX11, libICE, the X font server, and related components.

It is however, *NOT* a shared library, but code which each consumer
includes and builds it's own copy of with various #ifdef flags to make
each copy slightly different.  To support this in the modular build
system, this package simply installs the C source files into
`$(prefix)/include/X11/Xtrans` and installs a pkg-config file and an
autoconf m4 macro file with the flags needed to use it.

Documentation of the xtrans API can be found in the included xtrans.xml
file in DocBook XML format. If 'xmlto' is installed, you can generate text,
html, postscript or pdf versions of the documentation by configuring
the build with --enable-docs, which is the default.

The primary development code repository can be found at:
https://gitlab.freedesktop.org/xorg/lib/libxtrans

## Xaw - X Athena Widget Set

Xaw is a widget set based on the X Toolkit Intrinsics (Xt) Library.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXaw

### Examples

The examples are intended to test the different Xaw widgets.  Every program
should provide an example for one widget and if possible also support
functions.  Everyone is invited to add more.  Because the programs make use of
label and/or command widget, there is no separate program to show its use. 
All of the programs support the standard libXt command line options.

*list*  
	select one or none from the list

*menu*  
	press the menubutton and see the menu

*pane*  
	see the use of a pane widget

*repeater*  
	the repeater widget, press the button and keep it pressed

*scrollbar*  
	see the scrollbar moving relative and absolute

*strip*  
	a dynamic widget showing a simple graphic

*toggle*  
	select, unselect one of many buttons

*viewport*  
	shrink the window, select any of the buttons

*xawhisto*  
	use the scollbar to show a value

*simple*  
	use the simple widget to show the X logo, needs libXmu


## Xdmcp - X Display Manager Control Protocol library

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXdmcp

## Xcursor - X Window System Cursor management library

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXcursor

## Xpm - X Pixmap (XPM) image file format library

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXpm

libXpm supports two optional features to handle compressed pixmap files.

--enable-open-zfile makes libXpm recognize file names ending in .Z and .gz
and open a pipe to the appropriate command to compress the file when writing
and uncompress the file when reading. This is enabled by default on platforms
other than MinGW and can be disabled by passing the --disable-open-zfile flag
to the configure script.

--enable-stat-zfile make libXpm search for a file name with .Z or .gz added
if it can't find the file it was asked to open.  It relies on the
--enable-open-zfile feature to open the file, and is enabled by default
when --enable-open-zfile is enabled, and can be disabled by passing the
--disable-stat-zfile flag to the configure script.

All of these commands will be executed with whatever userid & privileges the
function is called with, relying on the caller to ensure the correct euid,
egid, etc. are set before calling.

To reduce risk, the paths to these commands are now set at configure time to
the first version found in the PATH used to run configure, and do not depend
on the PATH environment variable set at runtime.

To specify paths to be used for these commands instead of searching $PATH, pass
the XPM_PATH_COMPRESS, XPM_PATH_UNCOMPRESS, and XPM_PATH_GZIP
variables to the configure command.


### Tests

The pixmaps under this directory are used as test cases for several tests.
The tests iterate over all files in each directory, so new test cases can be
added by just adding a file there, adding it to the `EXTRA_DIST` list in
`test/Makefile`, and adding a note here to help us remember what each test case
covers.  Please make sure all pixmaps are appropriately licensed.

For details on the different format types, see xpmDataTypes in `src/data.c`,
<https://en.wikipedia.org/wiki/X_PixMap>, and
<http://fileformats.archiveteam.org/wiki/XPM>.

#### good

Those under the `good` subdirectory are expected to work and
return `XpmSuccess` when parsed.

A subset of these are specifically chosen/designed to test various things:

- `plaid-v3.xpm` - copy of the sample XPM file from pg. 10 of `doc/xpm.PS.gz`,
  in XPM version 3 format

- `plaid-v1.xpm` - alternate version of plaid.xpm in XPM version 1 format

- `plaid-v2.xpm` - alternate version of plaid.xpm in XPM version 2 "natural" format

- `plaid-lisp.xpm` - alternate version of plaid.xpm in XPM Version 2 Lisp format

- `jigglymap.xpm` - transparent background

Other pixmaps in this directory are a selection of real world XPM files
with a variety of sizes & numbers of colors.

#### invalid

Those under the `invalid` subdirectory are expected to fail and
return XpmFileInvalid when parsed.

- `doom.xpm` - This file is originally from
  <http://scary.beasts.org/misc/doom.xpm>.
  It is a test case for the stack-based overflow in xpmParseColors in
  CVE-2004-0687 as described in
  <https://security.appspot.com/security/CESA-2004-003.txt>.

- `doom2.xpm` - This file is originally from
  <http://scary.beasts.org/misc/doom2.xpm>.
  It is a test case for the stack-based overflow in ParseAndPutPixels
  and ParsePixels in CVE-2004-0687 as described in
  <https://security.appspot.com/security/CESA-2004-003.txt>.

- `invalid-type.xpm` - This file has an invalid XPM version 2 type header

- `no-contents.xpm` - This file has a valid header but no contents

- `unending-comment-c.xpm` - This file has a C comment block without the
  closing "*/" to test for CVE-2022-46285

- `zero-width.xpm` & `zero-width-v1.xpm` - These files declare a width of 0
  and a height of nearly UINT_MAX, to test for CVE-2022-44617

- `corrupt-colormap.xpm` - This file was generated by the clang libfuzzer,
  and serves as a test for CVE-2023-43789

- `width-overflow.xpm` - This file was provided by Yair Mizrahi of
  the JFrog Vulnerability Research team as a test for CVE-2023-43787.
  Its width causes an integer overflow when multiplied by a depth of 4 bytes
  (32-bits) when using 32-bit ints.

#### no-mem

Those under the `invalid` subdirectory are expected to fail and
return `XpmNoMemory` when parsed.

- `oversize.xpm` - This file specifies more pixels than can be mapped in
  a 64-bit address space that already has programs & libraries mapped in.

#### other

Those under the `other` subdirectory don't fit cleanly in any of the above
categories, and may be valid for some uses but not others, and thus can't be
easily used in the current test framework, but are still interesting cases.

- `overflow-stackexhaustion.xpm` - This file was provided by Yair Mizrahi of
  the JFrog Vulnerability Research team as a test for CVE-2023-43786.
  It is a valid XPM file, but is larger than fits into an X Pixmap, so
  should pass with many functions, but fail when used with sxpm or
  anything that calls through to `xpmCreatePixmapFromImage()`.

## SM - X Session Management Library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libSM

## Xmu - X miscellaneous utility routines library

This library contains miscellaneous utilities and is not part of the Xlib
standard.  It contains routines which only use public interfaces so that it
may be layered on top of any proprietary implementation of Xlib or Xt.

It is intended to support clients in the X.Org distribution; vendors
may choose not to distribute this library if they wish.  Therefore,
applications developers who depend on this library should be prepared to
treat it as part of their software base when porting.

API documentation for this library is provided in the docs directory in
DocBook format.  If xmlto is installed, it will be converted to supported
formats and installed in $(docdir) unless --disable-docs is passed to
configure.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXmu

## Xcvt

`libxcvt` is a library providing a standalone version of the X server
implementation of the VESA CVT standard timing modelines generator.

`libxcvt` also provides a standalone version of the command line tool
`cvt` copied from the Xorg implementation and is meant to be a direct
replacement to the version provided by the `Xorg` server.

An example output is:

```
$ cvt --verbose 1920 1200 75
# 1920x1200 74.93 Hz (CVT 2.30MA) hsync: 94.04 kHz; pclk: 245.25 MHz
Modeline "1920x1200_75.00"  245.25  1920 2064 2264 2608  1200 1203 1209 1255 -hsync +vsync
```
The code base of `libxcvt` is identical to `xf86CVTMode()` therefore
all credits for `libxcvt` go to the author (Luc Verhaegen) and
contributors of `xf86CVTMode()` and the `cvt` utility as found in the
[xserver](https://gitlab.freedesktop.org/xorg/xserver/) repository.

## Xaw3d - X 3D Athena Widget Set.

Xaw3d is a widget set based on the X Toolkit Intrinsics (Xt) Library.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXaw3d

## Xft - X FreeType library

libXft is the client side font rendering library, using libfreetype,
libX11, and the X Render extension to display anti-aliased text.

Xft version 2.1 was the first stand alone release of Xft, a library that
connects X applications with the FreeType font rasterization library. Xft
uses fontconfig to locate fonts so it has no configuration files.

Before building Xft you will need to have installed:
 - [FreeType](https://freetype.org/)
 - [Fontconfig](https://fontconfig.org/)
 - libX11, libXext, & libXrender (https://www.x.org/)

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/lib/libXft

To release a version of this library follow the steps listed in 
https://www.x.org/wiki/Development/Documentation/ReleaseHOWTO/

## Xt - X Toolkit Intrinsics library

Documentation for this library can be found in the included man pages; and
the libXt spec from the specs directory of the source, also available at:

 - https://www.x.org/releases/current/doc/libXt/intrinsics.html
 - https://www.x.org/releases/current/doc/libXt/intrinsics.pdf

and the O'Reilly X Toolkit books, which they have made freely available online:

 - X Series Volume 4: X Toolkit Intrinsics Programming Manual,
   1st Edition (1990, covers X11R3)

   https://archive.org/details/xtoolkitintrsin20400nyemiss

 - X Series Volume 4: X Toolkit Intrinsics Programming Manual,
   2nd Edition (1990, covers X11R4)

   https://archive.org/details/xtoolkitintrinsi04nyemiss

 - X Series Volume 4: X Toolkit Intrinsics Programming Manual,
   Motif Edition (1990, covers X11R4/Motif 1.1)

   https://archive.org/details/xtoolktintrmotif04nyemiss

 - X Series Volume 4: X Toolkit Intrinsics Programming Manual,
   3rd Edition (1993, covers X11R5/Motif 1.2)

   https://archive.org/details/xtoolkitintrinsi0000nyea

 - X Series Volume 5: X Toolkit Intrinsics Reference Manual
   (1990, covers X11R4)

   https://archive.org/details/xtoolkitintrirefman05oreimiss

 - X Series Volume 5: X Toolkit Intrinsics Reference Manual
   (1994, covers X11R4 and X11R5)

   https://archive.org/details/xtoolkitintrinsi05flan

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXt

## X11 - Core X11 protocol client library

Documentation for this library can be found in the included man pages,
and in the Xlib spec from the specs subdirectory, also available at:

 - https://www.x.org/releases/current/doc/libX11/libX11/libX11.html

 - https://www.x.org/releases/current/doc/libX11/libX11/libX11.pdf

and the O'Reilly Xlib books, which they have made freely available online,
though only for older versions of X11:

 - X Series Volume 2: Xlib Reference Manual (1989, covers X11R3)
   https://www.archive.org/details/xlibretmanver1102nyemiss

 - X Series Volume 2: Xlib Reference Manual, 2nd Edition (1990, covers X11R4)
   https://www.archive.org/details/xlibrefmanv115ed02nyemiss

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libX11

## P.S.

All questions regarding this software should be directed at the
Xorg mailing list: https://lists.x.org/mailman/listinfo/xorg

Please submit bug reports and requests to merge patches there.

For patch submission instructions, see: https://www.x.org/wiki/Development/Documentation/SubmittingPatches
