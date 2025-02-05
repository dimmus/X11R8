ver_nouveau = '1.0.18'
driver_version = ver_nouveau.split('.')

h_check += ['misyncshm.h', 'present.h', 'dri3.h', 'byteswap.h', 'sys/endian.h']

conf.set('NOUVEAU_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('NOUVEAU_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('NOUVEAU_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_XF86_CURSOR_RESET_CURSOR', '1')
conf.set('HAVE_LIBUDEV', true)
conf.set_quoted('NV_DRIVER_DATE', '25/01/27')

dep_int_nouveau = [xproto, xserver]
dep_ext_nouveau = [dep_drm, dep_drm_nouveau, dep_gbm, dep_udev, dep_pciaccess]

src = files(
    'src/nouveau_copy.c',
    'src/nouveau_copy85b5.c',
    'src/nouveau_copy90b5.c',
    'src/nouveau_copya0b5.c',
    'src/nouveau_exa.c',
    'src/nouveau_xv.c',
    'src/nouveau_dri2.c',
    'src/nouveau_present.c',
    'src/nouveau_sync.c',
    'src/nouveau_wfb.c',
    'src/nv_accel_common.c',
    'src/nv_driver.c',
    'src/nv_shadow.c',
    'src/nv04_exa.c',
    'src/nv04_xv_ovl.c',
    'src/nv04_xv_blit.c',
    'src/nv10_exa.c',
    'src/nv10_xv_ovl.c',
    'src/nv30_exa.c',
    'src/nv30_xv_tex.c',
    'src/nv40_exa.c',
    'src/nv40_xv_tex.c',
    'src/nv50_accel.c',
    'src/nv50_exa.c',
    'src/nv50_xv.c',
    'src/nvc0_accel.c',
    'src/nvc0_exa.c',
    'src/nvc0_xv.c',
    'src/drmmode_display.c',
    'src/vl_hwmc.c',
)

shared_module('nouveau_drv', src,
	name_prefix: '',
	include_directories: [
        include_directories('src'),
        include_directories('src' / 'hwdefs'),
        include_directories('src' / 'shader'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_nouveau, dep_ext_nouveau],
    c_args: '-Wno-pointer-arith',
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)