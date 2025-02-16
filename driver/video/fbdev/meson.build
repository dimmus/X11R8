ver_fbdev = '0.5.1'
driver_version = ver_amdgpu.split('.')

conf.set('FBDEV_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('FBDEV_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('FBDEV_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])

dep_int_fbdev = [xproto, xserver, mod_fbdevhw]
dep_ext_fbdev = [dep_pciaccess, dep_pixman]

shared_module('fbdev_drv',
	'fbdev.c',
	name_prefix: '',
	include_directories: [inc_server, inc_lib],
	dependencies: [dep_int_fbdev, dep_ext_fbdev],
	link_with: libxserver_miext_shadow,
	c_args: '-Wno-discarded-qualifiers',
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)