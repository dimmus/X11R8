srcs_xext = files(
    'bigreq.c',
    'geext.c',
    'shape.c',
    'sleepuntil.c',
    'sync.c',
    'xcmisc.c',
    'xtest.c',
)

hdrs_xext = files(
    'geext.h',
    'geint.h',
    'syncsdk.h',
)

if build_dpms
    srcs_xext += 'dpms.c'
endif

if build_mitshm
    srcs_xext += 'shm.c'
    hdrs_xext += 'shmint.h'
endif

if build_hashtable
    srcs_xext += 'hashtable.c'
endif

if build_res
    srcs_xext += 'xres.c'
endif

if build_screensaver
    srcs_xext += 'saver.c'
endif

if build_xace
    srcs_xext += 'xace.c'
endif

if build_xsecurity
    srcs_xext += 'security.c'
endif

if build_xselinux
    srcs_xext += ['xselinux_ext.c', 'xselinux_hooks.c', 'xselinux_label.c']
endif

if build_xf86bigfont
    srcs_xext += 'xf86bigfont.c'
endif

if build_xinerama
    srcs_xext += files('panoramiX.c', 'panoramiXprocs.c', 'panoramiXSwap.c')
    hdrs_xext += files('panoramiX.h', 'panoramiXsrv.h')
endif

if build_xv
    srcs_xext += files('xvmain.c', 'xvdisp.c', 'xvmc.c')
    hdrs_xext += files('xvdix.h', 'xvmcext.h')
endif

libxserver_xext = static_library('libxserver_xext',
    srcs_xext,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

libxserver_xext_vidmode = static_library('libxserver_xext_vidmode',
    'vidmode.c',
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

install_data(hdrs_xext, install_dir: dir_xorg)