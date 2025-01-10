shared_module('shadowfb',
    [ 'shadowfb.c', 'sfbmodule.c'],
    include_directories: [ inc_server, inc_server ],
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: module_dir,
    link_with: e,
)

install_data('shadowfb.h', install_dir: xorgsdkdir)
