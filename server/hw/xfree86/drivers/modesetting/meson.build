modesetting_srcs = [
    'dri2.c',
    'driver.c',
    'drmmode_display.c',
    'dumb_bo.c',
    'pageflip.c',
    'present.c',
    'vblank.c',
]

shared_module('modesetting_drv',
    modesetting_srcs,
    name_prefix: '',
    include_directories: inc_server,
    c_args: XFREE86_CFLAGS,
    dependencies: [
        dep_common,
        dep_udev,
        dep_drm,
        dep_gbm,
    ],
    install: true,
    install_dir: dir_xorg_module / 'drivers',
)

# Test that we don't have any unresolved symbols from our module to Xorg.
xorg_build_root = dir_build / 'server' / 'hw' / 'xfree86'
symbol_test_args = []
symbol_test_args += xorg_build_root / 'libxorgserver.so'
symbol_test_args += xorg_build_root / 'dixmods' / 'libshadow.so'
if dep_gbm.found()
    symbol_test_args += xorg_build_root / 'glamor_egl' / 'libglamoregl.so'
endif
symbol_test_args += xorg_build_root / 'drivers' / 'modesetting' / 'modesetting_drv.so'

test('xserver - modesetting symbol',
    xorg_symbol_test,
    args: symbol_test_args,
)
