subdir('dmx')
subdir('drivers')
subdir('exa')
subdir('fbdevhw')
subdir('vfb')
# subdir('x11')
subdir('xau')
subdir('xaw')
subdir('xcb')
# subdir('xcomposite')
# subdir('xcursor')
subdir('xcvt')
subdir('xephyr')
# subdir('xext')
# subdir('xf86dga')
# subdir('xf86vm')
subdir('xfixes')
# subdir('xfree86')
# subdir('xfs')
# subdir('xft')
# subdir('xi')
# subdir('xinerama')
# subdir('xnest')
# subdir('xpm')
# subdir('xprint')
# subdir('xrandr')
# subdir('xres')
subdir('xserver')
# subdir('xss')
# subdir('xt')
# subdir('xtst')
# subdir('xv')

# WAY 1
# -------
# manpage_config = configuration_data()
# manpage_config.set('vendorversion', '"XServer @0@ Exa" "X Version 11"'.format(ver_xserver))
# manpage_config.set('drivermansuffix', '4')
# manpage_config.set('appmansuffix', '1')
# manpage_config.set('filemansuffix', '5')

# install_man(configure_file(
#     input:  'exa.man',
#     output: 'exa.4',
#     configuration: manpage_config,
# ))

# WAY 2
# -------
# custom_target(
#     'twm.1',
#     build_by_default: true,
#     capture: true,
#     input: files('twm.man'),
#     output: 'twm.1',
#     install: true,
#     install_dir: dir_man,
#     command: [
#         exe_sed,
#         '@INPUT@',
#         '-e', 's#__appmansuffix__#1#g',
#         '-e', 's#__miscmansuffix__#7#g',
#         '-e', 's#__datadir__#@0@#g'.format(dir_data),
#         '-e', 's#__projectroot__#@0@#g'.format(dir_source),
#         '-e', 's#__xorgversion__#"twm @0@" "X Version 11"#g'.format(meson.project_version()),
#     ],
# )

# WAY 3
# -------
# MAN_SUBSTS+=	-e 's|__XSERVERNAME__|$(XSERVERNAME)|g' \
# 		-e 's|__XCONFIGFILE__|$(XCONFIGFILE)|g' \
# 		-e 's|__XCONFIGFILEMAN__|$(XCONFIGFILEMAN)|g' \
# 		-e 's|__xinitdir__|$(XINITDIR)|g' \
# 		-e 's|__bindir__|$(bindir)|g' \
# 		-e 's|__libdir__|$(libdir)|g' \
# 		-e 's|__configdir__|$(XINITDIR)|g'
# MAN_SUBSTS += -e 's|__X11datadir__|$(X11_DATADIR)|g'

