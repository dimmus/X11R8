srcs_xorg_ddc = [
    'ddc.c',
    'interpret_edid.c',
    'print_edid.c',
    'ddcProperty.c',
]

xorg_ddc = static_library('xorg_ddc',
    srcs_xorg_ddc,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XFREE86_CFLAGS,
)

install_data(['edid.h', 'xf86DDC.h'], install_dir: dir_xorg)
