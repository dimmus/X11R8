ver_xres = '1.2.2'

inc_xres = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xres = [xproto, libx11, libxext]

src = files(
  'src/XRes.c',
)

lib = library('Xres', src,
  include_directories : inc_xres,
  dependencies : dep_int_xres,
  version : '1.0.0',
  install : true,
)

libxres = declare_dependency(
  link_with : lib,
  include_directories : inc_xres,
)

meson.override_dependency('xres', libxres)

install_headers(
 'include/X11/extensions/XRes.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Resource Information Extension Library',
  version: ver_xres,
  filebase : 'xres',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


