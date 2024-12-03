ver_xss = '1.2.4'

inc_xss = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xss = [xproto, libx11, libxext]

src = files(
  'src/XScrnSaver.c',
)

lib = library('Xss', src,
  include_directories : inc_xss,
  dependencies : dep_int_xss,
  version : '1.0.0',
  install : true,
)

libxss = declare_dependency(
  link_with : lib,
  include_directories : inc_xss,
)

meson.override_dependency('xss', libxss)

install_headers(
  'include/X11/extensions/scrnsaver.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The XScrnSaver Library',
  version: ver_xss,
  filebase : 'xss',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


