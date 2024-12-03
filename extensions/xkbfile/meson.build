ver_xkbfile = '1.1.3'

inc_xkbfile = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xkbfile = [xproto, libx11, libxkb]

src = files(
  'src/cout.c',
  'src/maprules.c',
  'src/srvmisc.c',
  'src/xkbatom.c',
  'src/xkbbells.c',
  'src/xkbconfig.c',
  'src/xkbdraw.c',
  'src/xkberrs.c',
  'src/XKBfileInt.h',
  'src/xkbmisc.c',
  'src/xkbout.c',
  'src/xkbtext.c',
  'src/xkmout.c',
  'src/xkmread.c'
)

lib = library('xkbfile', src,
  include_directories : inc_xkbfile,
  dependencies : dep_int_xkbfile,
  version : '1.0.2',
  install : true,
)

libxkbfile = declare_dependency(
  link_with : lib,
  include_directories : inc_xkbfile,
)

meson.override_dependency('xkbfile', libxkbfile)

hdr = files(
  'include/X11/extensions/XKM.h',
  'include/X11/extensions/XKBrules.h',
  'include/X11/extensions/XKBbells.h',
  'include/X11/extensions/XKBconfig.h',
  'include/X11/extensions/XKMformat.h',
  'include/X11/extensions/XKBfile.h'    
)

install_headers(hdr,
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The xkbfile Library',
  version: ver_xkbfile,
  filebase : 'xkbfile',
  requires : 'xproto',
  requires_private: 'x11'
)