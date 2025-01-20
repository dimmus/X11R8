<h1 align="center">X Window System<br/>
<span style="font-size:0.5em;">Version 11, Release 8</span>
</h1>

<img src="doc/X11.png" width=100 align="right"/>

This document describes how to build, install, and get started with Release 8 of the X Window System and gives a brief overview of the contents of the release.

## Build

```sh
meson setup . build
meson compile -C build
meson install -C build
```

## Changes from mainstream
- Monolithic X Window System package
- Meson build system
- Enabled 3D acceleration by default
- Integrated XCB
- Integrated X drivers
- Integrated X apps like `twm`, `xinit`, `xclock`, `xterm` *
- Revived font server
- No Windows support
- No Wayland support

`*` - work in progress
