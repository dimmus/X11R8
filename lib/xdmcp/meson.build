ver_xdmcp = '1.1.5'

inc_xdmcp = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
]

lib_args = []

h_check += ['sys/random.h']
f_check += ['srand48', 'lrand48', 'arc4random_buf', 'getentropy']

src = files(
  'Array.c',
  'Fill.c',
  'Flush.c',
  'Key.c',
  'Read.c',
  'Unwrap.c',
  'Wrap.c',
  'Wrap.h',
  'Write.c',
)

if get_option('xdmauth')
  lib_args += '-DHASXDMAUTH'
  src += 'Wraphelp.c'
endif

lib = library('Xdmcp', src,
  c_args : lib_args,
  include_directories : inc_xdmcp,
  dependencies : xproto,
  version : '6.0.0',
  install : true,
)

test('array',
  executable('array',
    'test/Array.c',
    link_with : lib,
    include_directories : inc_xdmcp,
    dependencies : xproto,
  )
)

libxdmcp = declare_dependency(
  link_with : lib,
  include_directories : inc_xdmcp,
)

meson.override_dependency('xdmcp', libxdmcp)

install_headers(
  'include/X11/Xdmcp.h',
  subdir : 'X11',
)

pkg.generate(lib,
  description : 'X Display Manager Control Protocol library',
  filebase : 'xdmcp',
  requires : 'xproto',
)

# TODO: implement
# subdir('test')
