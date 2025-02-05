<h1 align="center">X Window System<br/>
<span style="font-size:0.5em;">Version 11, Release 8</span>
</h1>

<img src="doc/X11.png" width=100 align="right"/>

This document describes how to build and install Release 8 of the X Window System and gives a brief overview of the contents of the release.

## Build

Install dependencies by running
```
./util/install_deps.sh
```
Script supports Ubuntu, Archlinux and Alpine. You have **no need to edit** it.

Then
```sh
meson setup . build
meson compile -C build
meson install -C build
```

## Changes from mainstream
- Monolithic X Window System package
- Meson build system
- Scripted Linux dependencies installation
- Enabled 3D acceleration by default
- Integrated XCB
- Integrated X drivers
- Integrated X apps like `twm`, `xinit`, `xclock`, `xterm`
- Integrated `libepoxy` and `pixman`
- Revived font server
- No XWin support
- No XWayland support
- No XQuarz support
- Oriented to modern Linux systems

<!-- `*` - work in progress -->
