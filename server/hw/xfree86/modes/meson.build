srcs_xorg_modes = [
    'xf86Crtc.c',
    'xf86Cursors.c',
    'xf86gtf.c',
    'xf86EdidModes.c',
    'xf86Modes.c',
    'xf86RandR12.c',
    'xf86Rotate.c',
]

if build_dga
    srcs_xorg_modes += 'xf86DiDGA.c'
endif

xorg_modes = static_library('xorg_modes',
    srcs_xorg_modes,
    include_directories: inc_server,
    dependencies: [ dep_common, libxcvt ],
    c_args: XFREE86_CFLAGS,
)

install_data(
    'xf86Crtc.h',
    'xf86Modes.h',
    'xf86RandR12.h',
    install_dir: dir_xorg,
)
