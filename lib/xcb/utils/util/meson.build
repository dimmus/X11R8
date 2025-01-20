inc_xcb += include_directories('.')

dep_int_util = libxcb

f_check += ['vasprintf']

src = files(
  'atoms.c',
  'event.c',
  'xcb_aux.c',
)

lib = library('xcb-util', src,
  include_directories: inc_xcb,
  dependencies: dep_int_util,
  version: '1.0.0',
  install: true,
)

util = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(
  name: 'XCB Atom library',
  description: 'XCB atom cache',
  version: '0.4.1',
  requires: 'xcb',
)

pkg.generate(
  name: 'XCB Aux library',
  description: 'XCB convenient functions',
  version: '0.4.1',
  requires: 'xcb',
)

pkg.generate(
  name: 'XCB Event library',
  description: 'XCB event callback interface',
  version: '0.4.1',
  requires: 'xcb',
)

pkg.generate(
  name: 'XCB Util Core library',
  description: 'XCB util core interface',
  version: '0.4.1',
  requires: 'xcb',
)