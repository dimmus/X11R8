ver_dmx = '1.1.5'

inc_dmx = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_dmx = [xproto, libx11, libxext]

src = files(
  'src/dmx.c',
)

lib = library('dmx', src,
  include_directories : inc_dmx,
  dependencies : dep_int_dmx,
  version : '1.0.0',
  install : true,
)

libdmx = declare_dependency(
  link_with : lib,
  include_directories : inc_dmx,
)

meson.override_dependency('dmx', libdmx)

install_headers(
  'include/X11/extensions/dmxext.h',
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The dmx Library',
  version: ver_dmx,
  filebase : 'dmx',
  requires : 'xproto',
  requires_private: ['x11', 'xext']
)
