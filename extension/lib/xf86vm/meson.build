dep_int_xxf86vm = [xproto, libx11, libxext]

lib = library('Xxf86vm',
  'XF86VMode.c',
  include_directories: inc_x11,
  dependencies: dep_int_xxf86vm,
  version: '1.0.0',
  install: true,
)

libxxf86vm = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

meson.override_dependency('xxf86vm', libxxf86vm)

pkg.generate(lib,
  description: 'XFree86 Video Mode Extension Library',
  version: ver_xf86vm,
  filebase: 'xxf86vm',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)


