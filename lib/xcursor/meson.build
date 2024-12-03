ver_xcursor = '1.2.3'

conf.set('XCURSOR_LIB_MAJOR', 1)
conf.set('XCURSOR_LIB_MINOR', 2)
conf.set('XCURSOR_LIB_REVISION', 3)

inc_xcursor = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/Xcursor'),
]

dep_int_xcursor = [xproto, libx11, libxrender, libxfixes]

conf.set('HAVE_XFIXES', 1)

# TODO: implement. Need?
# AC_ARG_WITH(icondir,
#         AS_HELP_STRING([--with-icondir=<path>],
#                        [Set default icon directory (default: ${datadir}/icons)]),
#         [ICONDIR="$withval"],
#         [ICONDIR=${datadir}/icons])
# AC_SUBST([ICONDIR])

# DEF_CURSORPATH="~/.local/share/icons:~/.icons:${datadir}/icons:${datadir}/pixmaps"
# if test "x${ICONDIR}" != "x${datadir}/icons"; then
# 	DEF_CURSORPATH="${DEF_CURSORPATH}:${ICONDIR}"
# fi
# AC_ARG_WITH(cursorpath,
#         AS_HELP_STRING([--with-cursorpath=<paths>],
#                        [Set default search path for cursors]),
#         [XCURSORPATH="$withval"],
#         [XCURSORPATH=$DEF_CURSORPATH])
# AC_SUBST([XCURSORPATH])

src = files(
  'src/xcursorint.h',
  'src/cursor.c',
  'src/display.c',
  'src/file.c',
  'src/library.c',
  'src/xlib.c',
)

lib = library('Xcursor', src,
  include_directories : inc_xcursor,
  dependencies : dep_int_xcursor,
  version : '1.0.2',
  install : true,
)

libxcursor = declare_dependency(
  link_with : lib,
  include_directories : inc_xcursor,
)

meson.override_dependency('xcursor', libxcursor)

install_headers(
  'include/X11/Xcursor/Xcursor.h',
  subdir : 'X11/Xcursor',
)

pkg.generate(lib,
  description : 'X Cursor Library',
  version: ver_xcursor,
  filebase : 'xcursor',
  requires : 'xproto',
  requires_private: ['x11', 'xrender', 'xfixes']
)


