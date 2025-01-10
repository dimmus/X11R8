dep_int_xkbfile = [xproto, libx11, libxkb]

src = files(
  'cout.c',
  'maprules.c',
  'srvmisc.c',
  'xkbatom.c',
  'xkbbells.c',
  'xkbconfig.c',
  'xkbdraw.c',
  'xkberrs.c',
  'xkbmisc.c',
  'xkbout.c',
  'xkbtext.c',
  'xkmout.c',
  'xkmread.c'
)

lib = library('xkbfile', src,
  include_directories: inc_lib,
  dependencies: dep_int_xkbfile,
  version: '1.0.2',
  install: true,
)

libxkbfile = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

meson.override_dependency('xkbfile', libxkbfile)

pkg.generate(lib,
  description: 'The xkbfile Library',
  version: ver_xkbfile,
  filebase: 'xkbfile',
  requires: 'xproto',
  requires_private: 'x11'
)