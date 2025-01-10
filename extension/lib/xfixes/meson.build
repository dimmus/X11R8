dep_int_xfixes = [xproto, libx11]

src = files(
  'Cursor.c',
  'Disconnect.c',
  'Region.c',
  'SaveSet.c',
  'Selection.c',
  'Xfixes.c',
  'Xfixesint.h',
)

lib = library('Xfixes', src,
  include_directories: inc_x11,
  dependencies: dep_int_xfixes,
  version: '3.1.0',
  install: true,
)

libxfixes = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

meson.override_dependency('xfixes', libxfixes)

pkg.generate(lib,
  description: 'X Fixes  Library',
  version: ver_xfixes,
  filebase: 'xrender',
  requires: 'xproto',
  requires_private: ['x11', 'xproto']
)


