ver_fontenc = '1.1.8'

inc_font += include_directories('.')

# TODO: make path with $prefix defined
conf.set_quoted('FONT_ENCODINGS_DIRECTORY', '/usr/share/fonts/X11/encodings')

f_check += ['iswalnum', 'getpagesize']
h_check += ['zlib.h']
# TODO: add checking for gzclose in -lz. Need?
# TODO: AC_REPLACE_FUNCS([reallocarray])

dep_ext_fontenc = dep_zlib
dep_int_fontenc = xproto

src = files(
  'encparse.c',
  'fontenc.c',
  'reallocarray.c',
)

lib = shared_library('fontenc', src,
  include_directories: [inc_lib, inc_font],
  dependencies: [dep_int_fontenc, dep_ext_fontenc],
  version: '1.0.0',
  install: true,
)

libfontenc = declare_dependency(
  link_with: lib,
  include_directories: [inc_lib, inc_font],
)

pkg.generate(lib,
  description: 'The fontenc Library',
  version: ver_fontenc,
  filebase: 'fontenc',
)
