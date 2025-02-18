ver_armsoc = '1.4.1'
driver_version = ver_armsoc.split('.')

h_check += ['sys/ioctl.h', 'stdint.h']

conf.set('ARMSOC_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('ARMSOC_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('ARMSOC_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])

dep_int_armsoc = [xproto, libxorg]
dep_ext_armsoc = [dep_drm, dep_pixman]

src = files(
    'src/drmmode_exynos/drmmode_exynos.c',
    'src/drmmode_pl111/drmmode_pl111.c',
    'src/drmmode_kirin/drmmode_kirin.c',
    'src/drmmode_sti/drmmode_sti.c',
)

src += files(
    'src/drmmode_display.c',
    'src/armsoc_exa.c',
    'src/armsoc_exa_null.c',
    'src/armsoc_dri2.c',
    'src/armsoc_driver.c',
    'src/armsoc_dumb.c',
)


shared_module('armsoc_drv', 
    [src, src_kms, src_glamor],
	name_prefix: '',
	include_directories: [
        include_directories('src'),
        include_directories('src/umplock'),
        inc_config,
        inc_server,
        inc_lib,
    ],
	dependencies: [dep_int_armsoc, dep_ext_armsoc],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)