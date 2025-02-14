inc_server += include_directories('.')

mod = shared_module('vgahw',
    [ 'vgaHW.c', 'vgaHWmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_xorg_module,
)

mod_vgahw = declare_dependency(
    link_with: mod,
    include_directories: inc_server,
)

install_data('vgaHW.h', install_dir: dir_xorg)
