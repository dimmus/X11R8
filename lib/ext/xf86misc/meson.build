dep_int_xxf86misc = [xproto, libx11, libxext]

lib = library('Xxf86misc',
  'XF86Misc.c',
  include_directories: inc_lib,
  dependencies: dep_int_xxf86misc,
  version: '1.0.0',
  install: true,
)

libxxf86misc = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

meson.override_dependency('xxf86misc', libxxf86misc)

pkg.generate(lib,
  description: 'XFree86 Misc Extension Library',
  version: ver_xf86misc,
  filebase: 'xxf86vm',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


