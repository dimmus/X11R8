dep_int_xevie = [xproto, libx11, libxcursor, libxext]

lib = library('Xevie',
  'Xevie.c',
  include_directories: inc_lib,
  dependencies: dep_int_xevie,
  version: '1.0.0',
  install: true,
)

libxevie = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

meson.override_dependency('xevie', libxevie)

pkg.generate(lib,
  description: 'XFree86 Misc Extension Library',
  version: ver_xf86misc,
  filebase: 'xevie',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


