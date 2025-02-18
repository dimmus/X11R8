srcs_xorg_dri = [
    'dri.c',
    'xf86dri.c',
]

xorg_dri = static_library('xorg_dri',
    srcs_xorg_dri,
    include_directories: inc_server,
    dependencies: [dep_common, dep_drm],
    c_args: xorg_c_args,
)

install_data(
    'dri.h',
    'sarea.h',
    'dristruct.h',
    install_dir: dir_xorg,
)
