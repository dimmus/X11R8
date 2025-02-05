---
title: X Window System Applications (Clients)
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

# X Window System Clients

## Xrdb

X server resource database utility

## XModmap

The xmodmap program is used to edit and display the keyboard modifier
map and keymap table that are used by client applications to convert
event keycodes into keysyms.  It is usually run from the user's
session startup script to configure the keyboard according to personal
tastes.

https://gitlab.freedesktop.org/xorg/app/xmodmap


## Xinit

The xinit program is used to start the X Window System server and a first
client program on systems that are not using a display manager such as xdm.

The xinit is not intended for naive users.  Instead, site administrators should
design user-friendly scripts that present the desired interface when starting
up X.  The startx script is one such example.

https://gitlab.freedesktop.org/xorg/app/xinit

## XFontSel
xfontsel application provides a simple way to display the X11 core
protocol fonts known to your X server, examine samples of each, and
retrieve the X Logical Font Description ("XLFD") full name for a font.

https://gitlab.freedesktop.org/xorg/app/xfontsel

## XlsFonts
xlsfonts lists fonts available from an X server via the X11 core protocol.

https://gitlab.freedesktop.org/xorg/app/xlsfonts

## mkfontscale
mkfontscale creates the fonts.scale and fonts.dir index files used by the legacy X11 font system.  It now includes the mkfontdir script previously distributed separately for compatibility with older X11 versions.

https://gitlab.freedesktop.org/xorg/app/mkfontscale

## fslsfonts
fslsfonts produces a list of fonts served by an X font server.

https://gitlab.freedesktop.org/xorg/app/fslsfonts

## P.S.

All questions regarding this software should be directed at the
Xorg mailing list:

  https://lists.x.org/mailman/listinfo/xorg

Please submit bug reports and requests to merge patches there.

For patch submission instructions, see:

  https://www.x.org/wiki/Development/Documentation/SubmittingPatches
