inc_server += include_directories('.')

shared_module('shadowfb',
    [ 'shadowfb.c', 'sfbmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: module_dir,
    link_with: exe_xorg,
)

install_data('shadowfb.h', install_dir: dir_xorg)
