inc_server += include_directories('.')

shared_module('vgahw',
    [ 'vgaHW.c', 'vgaHWmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: module_dir,
)

install_data('vgaHW.h', install_dir: dir_xorg)
