ver_xfixes = '6.0.1'

inc_xfixes = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xfixes = [xproto, libx11]

src = files(
  'src/Cursor.c',
  'src/Disconnect.c',
  'src/Region.c',
  'src/SaveSet.c',
  'src/Selection.c',
  'src/Xfixes.c',
  'src/Xfixesint.h',
)

lib = library('Xfixes', src,
  include_directories : inc_xfixes,
  dependencies : dep_int_xfixes,
  version : '3.1.0',
  install : true,
)

libxfixes = declare_dependency(
  link_with : lib,
  include_directories : inc_xfixes,
)

meson.override_dependency('xfixes', libxfixes)

install_headers(
  'include/X11/extensions/Xfixes.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Fixes  Library',
  version: ver_xfixes,
  filebase : 'xrender',
  requires : 'xproto',
  requires_private: ['x11', 'xproto']
)


