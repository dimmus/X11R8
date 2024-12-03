ver_xrender = '0.9.11'

inc_xrender = [
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xrender = [libx11, xproto]

src = files(
  'src/AddTrap.c',
  'src/Color.c',
  'src/Composite.c',
  'src/Cursor.c',
  'src/FillRect.c',
  'src/FillRects.c',
  'src/Filter.c',
  'src/Glyph.c',
  'src/Picture.c',
  'src/Poly.c',
  'src/Trap.c',
  'src/Tri.c',
  'src/Xrender.c',
  'src/Xrenderint.h',
)

lib = library('Xrender', src,
  include_directories : inc_xrender,
  dependencies : dep_int_xrender,
  version : '1.3.0',
  install : true,
)

libxrender = declare_dependency(
  link_with : lib,
  include_directories : inc_xrender,
)

meson.override_dependency('xrender', libxrender)

install_headers(
  'include/X11/extensions/Xrender.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Render Library',
  version: ver_xrender,
  filebase : 'xrender',
  requires : ['xproto', 'x11'],
  requires_private: 'x11'
)
