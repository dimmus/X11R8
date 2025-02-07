ver_xkbui = '0.0.1'

dep_int_xkbui = [xproto, libx11, libxkb]

lib = library('xkbui', 'XKBui.c',
  include_directories: inc_lib,
  dependencies: dep_int_xkbui,
  version: '0.0.1',
  install: true,
)

libxkbui = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'The xkbui Library',
  version: ver_xkbui,
  filebase: 'xkbui',
  requires: 'xproto',
  requires_private: 'x11'
)