---
title: X Window System Font Libraries
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

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

<!-- font/server -->
## X font Server (xfs)

[The rest of these notes come from the original X11R5 implementation
 in 1991, and have been updated slightly for the xfs 1.1.0 modular release,
 but are otherwise a bit stale.]

Installation instructions for fontserver

1 - If you don't want to use the default config file location,
run configure with the --with-default-config-file=path option to
point to the correct place.

An example config file is in ./config

2 - modify the config file so the 'catalogue'
parameter points to a set of valid font directories.

At this point the test programs should work.  Start the font server
(xfs &) and try some tests.  Most of the clients take
a command line switch of where to find the server, and
FSlib understands the environment variable FONTSERVER.
The format is the same as Xlib, (ie, hostname:server_number).

The doc directory contains various pieces of documentation on the font
server and associated software:

    xfs-design.xml	- DocBook source of fontserver design overview

Tested font formats:

The fontserver has been tested with PCF, Speedo, SNF and BDF formats.

Tested environments:

the fontserver and clients have been built & tested on SPARC running
4.x and a DECstation 3100 running V4.0.  it should work ok on any 32
bit UNIX w/ BSD sockets.

The primary development code repository can be found at: 
https://gitlab.freedesktop.org/xorg/app/xfs
