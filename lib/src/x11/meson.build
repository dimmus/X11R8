inc_lib += include_directories(
  'src',
  'src' / 'util',
  'src' / 'xcms',
  'src' / 'xkb',
  'src' / 'xlibi18n',
  'src' / 'xlibi18n' / 'lcUniConv',
)

lib_args = []

f_check += ['strtol', 'seteuid', 'issetugid', 'getresuid', 'shmat', 'poll', 'nl_langinfo']
h_check += ['sys/filio.h', 'sys/select.h', 'sys/ioctl.h', 'sys/socket.h', 'dlfcn.h']

if get_option('xthreads')
  lib_args += '-DXTHREADS'
endif

if get_option('xcms')
  lib_args += '-DXCMS'
endif

if get_option('xlocale')
  lib_args += '-DXLOCALE'
endif

if get_option('xf86bigfont')
  lib_args += '-DXF86BIGFONT'
endif

if get_option('xkb')
  lib_args += '-DXKB'
endif

if get_option('composecache')
  lib_args += '-DCOMPOSECACHE' # Include compose table cache support
endif

dep_int_x11 = [xproto, libxcb]

if get_option('xthreads')
  lib_args += '-DXTHREADS'
  # This define is not in libXau specific code, but is part of the xproto header
  # This may be only required by HP-UX.
  if cc.has_function('gethostbyname_r') or \
     cc.has_function('gethostbyname_r', dependencies: cc.find_library('nls'))
    lib_args += '-DXUSE_MTSAFE_API=1'
  endif
  # if host_machine.system() == 'sunos'
  #   lib_args += ['-D_REENETRANT', '-D_POSIX_PTHREAD_SEMANTICS']
  # endif
endif

conf.set_quoted('X11_DATADIR'       , dir_data / 'X11')               # Location of libX11 data
conf.set_quoted('X11_LOCALEDATADIR' , dir_data / 'X11' / 'locale')    # Location of libX11 locale data
conf.set_quoted('X11_LIBDIR'        , dir_lib  / 'X11')               # Location of libX11 library data
conf.set_quoted('X11_LOCALELIBDIR'  , dir_lib  / 'X11' / 'locale')    # Location of libX11 locale libraries
conf.set_quoted('X11_LOCALEDIR'     , dir_lib  / 'X11' / 'locale')    # Location of libX11 locale data
conf.set_quoted('XKEYSYMDB'         , dir_data / 'X11' / 'XKeysymDB') # Location of keysym database   
conf.set_quoted('XERRORDB'          , dir_data / 'X11' / 'XErrorDB')  # Location of error message database
conf.set_quoted('XLOCALELIBDIR'     , dir_lib  / 'X11' / 'locale')
conf.set('USE_DYNAMIC_XCURSOR', 1)

subdir('modules/im')
subdir('modules/lc')
subdir('modules/om')

dep_mod_x11 = [libxlcdef, libxlibi18n, libxlcutf8load, libxomgeneric, libximcp]

subdir('src/xcms')
subdir('src/xkb')
subdir('src/xlibi18n')

## START: Generate ks_table.h
subdir('src' / 'util')
keysym_path = meson.project_source_root() / 'include' / 'X11'
keysym_h = [
  keysym_path / 'keysymdef.h',
  keysym_path / 'XF86keysym.h',
  keysym_path / 'Sunkeysym.h',
  keysym_path / 'DECkeysym.h',
  keysym_path / 'HPkeysym.h',
]
ks_table_h = custom_target('makekeystable',
  build_by_default: true,
  capture: true,
  command: [makekeys_exe, keysym_h], 
  output: 'ks_tables.h'
)
ks_table = declare_dependency(
  include_directories: inc_lib,
  sources: ks_table_h,
)
##  END: Generate ks_table.h

subdir('src')

lib_x11 = library('X11', src_x11,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: [dep_int_x11, ks_table, libxcms, libxkb, libi18n],
  version: '6.4.0',
  install: true,
)

libx11 = declare_dependency(
  link_with: lib_x11,
  include_directories: inc_lib,
)

lib_x11_xcb = library('X11-xcb', src_x11_xcb,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_x11,
  version: '1.0.0',
  install: true,
)

libx11_xcb = declare_dependency(
  link_with: lib_x11_xcb,
  include_directories: inc_lib,
)

pkg.generate(lib_x11,
  description: 'X library',
  filebase: 'x11',
  requires: ['xproto'],
  requires_private: 'xcb >= 1.11.1',
  version: ver_x11,
)

pkg.generate(lib_x11_xcb,
  description: 'X Library XCB interface',
  filebase: 'x11-xcb',
  requires: ['x11', 'x11-xcb'],
  version: ver_x11,
)

