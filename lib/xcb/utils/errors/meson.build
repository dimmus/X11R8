inc_xcb += include_directories('.')

dep_int_errors = libxcb

src = files(
  'xcb_errors.c',
  'extensions.c', # generated by extensions.py
)

# Run command: python3 extensions.py extensions.c ../../proto/src/*.xml

# src_exten = custom_target('extensions',
#   output: 'tmp', # no need
#   command: [
#     python, 
#     dir_source / 'utils' / 'errors' / 'extensions.py', 
#     'extensions.c', 
#     dir_source / 'proto' / 'src' / '*.xml'
#   ],
# )

lib = library('xcb-util-errors', src,
  include_directories: inc_xcb,
  dependencies: dep_int_errors,
  version: '6.3.0',
  install: true,
)

libxcb_errors = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(lib,
  name: 'XCB errors library',
  description: 'XCB errors utility library',
  version: '1.0.1',
  requires: 'xcb',
)