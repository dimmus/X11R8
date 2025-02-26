shared_module('exa',
    'examodule.c',
    include_directories: inc_server,
    dependencies: dep_common,
    link_with: [libxserver_exa, exe_xorg],
    c_args: XFREE86_CFLAGS,
    install: true,
    install_dir: dir_xorg_module,
)
