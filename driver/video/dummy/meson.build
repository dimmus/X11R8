ver_dummy = '0.4.1'
driver_version = ver_amdgpu.split('.')

conf.set('DUMMY_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('DUMMY_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('DUMMY_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('XFree86LOADER', true)

dep_int_dummy = [xproto, xserver]
dep_ext_dummy = dep_pixman

src = files(
    'dummy_cursor.c',
    'dummy_driver.c',
)

shared_module('dummy_drv',
	src,
	name_prefix: '',
	include_directories: [include_directories('.'), inc_server, inc_lib],
	dependencies: [dep_int_dummy, dep_ext_dummy],
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)