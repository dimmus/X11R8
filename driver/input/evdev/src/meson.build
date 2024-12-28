src = files(
    'emuMB.c',
    'emuThird.c',
    'emuWheel.c',
    'draglock.c',
    'apple.c',
	'evdev.c',
)

shared_module('libevdev_drv',
	src,
	name_prefix: '',
	include_directories: [include_directories('include'), inc_config, inc_server],
	dependencies: dep_drivers,
	install: true,
	install_dir: dir_xorg_module,
)

install_data('10-evdev.conf', install_dir: dir_xorg_conf)