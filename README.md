<h1 align="center">X Window System<br/>
<span style="font-size:0.5em;">Version 11, Release 8</span>
</h1>

<img src="doc/X11.png" width=100 align="right"/>

This document describes how to build, install, and get started with Release 8 of the X Window System and gives a brief overview of the contents of the release.

## For the Impatient Explorer

For those of you who will try to build the distribution without reading the entire release notes first, here is a quick summary of what to do.

```sh
meson setup . build
meson compile -C build
meson install -C build
```

## Changes from X11R7
- **Monolithic X package (again).**
It's quite annoying to gather a tenth of separate packages to get Xserver running. Moreover, all changes to separate libraries and extensions *should be* tested for regression for the *whole* X package.
- **Complete picture of X Window System.** Especially for newcomers, it is very difficult to observe the whole system and their internal and external dependencies. The earlier decision to divide packages to force their individual progress failed in general.
- **Common standards for all subpackages.** Let's apply equal development environments and build conditions to all system parts.

## N.B.
**Warning:** If you get a fatal error, `StringDefs.h: No such file or directory`, no problem; simply **continue** the compilation. When you build on very fast PCs with ccache, Meson cannot find the compile-time-generated "StringDefs.h" file so quickly. Still search for the way to avoid this problem.

