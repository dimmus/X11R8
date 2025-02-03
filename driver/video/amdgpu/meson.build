ver_amdgpu = '23.0.0'
driver_version = ver_amdgpu.split('.')

h_check += ['misyncshm.h', 'present.h', 'dri3.h', 'byteswap.h', 'sys/endian.h']

conf.set('AMDGPU_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('AMDGPU_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('AMDGPU_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('USE_GLAMOR', '1')
conf.set('HAVE_REGIONDUPLICATE', '1')
conf.set('HAVE_FBGLYPHS', '1')
conf.set('HAVE_XF86_CURSOR_RESET_CURSOR', '1')
conf.set('HAVE_GBM_BO_USE_LINEAR', '1')
conf.set('HAVE_GBM_BO_USE_FRONT_RENDERING', '1')

dep_int_amdgpu = [xproto, xserver]
dep_ext_amdgpu = [dep_drm, dep_gbm, dep_udev]

src_kms = files(
    'src/amdgpu_bo_helper.c',
    'src/amdgpu_dri2.c',
    'src/amdgpu_dri3.c',
    'src/amdgpu_drm_queue.c',
	'src/amdgpu_kms.c',
    'src/amdgpu_present.c',
    'src/amdgpu_sync.c',
    'src/drmmode_display.c',
)

src_glamor = files(
    'src/amdgpu_glamor.c',
	'src/amdgpu_glamor_wrappers.c',
	'src/amdgpu_pixmap.c',
)

src = files(
	'src/amdgpu_video.c',
	'src/amdgpu_misc.c',
    'src/amdgpu_probe.c',
)

shared_module('amdgpu_drv', 
    [src, src_kms, src_glamor],
	name_prefix: '',
	include_directories: [
        include_directories('src'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_amdgpu, dep_ext_amdgpu],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

install_data('conf/10-amdgpu.conf', install_dir: dir_xorg_conf)