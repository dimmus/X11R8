ver_ati = '22.0.0'
driver_version = ver_ati.split('.')

h_check += ['misyncshm.h', 'present.h', 'dri3.h', 'byteswap.h', 'sys/endian.h']

conf.set('ATI_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('ATI_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('ATI_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_GLAMOR_GLYPHS_INIT', false)
conf.set('HAVE_GLAMOR_EGL_DESTROY_TEXTURED_PIXMAP', false)
conf.set('HAVE_GLAMOR_FINISH', false)
conf.set('USE_GLAMOR', true)
conf.set('HAVE_REGIONDUPLICATE', true)
conf.set('HAVE_FBGLYPHS', true)
conf.set('HAVE_XF86_CURSOR_RESET_CURSOR', true)

dep_int_ati = [xproto, xserver]
dep_ext_ati = [dep_drm, dep_drm_radeon, dep_gbm, dep_udev, dep_pixman]

inc_ati = [
    include_directories('.'),
    inc_config,
    inc_server,
    inc_lib,
]

src_kms = files(
    'radeon_dri2.c',
    'radeon_dri3.c',
    'radeon_drm_queue.c',
    'radeon_kms.c',
    'radeon_present.c',
    'radeon_sync.c',
    'radeon_vbo.c',
    'radeon_bo_helper.c',
    'drmmode_display.c',
)

src_exa = files(
    'radeon_exa.c',
    'r600_exa.c',
    'r6xx_accel.c',
    'r600_textured_videofuncs.c',
    'r600_shader.c',
    'radeon_exa_shared.c',
    'evergreen_exa.c',
    'evergreen_accel.c',
    'evergreen_shader.c',
    'evergreen_textured_videofuncs.c',
    'cayman_accel.c',
    'cayman_shader.c',
)

src_radeon = files(
    'radeon_accel.c',
    'radeon_video.c',
    'radeon_misc.c',
    'radeon_probe.c',
    'radeon_textured_video.c',
    'radeon_xvmc.c',
    'radeon_glamor_wrappers.c',
	'radeon_glamor.c',
)

src_radeon += src_kms + src_exa

src_ati = files(
    'ati.c',
    'atimodule.c',
)

shared_module('ati_drv',
    src_ati,
	name_prefix: '',
	include_directories: inc_ati,
	dependencies: [dep_int_ati, dep_ext_ati],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

shared_module('radeon_drv',
    src_radeon,
	name_prefix: '',
	include_directories: inc_ati,
	dependencies: [dep_int_ati, dep_ext_ati],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

install_data('10-radeon.conf', install_dir: dir_xorg_conf)