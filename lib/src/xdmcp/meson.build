h_check += ['sys/random.h']
f_check += ['srand48', 'lrand48', 'arc4random_buf', 'getentropy']

lib_args = []
if get_option('xdmauth')
  lib_args += '-DHASXDMAUTH'
  src += 'Wraphelp.c'
endif

src = files(
  'Array.c',
  'Fill.c',
  'Flush.c',
  'Key.c',
  'Read.c',
  'Unwrap.c',
  'Wrap.c',
  'Wraphelp.c',
  'Write.c',
)

lib = library('Xdmcp', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: xproto,
  version: '6.0.0',
  install: true,
)

libxdmcp = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X Display Manager Control Protocol library',
  filebase: 'xdmcp',
  requires: 'xproto',
)