dep_int_xtrap = [xproto, libx11, libxext, libxt]

src = files(
  'XECallBcks.c',
  'XEConTxt.c',
  'XEDsptch.c',
  'XEPrInfo.c',
  'XERqsts.c',
  'XEStrMap.c',
  'XETrapInit.c',
  'XEWrappers.c',
)

lib = library('XTrap', src,
  include_directories: inc_lib,
  dependencies: dep_int_xtrap,
  version: '1.0.0',
  install: true,
)

libxtrap = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

# pkg.generate(lib,
#   description: 'The XTrap Library',
#   version: ver_xtrap,
#   filebase: 'xtrap',
#   requires: 'xproto',
#   requires_private: ['x11', 'xext']
# )


