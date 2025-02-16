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
dep_ext_nouveau = [dep_drm, dep_drm_nouveau, dep_gbm, dep_udev, dep_pciaccess, dep_pixman]

src = files(
    'nouveau_copy.c',
    'nouveau_copy85b5.c',
    'nouveau_copy90b5.c',
    'nouveau_copya0b5.c',
    'nouveau_exa.c',
    'nouveau_xv.c',
    'nouveau_dri2.c',
    'nouveau_present.c',
    'nouveau_sync.c',
    'nouveau_wfb.c',
    'nv_accel_common.c',
    'nv_driver.c',
    'nv_shadow.c',
    'nv04_exa.c',
    'nv04_xv_ovl.c',
    'nv04_xv_blit.c',
    'nv10_exa.c',
    'nv10_xv_ovl.c',
    'nv30_exa.c',
    'nv30_xv_tex.c',
    'nv40_exa.c',
    'nv40_xv_tex.c',
    'nv50_accel.c',
    'nv50_exa.c',
    'nv50_xv.c',
    'nvc0_accel.c',
    'nvc0_exa.c',
    'nvc0_xv.c',
    'drmmode_display.c',
    'vl_hwmc.c',
)

shared_module('nouveau_drv',
    src,
	name_prefix: '',
	include_directories: [
        include_directories('.'),
        include_directories('hwdefs'),
        include_directories('shader'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_nouveau, dep_ext_nouveau],
    c_args: '-Wno-pointer-arith',
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)