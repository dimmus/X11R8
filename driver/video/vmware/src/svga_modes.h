/* **********************************************************
 * Copyright (C) 2007 VMware, Inc. All Rights Reserved
 * **********************************************************/

#ifndef _SVGA_MODES_H_
#define _SVGA_MODES_H_

#define INCLUDE_ALLOW_USERLEVEL
#include "includeCheck.h"

#define SVGA_DEFAULT_MODES        \
   /* 4:3 modes */               \
    SVGA_DEFAULT_MODE(320, 240)   \
    SVGA_DEFAULT_MODE(400, 300)   \
    SVGA_DEFAULT_MODE(512, 384)   \
    SVGA_DEFAULT_MODE(640, 480)   \
    SVGA_DEFAULT_MODE(800, 600)   \
    SVGA_DEFAULT_MODE(1024, 768)  \
    SVGA_DEFAULT_MODE(1152, 864)  \
    SVGA_DEFAULT_MODE(1280, 960)  \
    SVGA_DEFAULT_MODE(1400, 1050) \
    SVGA_DEFAULT_MODE(1600, 1200) \
    SVGA_DEFAULT_MODE(1920, 1440) \
    SVGA_DEFAULT_MODE(2048, 1536) \
    SVGA_DEFAULT_MODE(2560, 1920) \
   /* 16:9 modes */              \
    SVGA_DEFAULT_MODE(854, 480)   \
    SVGA_DEFAULT_MODE(1280, 720)  \
    SVGA_DEFAULT_MODE(1366, 768)  \
    SVGA_DEFAULT_MODE(1920, 1080) \
    SVGA_DEFAULT_MODE(2560, 1440) \
   /* 16:10 modes */             \
    SVGA_DEFAULT_MODE(1280, 800)  \
    SVGA_DEFAULT_MODE(1440, 900)  \
    SVGA_DEFAULT_MODE(1680, 1050) \
    SVGA_DEFAULT_MODE(1920, 1200) \
    SVGA_DEFAULT_MODE(2560, 1600) \
   /* DVD modes */               \
    SVGA_DEFAULT_MODE(720, 480)   \
    SVGA_DEFAULT_MODE(720, 576)   \
   /* Odd modes */               \
    SVGA_DEFAULT_MODE(320, 200)   \
    SVGA_DEFAULT_MODE(640, 400)   \
    SVGA_DEFAULT_MODE(800, 480)   \
    SVGA_DEFAULT_MODE(1280, 768)  \
    SVGA_DEFAULT_MODE(1280, 1024)

#endif /* _SVGA_MODES_H_ */
