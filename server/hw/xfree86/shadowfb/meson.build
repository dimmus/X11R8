inc_server += include_directories('.')

shared_module('shadowfb',
    [ 'shadowfb.c', 'sfbmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XFREE86_CFLAGS,
    install: true,
    install_dir: dir_xorg_module,
    link_with: exe_xorg,
)

install_data('shadowfb.h', install_dir: dir_xorg)
