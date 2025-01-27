ver_evdev = '2.11.0'

dep_ext_evdev = [dep_udev, dep_evdev]
dep_int_evdev = [xserver]

src = files(
    'src/emuMB.c',
    'src/emuThird.c',
    'src/emuWheel.c',
    'src/draglock.c',
)

# TODO: implement support for Apple
# if APPLE
# src += fiels('src/apple.c',)
# endif

shared_module('libevdev_drv',
	src,
	name_prefix: '', # we want libinput_drv.so, not liblibinput_drv.so
	include_directories: [include_directories('include'), inc_config, inc_server, inc_lib],
	dependencies: [dep_int_evdev, dep_ext_evdev],
	install: true,
	install_dir: dir_xorg_module / 'input',
)

install_data(
	'10-evdev.conf',
	install_dir: dir_xorg_conf,
)