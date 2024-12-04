<!-- ./lib/ice -->

## ICE - Inter-Client Exchange Library

Documentation for this API can be found in the doc directory of the source
code, or online at: https://www.x.org/releases/current/doc/libICE/

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libICE


<!-- ./lib/xtrans -->

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


<!--  ./lib/xaw -->

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


<!-- ./lib/xdmcp -->

## Xdmcp - X Display Manager Control Protocol library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXdmcp


<!-- ./lib/xcursor -->

## Xcursor - X Window System Cursor management library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXcursor


<!-- ./lib/xpm -->

## Xpm - X Pixmap (XPM) image file format library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXpm


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


<!-- ./lib/sm -->

## SM - X Session Management Library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libSM


<!-- ./lib/xmu -->

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


<!-- ./lib/xcvt -->

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


<!-- ./lib/xaw3d -->

## Xaw3d - X 3D Athena Widget Set.

Xaw3d is a widget set based on the X Toolkit Intrinsics (Xt) Library.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXaw3d


<!-- ./lib/xft -->

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

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXft


To release a version of this library follow the steps listed in https://www.x.org/wiki/Development/Documentation/ReleaseHOWTO/


<!-- ./lib/xt -->

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


<!-- ./lib/x11 -->

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

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXxf86dga


<!-- ./extensions/xv -->

## Xv - library for the X Video (Xv) extension to the X Window System

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXv


<!-- ./extensions/xcomposite -->

## Xcomposite - client library for the Composite extension to the X11 protocol

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXcomposite


<!-- ./extensions/xres -->

## XRes - X-Resource extension client library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXRes


<!-- ./fonts/lib/fontenc -->

## libfontenc - font encoding library

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libfontenc


<!-- ./fonts/lib/xfont -->

## Xfont - X font handling library for server & utilities

libXfont provides the core of the legacy X11 font system, handling the index
files (fonts.dir, fonts.alias, fonts.scale), the various font file formats,
and rasterizing them.  It is used by the X display servers (Xorg, Xvfb, etc.)
and the X Font Server (xfs), but should not be used by normal X11 clients.  X11
clients access fonts via either the new APIs in libXft, or the legacy APIs in
libX11.

libXfont supports a number of compression and font formats, and the
configure script takes various options to enable or disable them:

- Compression types:

  * gzip - always enabled, no option to disable, requires libz

  * bzip2 - disabled by default, enable via --with-bzip2, requires libbz2

- Font formats:

  * builtins - copies of the "fixed" & "cursor" fonts required by the
    X protocol are built into the library so the X server always
    has the fonts it requires to start up.   Accessed via the
    special 'built-ins' entry in the X server font path.  
    Enabled by default, disable via --disable-builtins.

  * freetype - handles scalable font formats including OpenType, FreeType,
    and PostScript formats.  Requires FreeType2 library.
    Can also be used to handle bdf & bitmap pcf font formats.  
    Enabled by default, disable via --disable-freetype.

  * bdf bitmap fonts - text file format for distributing fonts, described
    in https://www.x.org/docs/BDF/bdf.pdf specification.  Normally
    not used by the X server at runtime, as the fonts distributed
    by X.Org in bdf format are compiled with bdftopcf when
    installing/packaging them.  
    Enabled by default, disable via --disable-bdfformat.

  * pcf bitmap fonts - standard bitmap font format since X11R5 in 1991,
    used for all bitmap fonts installed from X.Org packages.
    Compiled format is architecture independent.
    As noted above, usually produced by bdftopcf.  
    Enabled by default, disable via --disable-pcfformat.

  * snf bitmap fonts - standard bitmap font format prior to X11R5 in 1991,
    remains only for backwards compatibility.  Unlike pcf, snf files
    are architecture specific, and contain less font information
    than pcf files.  snf fonts are deprecated and support for them
    may be removed in future libXfont releases.  
    Disabled by default, enable via --disable-snfformat.

- Font services:

  * xfs font servers - allows retrieving fonts as a client of an xfs server.
    Enabled by default, disable via --disable-fc (font client).

    If enabled, you can also use the standard libxtrans flags to
    configure which transports can be used to connect to xfs:
    
        --enable-unix-transport  Enable UNIX domain socket transport
        --enable-tcp-transport   Enable TCP socket transport (IPv4)
        --enable-ipv6            Enable IPv6 support for tcp-transport
        --enable-local-transport Enable os-specific local transport

    (Change `--enable` to `--disable` to force disabling support).
    The default setting is to enable all of the transports the
    configure script can find OS support for.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libXfont


<!-- ./fonts/lib/fs -->

## libFS - X Font Service client library

This library is used by clients of X Font Servers (xfs), such as
xfsinfo, fslsfonts, and the X servers themselves.

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/lib/libFS


<!-- ./proto -->

## Xproto - X Window System Unified Protocol

This package provides the headers and specification documents defining
the core protocol and (many) extensions for the X Window System. The
extensions are those common among servers descended from X11R7. It
also includes a number of headers that aren't purely protocol related,
but are depended upon by many other X Window System packages to provide
common definitions and porting layer.

Though the protocol specifications herein are authoritative, the
content of the headers is bound by compatibility constraints with older
versions of the X11 suite. If you are looking for a machine-readable
protocol description suitable for code generation or use in new
projects, please refer to the XCB project:

  https://xcb.freedesktop.org/
  https://gitlab.freedesktop.org/xorg/proto/xcbproto

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/proto/xorgproto


### Updating for new Linux kernel releases

The XF86keysym.h header file needs updating whenever the Linux kernel
adds a new keycode to linux/input-event-codes.h. See the comment in
include/X11/XF86keysym.h for details on the format.

The steps to update the file are:

- if the kernel release did not add new `KEY_FOO` defines, no work is
  required
- ensure that libevdev has been updated to the new kernel headers. This may
  require installing libevdev from git.
- run `scripts/keysym-generator.py` to add new keysyms. See the `--help`
  output for the correct invocation.
- verify that the format for any keys added by this script is correct and
  that the keys need to be mapped. Where a key code should not get a new
  define or is already defined otherwise, comment the line.
- file a merge request with the new changes
- notify the xkeyboard-config maintainers that updates are needed

Note that any #define added immediately becomes API. Due diligence is
recommended.


<!-- ./server -->

## X Server

The X server accepts requests from client applications to create windows,
which are (normally rectangular) "virtual screens" that the client program
can draw into.

Windows are then composed on the actual screen by the X server
(or by a separate composite manager) as directed by the window manager,
which usually communicates with the user via graphical controls such as buttons
and draggable titlebars and borders.

For a comprehensive overview of X Server and X Window System, consult the
following article: https://en.wikipedia.org/wiki/X_server

All questions regarding this software should be directed at the
Xorg mailing list: https://lists.freedesktop.org/mailman/listinfo/xorg

The primary development code repository can be found at: https://gitlab.freedesktop.org/xorg/xserver

For patch submission instructions, see: https://www.x.org/wiki/Development/Documentation/SubmittingPatches

As with other projects hosted on freedesktop.org, X.Org follows its
Code of Conduct, based on the Contributor Covenant. Please conduct
yourself in a respectful and civilized manner when using the above
mailing lists, bug trackers, etc: https://www.freedesktop.org/wiki/CodeOfConduct


## P.S.

All questions regarding this software should be directed at the
Xorg mailing list: https://lists.x.org/mailman/listinfo/xorg

Please submit bug reports and requests to merge patches there.

For patch submission instructions, see: https://www.x.org/wiki/Development/Documentation/SubmittingPatches