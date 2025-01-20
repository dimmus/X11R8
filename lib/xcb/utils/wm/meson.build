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

# Run command: m4 ewmh.c.m4 > ewmh.c

# exe_m4 = find_program('m4', required: true)

# gen_ewmh_c = custom_target('gen_ewmh_c',
#   input: 'ewmh.c.m4',
#   output: 'ewmh.c',
#   build_by_default: true,
#   capture: true,
#   command: [
#     exe_m4,
#     dir_source / 'utils' / 'wm' / 'ewmh.c.m4'
#   ],
# )

# custom_target('gen_ewmh_h',
#   input: 'xcb_ewmh.h.m4',
#   output: 'ewmh.h',
#   build_by_default: true,
#   capture: true,
#   command: [
#     exe_m4, 
#     dir_source / 'utils' / 'wm' / 'xcb_ewmh.h.m4', 
#   ],
#   install_dir: dir_include / 'xcb',
# )

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