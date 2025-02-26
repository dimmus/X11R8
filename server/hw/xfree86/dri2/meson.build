srcs_xorg_dri2 = [
    'dri2.c',
    'dri2ext.c',
]

xorg_dri2 = static_library('xorg_dri2',
    srcs_xorg_dri2,
    include_directories: inc_server,
    dependencies: [dep_common, dep_drm],
    c_args: XFREE86_CFLAGS,
)

install_data('dri2.h', install_dir: dir_xorg)
