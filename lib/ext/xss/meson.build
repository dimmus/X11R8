dep_int_xss = [xproto, libx11, libxext]

lib = library('Xss',
  'XScrnSaver.c',
  include_directories: inc_x11,
  dependencies: dep_int_xss,
  version: '1.0.0',
  install: true,
)

libxss = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

meson.override_dependency('xss', libxss)

pkg.generate(lib,
  description: 'The XScrnSaver Library',
  version: ver_xss,
  filebase: 'xss',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


