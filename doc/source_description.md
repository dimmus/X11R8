# Structure of the X Sources

Sources  are  organized into the following subdirectories:

clients
```
This directory contains most of the sample applications. See the program man pages for details.
```

config
```
This directory contains configuration files and the imake program used to build the release. Details are covered in other sections below.
```

demos
```
This directory contains a small collection of graphics demonstration programs, a few utility/test programs, and some performance demonstration programs. These are by no means the "best" demo programs around, they just happen to be ones we try to maintain.

doc
```
This directory contains troff sources to X  Consortium  standards, server internals documentation, documentation for various utility libraries, some useful tutorial material.
```

extensions
```
This directory contains implementations of X server extensions, both the server internals and the application programming libraries, and some test programs. Of particular note here, new in Release 5, is PEX, the PHIGS Extension to X used for 3D graphics, and the PHIGS programming library which interfaces to the PEX protocol.

fonts
```
This directory contains bitmap fonts in source form, some outline fonts, a sample font server, a utility font library used by the X server and font server, a client font library for interacting with the font server, and programs for building fonts and querying the font server.
```

hardcopy
```
This directory contains pre-generated PostScript files for the client man pages and for most of the documentation found in the doc directory. The files are compressed with compress to save disk space. If you do not have compress on your system, you will find a version in the mit/util/compress directory.
```

include
```
This directory contains various library-independent C header files and a collection of bitmap files.
```

lib
```
This directory contains programming libraries and support files. Of note are Xlib (the lowest-level C programming interface to X), Xt (the X Toolkit Intrinsics), Xmu (an eclectic set of utility functions), Xaw (the Athena Widget Set), and CLX (a Common Lisp interface to X).
```

man
```
This directory contains a few top-level man pages about the release (general information, server access control mechanisms, the X Consortium, and X Consortium standards), and man pages for some of the programming libraries.
```

rgb
```
This directory contains a program to generate the color database used by the X server and sample databases.
```

server
```
This directory contains the X server sources, both  device-independent (dix) and device-dependent (ddx). In this release, there is support for building the following servers:

DECstation 2100/3100 monochrome and color displays
DECstation 5000 CX and MX displays
IBM RS/6000 skyway adapter
Apple Macintosh monochrome and color displays
MIPS monochrome and color displays
OMRON LUNA monochrome displays (color displays operate in monochrome)
Tektronix 4319 color display
VAXstation QVSS and QDSS displays
Sun monochrome and 8-bit color displays (with GX support)
Various VGA displays under System V/386

If your favorite hardware is not listed above, please do not blame us at MIT, we ship what Consortium members provide. Only in a few cases do we try to maintain device-specific software for our own development needs.
```

util
```
This directory contains miscellaneous utility programs and shell scripts used to build, maintain, and install the release.
```