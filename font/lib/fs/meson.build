ver_fs = '1.0.10'

lib_args = ['-DFS_t', '-DTRANS_CLIENT']

f_check += ['strlcpy', 'strnlen']
# TODO: AC_REPLACE_FUNCS([reallocarray])

dep_int_xfs = [xproto]

src = files(
  'FSCloseFt.c',
  'FSClServ.c',
  'FSConnServ.c',
  'FSErrDis.c',
  'FSErrHndlr.c',
  'FSFlush.c',
  'FSFontInfo.c',
  'FSFtNames.c',
  'FSGetCats.c',
  'FSlibInt.c',
  'FSlibint.h',
  'FSlibos.h',
  'FSListCats.c',
  'FSListExt.c',
  'FSMisc.c',
  'FSNextEv.c',
  'FSOpenFont.c',
  'FSOpenServ.c',
  'FSQGlyphs.c',
  'FSQuExt.c',
  'FSQXExt.c',
  'FSQXInfo.c',
  'FSServName.c',
  'FSSetCats.c',
  'FSSync.c',
  'FSSynchro.c',
  'fs_transport.c',
  'reallocarray.c',
)

lib = library('FS', src,
  c_args: lib_args,
  include_directories: [inc_lib, include_directories('.')],
  dependencies: dep_int_xfs,
  version: '6.0.0',
  install: true,
)

libfs = declare_dependency(
  link_with: lib,
  include_directories: [inc_lib, include_directories('.')],
)

# Warning: already generated pkg-config for FS
# pkg.generate(lib,
#   description: 'Library Interface to the X Font Server',
#   filebase: 'fs',
#   version: ver_fs,
#   requires: 'xproto',
# )
