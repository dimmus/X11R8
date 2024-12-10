ver_xrender = '0.9.11'

dep_int_xrender = [libx11, xproto]

src = files(
  'AddTrap.c',
  'Color.c',
  'Composite.c',
  'Cursor.c',
  'FillRect.c',
  'FillRects.c',
  'Filter.c',
  'Glyph.c',
  'Picture.c',
  'Poly.c',
  'Trap.c',
  'Tri.c',
  'Xrender.c',
  'Xrenderint.h',
)

lib = library('Xrender', src,
  include_directories: inc_ext,
  dependencies: dep_int_xrender,
  version: '1.3.0',
  install: true,
)

libxrender = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

meson.override_dependency('xrender', libxrender)

pkg.generate(lib,
  description: 'X Render Library',
  version: ver_xrender,
  filebase: 'xrender',
  requires: ['xproto', 'x11'],
  requires_private: 'x11'
)
