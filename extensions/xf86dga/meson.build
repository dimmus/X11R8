ver_xf86dga = '1.1.6'

inc_xxf86dga = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xxf86dga = [xproto, libx11, libxext]

src = files(
  'src/XF86DGA.c',
  'src/XF86DGA2.c',
)

lib = library('Xxf86dga', src,
  include_directories : inc_xxf86dga,
  dependencies : dep_int_xxf86dga,
  version : '1.0.0',
  install : true,
)

libxxf86dga = declare_dependency(
  link_with : lib,
  include_directories : inc_xxf86dga,
)

meson.override_dependency('xxf86dga', libxxf86dga)

install_headers(
  [
    'include/X11/extensions/Xxf86dga.h',
    'include/X11/extensions/xf86dga1.h',
  ],
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'XFree86 Direct Graphics Access Extension Library',
  version: ver_xf86dga,
  filebase : 'xxf86dga',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)


