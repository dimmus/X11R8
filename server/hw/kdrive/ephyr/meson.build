srcs = [
    'ephyr.c',
    'ephyrinit.c',
    'ephyrcursor.c',
    'ephyr_draw.c',
    'hostx.c',
]

dep_xephyr = [
    dep_common,
    libxcb,
    libxcb_renderutil,
    libxcb_image,
    libxcb_iccm,
    libxcb_keysyms,
    libxcb_util,
]

srcs += 'ephyr_glamor.c'
if build_xv
    srcs += 'ephyr_glamor_xv.c'
endif
dep_xephyr += dep_epoxy

if build_xv
    srcs += 'ephyrvideo.c'
endif

xephyr_server = executable('Xephyr',
    srcs,
    include_directories: [
        inc_server,
        include_directories('../src')
    ],
    dependencies: dep_xephyr,
    link_with: [
        libxserver_main,
        libxserver_exa,
        glamor,
        kdrive,
        libxserver_fb,
        libxserver,
        libxserver_config,
        libxserver_xkb_stubs,
        libxserver_xi_stubs,
        libxserver_glx,
        libglxvnd,
    ],
    install: true,
)
