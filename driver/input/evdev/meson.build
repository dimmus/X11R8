ver_evdev = '2.11.0'

dep_ext_evdev = [dependency('libudev'), dependency('libevdev')]
dep_int_evdev = [xserver]
dep_drivers   = [dep_int_evdev, dep_ext_evdev]

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

shared_module(
	'libevdev_drv',
	src,
	name_prefix: '', # we want libinput_drv.so, not liblibinput_drv.so
	include_directories: [include_directories('include'), inc_config, inc_server, inc_x11],
	dependencies: dep_drivers,
	install: true,
	install_dir: dir_xorg_module,
)