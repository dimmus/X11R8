ver_fs = '1.0.10'

inc_font_fs = [
  include_directories('include'),
  include_directories('include' / 'X11'),
  include_directories('include' / 'X11' / 'fonts'),
]

lib_args = ['-DFS_t', '-DTRANS_CLIENT']

f_check += ['strlcpy', 'strnlen']
# TODO: AC_REPLACE_FUNCS([reallocarray])

dep_int_xfs = [xproto]

src = files(
  'src/FSCloseFt.c',
  'src/FSClServ.c',
  'src/FSConnServ.c',
  'src/FSErrDis.c',
  'src/FSErrHndlr.c',
  'src/FSFlush.c',
  'src/FSFontInfo.c',
  'src/FSFtNames.c',
  'src/FSGetCats.c',
  'src/FSlibInt.c',
  'src/FSlibint.h',
  'src/FSlibos.h',
  'src/FSListCats.c',
  'src/FSListExt.c',
  'src/FSMisc.c',
  'src/FSNextEv.c',
  'src/FSOpenFont.c',
  'src/FSOpenServ.c',
  'src/FSQGlyphs.c',
  'src/FSQuExt.c',
  'src/FSQXExt.c',
  'src/FSQXInfo.c',
  'src/FSServName.c',
  'src/FSSetCats.c',
  'src/FSSync.c',
  'src/FSSynchro.c',
  'src/fs_transport.c',
  'src/reallocarray.c',
)

lib = library('FS', src,
  c_args: lib_args,
  include_directories: [inc_font, inc_font_fs],
  dependencies: dep_int_xfs,
  version: '6.0.0',
  install: true,
)

libfs = declare_dependency(
  link_with: lib,
  include_directories: [inc_font, inc_font_fs],
)

install_headers(
  'include/X11/fonts/FSlib.h',
  subdir: 'X11/fonts',
)

pkg.generate(lib,
  description: 'Library Interface to the X Font Server',
  filebase: 'fs',
  version: ver_fs,
  requires: 'xproto',
)
