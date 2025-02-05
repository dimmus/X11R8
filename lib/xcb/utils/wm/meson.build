inc_xcb += include_directories('.')

dep_int_wm = libxcb

lib_iccm = library('xcb-iccm', 
  'icccm.c',
  include_directories: inc_xcb,
  dependencies: dep_int_wm,
  version: '4.0.0',
  install: true,
)

libxcb_iccm = declare_dependency(
  link_with: lib_iccm,
  include_directories: inc_xcb,
)

lib_ewmh = library('xcb-ewmh', 
  'ewmh.c',
  include_directories: inc_xcb,
  dependencies: dep_int_wm,
  version: '2.0.0',
  install: true,
)

libxcb_ewmh = declare_dependency(
  link_with: lib_ewmh,
  include_directories: inc_xcb,
)

pkg.generate(lib_iccm,
  name: 'XCB ICCCM library',
  description: 'XCB ICCCM binding',
  version: '0.4.2',
  requires: 'xcb',
)

pkg.generate(lib_ewmh,
  name: 'XCB EWMH library',
  description: 'XCB EWMH binding',
  version: '0.4.2',
  requires: 'xcb',
)