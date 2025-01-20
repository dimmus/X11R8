inc_xcb += include_directories('.')

dep_int_keysyms = libxcb

lib = library('xcb-util-keysyms', 'keysyms.c',
  include_directories: inc_xcb,
  dependencies: dep_int_keysyms,
  version: '1.0.0',
  install: true,
)

keysyms = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(lib,
  name: 'XCB Keysyms library',
  description: 'XCB Keysyms',
  version: '0.4.1',
  requires: 'xcb',
)