dep_int_xv = [xproto, libx11, libxext]

lib = library('Xv',
  'Xv.c',
  include_directories: inc_x11,
  dependencies: dep_int_xv,
  version: '1.0.0',
  install: true,
)

libxv = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

meson.override_dependency('xv', libxv)

pkg.generate(lib,
  description: 'The Xv Library',
  version: ver_xv,
  filebase: 'xv',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


