dep_int_xcomposite = [xproto, libx11, libxfixes]

lib = library('Xcomposite', 
  'Xcomposite.c',
  include_directories: inc_x11,
  dependencies: dep_int_xcomposite,
  version: '1.0.0',
  install: true,
)

libxcomposite = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

meson.override_dependency('xcomposite', libxcomposite)

pkg.generate(lib,
  description: 'X Composite Extension Library',
  version: ver_xcomposite,
  filebase: 'xcomposite',
  requires: 'xproto',
  requires_private: ['x11', 'xfixes']
)


