ver_xcomposite = '0.4.6'

inc_xcomposite = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xcomposite = [xproto, libx11, libxfixes]

src = files(
  'src/xcompositeint.h',
  'src/Xcomposite.c',
)

lib = library('Xcomposite', src,
  include_directories : inc_xcomposite,
  dependencies : dep_int_xcomposite,
  version : '1.0.0',
  install : true,
)

libxcomposite = declare_dependency(
  link_with : lib,
  include_directories : inc_xcomposite,
)

meson.override_dependency('xcomposite', libxcomposite)

install_headers(
  'include/X11/extensions/Xcomposite.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Composite Extension Library',
  version: ver_xcomposite,
  filebase : 'xcomposite',
  requires : 'xproto',
  requires_private: ['x11', 'xfixes']
)


