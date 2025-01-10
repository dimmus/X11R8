srcs_xorg_i2c = [
    'xf86i2c.c'
]

xorg_i2c = static_library('xorg_i2c',
    srcs_xorg_i2c,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
)

install_data(['xf86i2c.h', 'i2c_def.h'], install_dir: xorgsdkdir)
