inc_server += include_directories('.')

mod = shared_module('shadowfb',
    [ 'shadowfb.c', 'sfbmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_xorg_module,
    link_with: exe_xorg,
)

mod_shadowfb = declare_dependency(
    link_with: mod,
    include_directories: inc_server,
)

install_data('shadowfb.h', install_dir: dir_xorg)
