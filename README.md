<h1 align="center">X Window System<br/>
<span style="font-size:0.5em;">Version 11, Release 8</span>
</h1>

<img src="doc/X11.svg" width=100 align="right"/>

This document describes how to build and install Release 8 of the X Window System and gives a brief overview of the contents of the release.

## Build

Install dependencies by running (no need to edit it)
```sh
./util/install_deps.sh
```
Script supports and autodefines Ubuntu, Archlinux and Alpine.

Then
```sh
meson setup . build
meson compile -C build
meson install -C build
```

## Changes from mainstream
- Monolithic X Window System package
- Minimal and sufficient for general usage
- Oriented to embedded Linux systems
- Meson build system
- Enabled accelerations by default
- Integrated XCB
- Integrated X drivers
- Integrated X apps like `twm`, `xinit`, `xclock`, `xterm`
- Integrated `libepoxy`, `pixman`
- Revived font server
- Scripted dependencies installation
- No XWin support
- No XWayland support
- No XQuartz support

<!-- `*` - work in progress -->
