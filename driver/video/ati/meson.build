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
dep_ext_ati = [dep_drm, dep_gbm, dep_udev]

src_kms = files(
    'src/radeon_dri2.c',
    'src/radeon_dri3.c',
    'src/radeon_drm_queue.c',
    'src/radeon_kms.c',
    'src/radeon_present.c',
    'src/radeon_sync.c',
    'src/radeon_vbo.c',
    'src/radeon_bo_helper.c',
    'src/drmmode_display.c',
)

src_exa = files(
    'src/radeon_exa.c',
    'src/r600_exa.c',
    'src/r6xx_accel.c',
    'src/r600_textured_videofuncs.c',
    'src/r600_shader.c',
    'src/radeon_exa_shared.c',
    'src/evergreen_exa.c',
    'src/evergreen_accel.c',
    'src/evergreen_shader.c',
    'src/evergreen_textured_videofuncs.c',
    'src/cayman_accel.c',
    'src/cayman_shader.c',
)

src_radeon = files(
    'src/radeon_accel.c',
    'src/radeon_video.c',
    'src/radeon_misc.c',
    'src/radeon_probe.c',
    'src/radeon_textured_video.c',
    'src/radeon_xvmc.c',
    'src/radeon_glamor_wrappers.c',
	'src/radeon_glamor.c',
)

src_radeon += src_kms + src_exa

src_ati = files(
    'src/ati.c',
    'src/atimodule.c',
)

shared_module('ati_drv', src_ati,
	name_prefix: '',
	include_directories: [
        include_directories('.'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_ati, dep_ext_ati],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

shared_module('radeon_drv', src_radeon,
	name_prefix: '',
	include_directories: [
        include_directories('.'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_ati, dep_ext_ati],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

install_data('10-radeon.conf', install_dir: dir_xorg_conf)