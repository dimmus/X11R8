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

### Error with "StringDefs.h"
If you get an error `fatal error: StringDefs.h: No such file or directory`, no problem, simply **continue** the compilation. When you build on very fast PCs with ccache, Meson cannot find compile-time generated "StringDefs.h" file so quickly. Still search the way to avoid this problem.