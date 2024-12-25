ver_void = '1.4.2'

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