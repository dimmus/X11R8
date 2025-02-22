ver_evdev = '2.11.0'

dep_ext_evdev = [dep_udev, dep_evdev]

src = files(
    'emuMB.c',
    'emuThird.c',
    'emuWheel.c',
    'draglock.c',
	'evdev.c'
)

shared_module('libevdev_drv', src,
	name_prefix: '',
	include_directories: [include_directories('.'), inc_server, inc_lib],
	dependencies: dep_ext_evdev,
	install: true,
	install_dir: dir_xorg_module / 'input',
)

pkg.generate(
  name: 'xorg-evdev',
  description: 'X.Org evdev input driver',
  version: ver_evdev,
)

install_data('10-evdev.conf', install_dir: dir_xorg_conf)