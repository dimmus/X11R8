inc_server += include_directories('.')

shared_module('vgahw',
    [ 'vgaHW.c', 'vgaHWmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XFREE86_CFLAGS,
    install: true,
    install_dir: dir_xorg_module,
)

install_data('vgaHW.h', install_dir: dir_xorg)
