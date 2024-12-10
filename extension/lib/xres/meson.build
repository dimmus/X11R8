ver_xres = '1.2.2'

dep_int_xres = [xproto, libx11, libxext]

lib = library('Xres',
  'XRes.c',
  include_directories: inc_ext,
  dependencies: dep_int_xres,
  version: '1.0.0',
  install: true,
)

libxres = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

meson.override_dependency('xres', libxres)

pkg.generate(lib,
  description: 'X Resource Information Extension Library',
  version: ver_xres,
  filebase: 'xres',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


