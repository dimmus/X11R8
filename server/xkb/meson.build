srcs_xkb = files(
    'ddxBeep.c',
    'ddxCtrls.c',
    'ddxLEDs.c',
    'ddxLoad.c',
    'maprules.c',
    'xkmread.c',
    'xkbtext.c',
    'xkbfmisc.c',
    'xkbout.c',
    'xkb.c',
    'xkbUtils.c',
    'xkbEvents.c',
    'xkbAccessX.c',
    'xkbSwap.c',
    'xkbLEDs.c',
    'xkbInit.c',
    'xkbActions.c',
    'xkbPrKeyEv.c',
    'XKBMisc.c',
    'XKBAlloc.c',
    'XKBGAlloc.c',
    'XKBMAlloc.c',
)

libxserver_xkb = static_library('libxserver_xkb',
    srcs_xkb,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

srcs_xkb_stubs = files(
    'ddxKillSrv.c',
    'ddxPrivate.c',
    'ddxVT.c',
)

libxserver_xkb_stubs = static_library('libxserver_xkb_stubs',
    srcs_xkb_stubs,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)
