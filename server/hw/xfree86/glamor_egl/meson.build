glamoregl_src = [
    '../../../glamor/glamor_egl.c',
    '../../../glamor/glamor_eglmodule.c',
    'glamor_xf86_xv.c',
]

shared_module(
    'glamoregl',
    glamoregl_src,

    include_directories: inc_server,
    c_args: xorg_c_args,
    dependencies: [
        dep_common,
        dep_drm,
        dep_gbm,
    ],
    link_with: [glamor, libxserver_glx],

    install: true,
    install_dir: dir_xorg_module,
)
