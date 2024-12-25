ver_void = '1.4.2'
driver_version = ver_void.split('.')

conf.set('VOID_VERSION_MAJOR', driver_version[0])
conf.set('VOID_VERSION_MINOR', driver_version[1])
conf.set('VOID_VERSION_PATCHLEVEL', driver_version[2])

src_driver = files(
    'void.c',
)

shared_module('libvoid_drv',
	src_driver,
	name_prefix: '',
	include_directories: [inc_config, inc_server],
	dependencies: xserver,
	install: true,
	install_dir: dir_xorg_module,
)