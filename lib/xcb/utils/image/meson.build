inc_xcb += include_directories('.')

h_check += ['sys/shm.h']

dep_int_image = [libxcb, util]

src = files(
  'xcb_image.c',
)

lib = library('xcb-util-image', src,
  include_directories: inc_xcb,
  dependencies: dep_int_image,
  version: '0.0.0',
  install: true,
)

image = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(lib,
  name: 'XCB Image library',
  description: 'XCB image convenience library',
  version: '0.4.1',
  requires: ['xcb', 'xcb-shm'],
)