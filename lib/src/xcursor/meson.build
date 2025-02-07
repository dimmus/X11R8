ver = ver_xcursor.split('.')

lib_args = [
  '-DXCURSOR_LIB_MAJOR=@0@'.format(ver[0]),
  '-DXCURSOR_LIB_MINOR=@0@'.format(ver[1]),
  '-DXCURSOR_LIB_REVISION=@0@'.format(ver[2]),
]

dep_int_xcursor = [xproto, libx11, libxrender, libxfixes]

conf.set('HAVE_XFIXES', true)

# TODO: implement. Need?
# ICONDIR=${datadir}/icons])
# DEF_CURSORPATH="~/.local/share/icons:~/.icons:${datadir}/icons:${datadir}/pixmaps"
# if test "x${ICONDIR}" != "x${datadir}/icons"; then
# 	DEF_CURSORPATH="${DEF_CURSORPATH}:${ICONDIR}"
# fi

src = files(
  'xcursorint.h',
  'cursor.c',
  'display.c',
  'file.c',
  'library.c',
  'xlib.c',
)

lib = library('Xcursor', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_xcursor,
  version: '1.0.2',
  install: true,
)

libxcursor = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X Cursor Library',
  version: ver_xcursor,
  filebase: 'xcursor',
  requires: 'xproto',
  requires_private: ['x11', 'xrender', 'xfixes']
)