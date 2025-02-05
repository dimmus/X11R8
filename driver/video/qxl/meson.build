ver_qxl = '0.1.6'

h_check += ['sys/inotify.h']
f_check += ['inotify_init1']

# PKG_CHECK_MODULES(LIBPCSCLITE, [libpcsclite])
# PKG_CHECK_MODULES(LIBCACARD, [libcacard])

conf.set('HAVE_XFONT2', true)
conf.set('XF86DRM_MODE', true) # DRM kernel modesetting
conf.set('HAVE_LIBUDEV', true)

dep_ext_qxl = [dep_drm, dep_pciaccess, dep_udev]
dep_int_qxl = [xserver]

inc_qxl = [
    include_directories(
        '.',
        'src',
        'src' / 'uxa'
    ),
    inc_server,
    inc_lib,
]

src = files(
    'src/qxl_driver.c',
    'src/qxl_image.c',
    'src/qxl_surface.c',
    'src/qxl_surface_ums.c',
    'src/qxl_ring.c',
    'src/qxl_mem.c',
    'src/mspace.c',
    'src/murmurhash3.c',
    'src/qxl_cursor.c',
    'src/qxl_option_helpers.c',
    'src/qxl_uxa.c',
    'src/qxl_ums_mode.c',
    'src/qxl_io.c',
    'src/dfps.c',
    'src/qxl_kms.c',
    'src/qxl_drmmode.c',
)

subdir('src/uxa')

shared_module('qxl_drv', src,
	name_prefix: '',
	include_directories: inc_qxl,
	dependencies: [dep_int_qxl, dep_ext_qxl],
    link_with: libqxl_uxa,
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)