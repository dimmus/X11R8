ver_xf86dga = '1.1.6'

dep_int_xxf86dga = [xproto, libx11, libxext]

src = files(
  'XF86DGA.c',
  'XF86DGA2.c',
)

lib = library('Xxf86dga', src,
  include_directories: inc_ext,
  dependencies: dep_int_xxf86dga,
  version: '1.0.0',
  install: true,
)

libxxf86dga = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

meson.override_dependency('xxf86dga', libxxf86dga)

pkg.generate(lib,
  description: 'XFree86 Direct Graphics Access Extension Library',
  version: ver_xf86dga,
  filebase: 'xxf86dga',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


