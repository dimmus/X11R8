ver_xdamage = '1.1.6'

dep_int_xdamage = [xproto, libx11, libxfixes]

lib = library('Xdamage', 
  'Xdamage.c',
  include_directories: inc_ext,
  dependencies: dep_int_xdamage,
  version: '1.1.0',
  install: true,
)

libxdamage = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

meson.override_dependency('xdamage', libxdamage)

pkg.generate(lib,
  description: 'X Damage  Library',
  version: ver_xdamage,
  filebase: 'xdamage',
  requires: ['xproto', 'xfixes'],
  requires_private: ['x11', 'xfixes']
)


