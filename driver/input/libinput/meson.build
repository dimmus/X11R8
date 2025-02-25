ver_libinput = '1.5.0'

driver_version = ver_libinput.split('.')

conf.set('LIBINPUT_VERSION_MAJOR', driver_version[0])
conf.set('LIBINPUT_VERSION_MINOR', driver_version[1])
conf.set('LIBINPUT_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_INPUTPROTO24', 1)

if cc.has_function('libinput_device_config_scroll_get_button_lock',
		   dependencies: dep_input)
	conf.set('HAVE_LIBINPUT_SCROLL_BUTTON_LOCK', 1)
endif
if cc.has_function('libinput_event_pointer_get_scroll_value_v120',
	           dependencies: dep_input)
	conf.set('HAVE_LIBINPUT_AXIS_VALUE_V120', 1)
endif
if cc.has_function('libinput_config_accel_create',
		   dependencies: dep_input)
	conf.set('HAVE_LIBINPUT_CUSTOM_ACCEL', 1)
endif
if cc.has_function('libinput_tablet_tool_config_pressure_range_set',
		   dependencies: dep_input)
	conf.set('HAVE_LIBINPUT_PRESSURE_RANGE', 1)
endif
if cc.has_function('libinput_device_config_click_set_clickfinger_button_map',
		   dependencies: dep_input)
	conf.set('HAVE_LIBINPUT_CLICKFINGER_BUTTON_MAP', 1)
endif

if cc.has_header_symbol('libinput.h', 'LIBINPUT_LED_COMPOSE')
	conf.set('HAVE_LIBINPUT_COMPOSE_AND_KANA', 1)
endif

libbezier = static_library('bezier', ['bezier.c', 'bezier.h'], include_directories: inc_config)
bezier = declare_dependency(link_with: libbezier, include_directories: inc_config)

libdraglock = static_library('draglock', ['draglock.c', 'draglock.h'], include_directories: inc_config)
draglock = declare_dependency(link_with: libdraglock, include_directories: inc_config)

dep_drivers = [
	bezier,
  	draglock,
	xproto,
	dep_input,
	dep_pixman,
]

driver_src = ['xf86libinput.c', 'util-strings.c']

shared_module('libinput_drv',
	driver_src,
	name_prefix: '',
	include_directories: [include_directories('.'), inc_server, inc_lib],
	dependencies: dep_drivers,
	install: true,
	install_dir: dir_xorg_module / 'input',
)

test_bezier = executable('test-bezier',
			 'test-bezier.c',
			 dependencies: bezier,
			 include_directories: include_directories('.'),
			 install: false)
test('test-bezier', test_bezier)

test_draglock = executable('test-draglock',
			 'test-draglock.c',
			 dependencies: draglock,
			 include_directories: include_directories('.'),
			 install: false)
test('test-draglock', test_draglock)

pkg.generate(
  name: 'xorg-libinput',
  description: 'X.Org input driver',
  version: ver_libinput,
)

install_data('40-libinput.conf', install_dir: dir_xorg_conf)