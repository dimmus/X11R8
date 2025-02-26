srcs_xorg_ramdac = [
    'xf86CursorRD.c',
    'xf86HWCurs.c',
]

xorg_ramdac = static_library('xorg_ramdac',
    srcs_xorg_ramdac,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XFREE86_CFLAGS,
)

install_data('xf86Cursor.h', install_dir: dir_xorg)
