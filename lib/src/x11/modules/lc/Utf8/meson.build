src = files(
  'lcUTF8Load.c',
)

lib = static_library('xlcUTF8Load', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_x11,
  # link_with: lib_x11,
  # version: '2.0.0',
  install: true,
)

libxlcutf8load = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)