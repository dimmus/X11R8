ver_xrandr = '1.5.4'

dep_int_xrandr = [xproto, libx11, libxext, libxrender]

src = files(
  'Xrandr.c',
  'XrrConfig.c',
  'XrrCrtc.c',
  'XrrMode.c',
  'XrrOutput.c',
  'XrrProperty.c',
  'XrrScreen.c',
  'XrrProvider.c',
  'XrrProviderProperty.c',
  'XrrMonitor.c',
)

lib = library('Xrandr', src,
  include_directories : inc_ext,
  dependencies : dep_int_xrandr,
  version : '2.2.0',
  install : true,
)

libxrandr = declare_dependency(
  link_with : lib,
  include_directories : inc_ext,
)

meson.override_dependency('xrandr', libxrandr)

pkg.generate(lib,
  description : 'X RandR Library',
  version: ver_xrandr,
  filebase : 'xrandr',
  requires : 'xproto',
  requires_private: ['x11', 'xext', 'xrender']
)