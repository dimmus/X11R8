ver_xft = '2.3.8'

xft_version = ver_xft.split('.')

lib_args = [
  '-DXFT_MAJOR=@0@'.format(xft_version[0]),
  '-DXFT_MINOR=@0@'.format(xft_version[1]),
  '-DXFT_REVISION=@0@'.format(xft_version[2]),
]

inc_xft = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/Xft'),
]

dep_ext_xft = [dep_freetype2, dep_fontconfig]
dep_int_xft = [libxrender, libx11, xproto]

src = files(
  'src/xftint.h',
  'src/xftcolor.c',
  'src/xftcore.c',
  'src/xftdbg.c',
  'src/xftdpy.c',
  'src/xftdraw.c',
  'src/xftextent.c',
  'src/xftfont.c',
  'src/xftfreetype.c',
  'src/xftglyphs.c',
  'src/xftinit.c',
  'src/xftlist.c',
  'src/xftname.c',
  'src/xftrender.c',
  'src/xftstr.c',
  'src/xftswap.c',
  'src/xftxlfd.c',
)

lib = library('Xft', src,
  c_args : lib_args,
  include_directories : inc_xft,
  dependencies : [dep_ext_xft, dep_int_xft],
  version : '1.0.0',
  install : true,
)

libxft = declare_dependency(
  link_with : lib,
  include_directories : inc_xft,
)

meson.override_dependency('xft', libxft)

install_headers(
  'include/X11/Xft/XftCompat.h',
  'include/X11/Xft/Xft.h',
  subdir : 'X11/Xft',
)

pkg.generate(lib,
  description : 'X FreeType library',
  version: ver_xft,
  filebase : 'xft',
  requires : 'xproto',
  requires_private: ['xrender', 'fontconfig', 'freetype2']
)


