inc_xcb += include_directories('.')

dep_int_renderutil = libxcb

src = files(
  'cache.c',
  'util.c',
  'glyph.c',
)

lib = library('xcb-util-renderutil', src,
  include_directories: inc_xcb,
  dependencies: dep_int_renderutil,
  version: '0.0.0',
  install: true,
)

renderutil = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(lib,
  name: 'XCB RenderUtil library',
  description: 'XCB RENDER-extension utilities library',
  version: '0.3.10',
  requires: ['xcb', 'xcb-render'],
)