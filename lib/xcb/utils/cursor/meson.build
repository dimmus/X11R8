inc_xcb += include_directories('.')

f_check += ['le32toh']
h_check += ['endian.h', 'sys/endian.h', 'sys/byteorder.h', 'libkern/OSByteOrder.h']

lib_args = '-DXCURSORPATH="~/.local/share/icons:~/.icons:@0@/icons:@0@/pixmaps"'.format(dir_data)

dep_int_cursor = [libxcb, libxcb_renderutil, libxcb_image]

src = files(
  'cursor.c',
  'shape_to_id.c', # generated by gperf
  'load_cursor.c',
  'parse_cursor_file.c',
)

lib = library('xcb-util-cursor', src,
  include_directories: inc_xcb,
  dependencies: dep_int_cursor,
  c_args: lib_args,
  version: '0.0.0',
  install: true,
)

libxcb_cursor = declare_dependency(
  link_with: lib,
  include_directories: inc_xcb,
)

pkg.generate(lib,
  name: 'XCB cursor library',
  description: 'XCB cursor utility library',
  version: '0.1.5',
  requires: 'xcb',
  requires_private: ['xcb-render', 'xcb-renderutil', 'xcb-image'],
)

# gperf = find_program('gperf', required: false)
# Run command: gperf --includes --struct-type --language=ANSI-C --switch=1 shape_to_id.gperf > shape_to_id.c