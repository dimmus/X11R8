ver_xinerama = '1.1.5'

inc_xinerama = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xinerama = [xproto, libx11, libxext]

src = files(
  'src/Xinerama.c',
)

lib = library('Xinerama', src,
  include_directories : inc_xinerama,
  dependencies : dep_int_xinerama,
  version : '1.0.0',
  install : true,
)

libxinerama = declare_dependency(
  link_with : lib,
  include_directories : inc_xinerama,
)

meson.override_dependency('xinerama', libxinerama)

install_headers(
  [
    'include/X11/extensions/Xinerama.h',
    'include/X11/extensions/panoramiXext.h',
  ],
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The Xinerama Library',
  version: ver_xinerama,
  filebase : 'xinerama',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


