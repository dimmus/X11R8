xft_version = ver_xft.split('.')

lib_args = [
  '-DXFT_MAJOR=@0@'.format(xft_version[0]),
  '-DXFT_MINOR=@0@'.format(xft_version[1]),
  '-DXFT_REVISION=@0@'.format(xft_version[2]),
]

dep_ext_xft = [dep_freetype2, dep_fontconfig]
dep_int_xft = [libxrender, libx11, xproto]

src = files(
  'xftint.h',
  'xftcolor.c',
  'xftcore.c',
  'xftdbg.c',
  'xftdpy.c',
  'xftdraw.c',
  'xftextent.c',
  'xftfont.c',
  'xftfreetype.c',
  'xftglyphs.c',
  'xftinit.c',
  'xftlist.c',
  'xftname.c',
  'xftrender.c',
  'xftstr.c',
  'xftswap.c',
  'xftxlfd.c',
)

lib = library('Xft', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: [dep_ext_xft, dep_int_xft],
  version: '1.0.0',
  install: true,
)

libxft = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X FreeType library',
  version: ver_xft,
  filebase: 'xft',
  requires: 'xproto',
  requires_private: ['xrender', 'fontconfig', 'freetype2']
)


