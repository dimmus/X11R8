dep_int_xinerama = [xproto, libx11, libxext]

lib = library('Xinerama',
  'Xinerama.c',
  include_directories: inc_lib,
  dependencies: dep_int_xinerama,
  version: '1.0.0',
  install: true,
)

libxinerama = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

meson.override_dependency('xinerama', libxinerama)

pkg.generate(lib,
  description: 'The Xinerama Library',
  version: ver_xinerama,
  filebase: 'xinerama',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


