src = files(
  'lcDefConv.c',
)

lib = static_library('xlcDef', src,
  c_args: lib_args,
  include_directories: inc_x11,
  dependencies: dep_ext_x11,
  # link_with: lib_x11,
  # version: '2.0.0',
  install: true,
)

libxlcdef = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)