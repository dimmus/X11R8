ver_xcomposite = '0.4.6'

dep_int_xcomposite = [xproto, libx11, libxfixes]

lib = library('Xcomposite', 
  'Xcomposite.c',
  include_directories : inc_ext,
  dependencies : dep_int_xcomposite,
  version : '1.0.0',
  install : true,
)

libxcomposite = declare_dependency(
  link_with : lib,
  include_directories : inc_ext,
)

meson.override_dependency('xcomposite', libxcomposite)

pkg.generate(lib,
  description : 'X Composite Extension Library',
  version: ver_xcomposite,
  filebase : 'xcomposite',
  requires : 'xproto',
  requires_private: ['x11', 'xfixes']
)


