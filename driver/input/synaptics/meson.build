ver_synaptics = '1.9.2'
driver_version = ver_synaptics.split('.')

f_check += ['timingsafe_memcmp']

conf.set('SYNAPTICS_VERSION_MAJOR', driver_version[0])
conf.set('SYNAPTICS_VERSION_MINOR', driver_version[1])
conf.set('SYNAPTICS_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_LIBEVDEV_DEVICE_LOG_FUNCS', '1')
conf.set('BUILD_PS2COMM', '1') # Optional backend
conf.set('BUILD_EVENTCOMM', '1') # Optional backend

src = files(
	'src/synaptics.c',
	'src/synproto.c',
	'src/properties.c',
	'src/alpscomm.c',
	'src/ps2comm.c',
	'src/eventcomm.c',
)

# BSD
# src += files(
# 	'src/psmcomm.c', # need <sys/mouse.h>
# )

shared_module('synaptics_drv', src,
	name_prefix: '',
	include_directories: [
		include_directories('src'),
		include_directories('include'),
		inc_config,
		inc_server,
		inc_lib
	],
	dependencies: [xproto, xserver, dep_evdev, libxi, libxtst],
	install: true,
	install_dir: dir_xorg_module / 'input',
)

subdir('tools')

install_data(
	'conf/70-synaptics.conf',
	install_dir: dir_xorg_conf,
)