glamoregl_src = [
    '../../../glamor/glamor_egl.c',
    '../../../glamor/glamor_eglmodule.c',
    'glamor_xf86_xv.c',
]

shared_module(
    'glamoregl',
    glamoregl_src,

    include_directories: [inc, xorg_inc],
    c_args: xorg_c_args,
    dependencies: [
        dep_common,
        dependency('libdrm', version: '>= 2.4.46'),
        dep_gbm,
    ],
    link_with: [glamor, libxserver_glx],

    install: true,
    install_dir: module_dir,
)
