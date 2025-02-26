srcs = files(
    'Args.c',
    'Color.c',
    'Cursor.c',
    'Display.c',
    'Events.c',
    'Font.c',
    'GC.c',
    'GCOps.c',
    'Handlers.c',
    'Init.c',
    'Keyboard.c',
    'Pixmap.c',
    'Pointer.c',
    'Screen.c',
    'Visual.c',
    'Window.c',
    '../../mi/miinitext.c',
    '../../mi/miinitext.h',
)

executable('Xnest',
    srcs,
    include_directories: inc_server,
    dependencies: [
        dep_common,
        libxext, libx11, libxau,
    ],
    link_with: [
        libxserver_main,
        libxserver,
        libxserver_xi_stubs,
        libxserver_xkb_stubs,
        lib_xkb,
    ],
    c_args: [
        '-DHAVE_XNEST_CONFIG_H',
        '-DDISABLE_EXT_COMPOSITE',
        '-DDISABLE_EXT_DPMS',
        '-DDISABLE_EXT_MITSHM'
    ],
    install: true,
)
