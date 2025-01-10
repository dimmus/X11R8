dep_int_dmx = [xproto, libx11, libxext]

lib = library('dmx', 
  'dmx.c',
  include_directories: inc_lib,
  dependencies: dep_int_dmx,
  version: '1.0.0',
  install: true,
)

libdmx = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

meson.override_dependency('dmx', libdmx)

pkg.generate(lib,
  description: 'The dmx Library',
  version: ver_dmx,
  filebase: 'dmx',
  requires: 'xproto',
  requires_private: ['x11', 'xext']
)
