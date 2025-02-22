dep_int_xkbui = [xproto, libx11, libxkbfile]
dep_ext_xkbui = dep_m

lib = library('xkbui', 'XKBui.c',
  include_directories: inc_lib,
  dependencies: [dep_int_xkbui, dep_ext_xkbui],
  link_with: lib_xkb,
  version: '0.0.1',
  install: true,
)

libxkbui = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'The XKBui Library',
  version: ver_xkbui,
  filebase: 'xkbui',
  requires: 'xproto',
  requires_private: 'x11'
)