ver_qxl = '0.1.6'

h_check += 'sys/inotify.h'
f_check += 'inotify_init1'

# PKG_CHECK_MODULES(LIBPCSCLITE, [libpcsclite])
# PKG_CHECK_MODULES(LIBCACARD, [libcacard])

conf.set('HAVE_XFONT2',  true)
conf.set('XF86DRM_MODE', true) # DRM kernel modesetting
conf.set('HAVE_LIBUDEV', true)

dep_ext_qxl = [dep_drm, dep_pciaccess, dep_udev]
dep_int_qxl = [xserver]

inc_qxl = [
    include_directories('uxa'),
    inc_server,
    inc_lib,
]

src = files(
    'qxl_driver.c',
    'qxl_image.c',
    'qxl_surface.c',
    'qxl_surface_ums.c',
    'qxl_ring.c',
    'qxl_mem.c',
    'mspace.c',
    'murmurhash3.c',
    'qxl_cursor.c',
    'qxl_option_helpers.c',
    'qxl_uxa.c',
    'qxl_ums_mode.c',
    'qxl_io.c',
    'dfps.c',
    'qxl_kms.c',
    'qxl_drmmode.c',
)

subdir('uxa')

shared_module('qxl_drv',
    src,
	name_prefix: '',
	include_directories: inc_qxl,
	dependencies: [dep_int_qxl, dep_ext_qxl],
    link_with: libqxl_uxa,
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)