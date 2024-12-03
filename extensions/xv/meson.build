ver_xv = '1.0.12'

inc_xv = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xv = [xproto, libx11, libxext]

src = files(
  'src/Xv.c',
  'src/Xvlibint.h',
)

lib = library('Xv', src,
  include_directories : inc_xv,
  dependencies : dep_int_xv,
  version : '1.0.0',
  install : true,
)

libxv = declare_dependency(
  link_with : lib,
  include_directories : inc_xv,
)

meson.override_dependency('xv', libxv)

install_headers(
  'include/X11/extensions/Xvlib.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The Xv Library',
  version: ver_xv,
  filebase : 'xv',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


