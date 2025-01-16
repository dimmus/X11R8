shared_module('wfb',
    'fbmodule.c',
    include_directories: inc_server,
    c_args: [ xorg_c_args, wfb_args ],
    dependencies: dep_common,
    link_whole: libxserver_wfb,
    link_with: e,
    install: true,
    install_dir: module_dir,
)

shared_module('shadow',
    'shmodule.c',
    include_directories: inc_server,
    c_args: xorg_c_args,
    dependencies: dep_common,
    link_whole: libxserver_miext_shadow,
    link_with: e,
    install: true,
    install_dir: module_dir,
)

if build_glx
shared_module('glx',
    [ 'glxmodule.c', srcs_glxdri2 ],
    include_directories: [ inc_server, glx_inc ],
    c_args: [ xorg_c_args, glx_align64 ],
    dependencies: [ dep_common, dep_dl, dep_dri ],
    link_whole: libxserver_glx,
    link_with: e,
    install: true,
    install_dir: module_dir / 'extensions'
)
endif
