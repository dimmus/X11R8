shared_module('exa',
    'examodule.c',
    include_directories: inc_server,
    dependencies: dep_common,
    link_with: [libxserver_exa, exe_xorg],
    c_args: xorg_c_args,
    install: true,
    install_dir: module_dir,
)
