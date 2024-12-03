ver_xrandr = '1.5.4'

inc_xrandr = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xrandr = [xproto, libx11, libxext, libxrender]

src = files(
  'src/Xrandr.c',
  'src/Xrandrint.h',
  'src/XrrConfig.c',
  'src/XrrCrtc.c',
  'src/XrrMode.c',
  'src/XrrOutput.c',
  'src/XrrProperty.c',
  'src/XrrScreen.c',
  'src/XrrProvider.c',
  'src/XrrProviderProperty.c',
  'src/XrrMonitor.c',
)

lib = library('Xrandr', src,
  include_directories : inc_xrandr,
  dependencies : dep_int_xrandr,
  version : '2.2.0',
  install : true,
)

libxrandr = declare_dependency(
  link_with : lib,
  include_directories : inc_xrandr,
)

meson.override_dependency('xrandr', libxrandr)

install_headers(
  'include/X11/extensions/Xrandr.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X RandR Library',
  version: ver_xrandr,
  filebase : 'xrandr',
  requires : 'xproto',
  requires_private: ['x11', 'xext', 'xrender']
)