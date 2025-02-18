ver_synaptics = '1.9.2'
driver_version = ver_synaptics.split('.')

f_check += ['timingsafe_memcmp']

conf.set('SYNAPTICS_VERSION_MAJOR', driver_version[0])
conf.set('SYNAPTICS_VERSION_MINOR', driver_version[1])
conf.set('SYNAPTICS_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_LIBEVDEV_DEVICE_LOG_FUNCS', '1')
conf.set('BUILD_PS2COMM', '1') # Optional backend
conf.set('BUILD_EVENTCOMM', '1') # Optional backend
conf.set_quoted('SYNAPTICS_VERSION', ver_synaptics)

src = files(
	'synaptics.c',
	'synproto.c',
	'properties.c',
	'alpscomm.c',
	'ps2comm.c',
	'eventcomm.c',
)

# BSD
# src += files(
# 	'src/psmcomm.c', # need <sys/mouse.h>
# )

shared_module('synaptics_drv',
	src,
	name_prefix: '',
	include_directories: [
		include_directories('.'),
		inc_server,
		inc_lib
	],
	dependencies: [xproto, libxorg, libxi, libxtst] + dep_evdev,
	install: true,
	install_dir: dir_xorg_module / 'input',
)

executable('synclient',
    sources : 'synclient.c',
    include_directories: include_directories('.'),
    dependencies : [xproto, libx11, libxorg, libxi, libxtst] + dep_evdev,
    install : true
)

executable('syndaemon',
    sources : 'syndaemon.c',
    include_directories: include_directories('.'),
    dependencies : [xproto, libx11, libxorg, libxi, libxtst] + dep_evdev,
    install : true
)

pkg.generate(
  name: 'synaptics',
  description: 'X.Org synaptics input driver',
  version: ver_synaptics,
)

install_data('70-synaptics.conf', install_dir: dir_xorg_conf)

install_data('11-x11-synaptics.fdi',
    install_dir: dir_sysconf / 'hal' / 'fdi' / 'policy' / '20thirdparty'
)