ver_xf86vm = '1.1.5'

inc_xxf86vm = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xxf86vm = [xproto, libx11, libxext]

src = files(
  'src/XF86VMode.c',
)

lib = library('Xxf86vm', src,
  include_directories : inc_xxf86vm,
  dependencies : dep_int_xxf86vm,
  version : '1.0.0',
  install : true,
)

libxxf86vm = declare_dependency(
  link_with : lib,
  include_directories : inc_xxf86vm,
)

meson.override_dependency('xxf86vm', libxxf86vm)

install_headers(
  'include/X11/extensions/xf86vmode.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'XFree86 Video Mode Extension Library',
  version: ver_xf86vm,
  filebase : 'xxf86vm',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


