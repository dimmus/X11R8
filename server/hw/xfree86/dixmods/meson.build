shared_module('wfb',
    'fbmodule.c',
    include_directories: inc_server,
    c_args: XFREE86_CFLAGS,
    dependencies: dep_common,
    link_whole: libxserver_wfb,
    link_with: exe_xorg,
    install: true,
    install_dir: dir_xorg_module,
)

shared_module('shadow',
    'shmodule.c',
    include_directories: inc_server,
    c_args: XFREE86_CFLAGS,
    dependencies: dep_common,
    link_whole: libxserver_miext_shadow,
    link_with: exe_xorg,
    install: true,
    install_dir: dir_xorg_module,
)

if build_glx
shared_module('glx',
    [ 'glxmodule.c', srcs_glxdri2 ],
    include_directories: [ inc_server, inc_server_glx ],
    c_args: [ XFREE86_CFLAGS, glx_align64 ],
    dependencies: [ dep_common, dep_dl, dep_dri ],
    link_whole: libxserver_glx,
    link_with: exe_xorg,
    install: true,
    install_dir: dir_xorg_module / 'extensions'
)
endif
