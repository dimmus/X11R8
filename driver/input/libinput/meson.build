ver_driver_libinput = '1.5.0'
driver_version = ver_driver_libinput.split('.')

dep_libinput = dependency('libinput', version: '>= 1.11.0')

conf.set('LIBINPUT_VERSION_MAJOR', driver_version[0])
conf.set('LIBINPUT_VERSION_MINOR', driver_version[1])
conf.set('LIBINPUT_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_INPUTPROTO24', 1)

if cc.has_function('libinput_device_config_scroll_get_button_lock',
		   dependencies: dep_libinput)
	conf.set('HAVE_LIBINPUT_SCROLL_BUTTON_LOCK', 1)
endif
if cc.has_function('libinput_event_pointer_get_scroll_value_v120',
	           dependencies: dep_libinput)
	conf.set('HAVE_LIBINPUT_AXIS_VALUE_V120', 1)
endif
if cc.has_function('libinput_config_accel_create',
		   dependencies: dep_libinput)
	conf.set('HAVE_LIBINPUT_CUSTOM_ACCEL', 1)
endif
if cc.has_function('libinput_tablet_tool_config_pressure_range_set',
		   dependencies: dep_libinput)
	conf.set('HAVE_LIBINPUT_PRESSURE_RANGE', 1)
endif
if cc.has_function('libinput_device_config_click_set_clickfinger_button_map',
		   dependencies: dep_libinput)
	conf.set('HAVE_LIBINPUT_CLICKFINGER_BUTTON_MAP', 1)
endif

if cc.has_header_symbol('libinput.h', 'LIBINPUT_LED_COMPOSE')
	conf.set('HAVE_LIBINPUT_COMPOSE_AND_KANA', 1)
endif

libbezier = static_library('bezier', ['src/bezier.c', 'src/bezier.h'], include_directories: inc_config)
bezier = declare_dependency(link_with: libbezier, include_directories: inc_config)

libdraglock = static_library('draglock', ['src/draglock.c', 'src/draglock.h'], include_directories: inc_config)
draglock = declare_dependency(link_with: libdraglock, include_directories: inc_config)

dep_drivers = [
	xproto,
	xserver,
  	dep_libinput,
	xserver,
  	bezier,
  	draglock,
	dep_pixman
]

driver_src = ['src/xf86libinput.c', 'src/util-strings.c']
shared_module(
	'libinput_drv',
	driver_src,
	name_prefix: '', # we want libinput_drv.so, not liblibinput_drv.so
	include_directories: [include_directories('include'), inc_config, inc_server],
	dependencies: dep_drivers,
	install: true,
	install_dir: dir_xorg_module,
)

test_bezier = executable('test-bezier',
			 ['test/test-bezier.c'],
			 dependencies: bezier,
			 include_directories: include_directories('src'),
			 install: false)
test('test-bezier', test_bezier)

test_draglock = executable('test-draglock',
			 ['test/test-draglock.c'],
			 dependencies: draglock,
			 include_directories: include_directories('src'),
			 install: false)
test('test-draglock', test_draglock)


# conf_pkgconf = configuration_data()
# conf_pkgconf.set('PACKAGE_VERSION', meson.project_version())
# conf_pkgconf.set('sdkdir', dir_headers)

# configure_file(
# 	input: 'xorg-libinput.pc.in',
# 	output: 'xorg-libinput.pc',
# 	configuration: conf_pkgconf,
# 	install_dir: dir_pkgconf,
# )

install_data('conf/40-libinput.conf', install_dir: dir_xorg_conf)