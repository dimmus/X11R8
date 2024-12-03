ver_xdamage = '1.1.6'

inc_xdamage = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xdamage = [xproto, libx11, libxfixes]

src = files(
  'src/xdamageint.h',
  'src/Xdamage.c',
)

lib = library('Xdamage', src,
  include_directories : inc_xdamage,
  dependencies : dep_int_xdamage,
  version : '1.1.0',
  install : true,
)

libxdamage = declare_dependency(
  link_with : lib,
  include_directories : inc_xdamage,
)

meson.override_dependency('xdamage', libxdamage)

install_headers(
  'include/X11/extensions/Xdamage.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Damage  Library',
  version: ver_xdamage,
  filebase : 'xdamage',
  requires : ['xproto', 'xfixes'],
  requires_private: ['x11', 'xfixes']
)


