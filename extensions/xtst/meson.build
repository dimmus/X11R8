ver_xtst = '1.2.5'

inc_xtst = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xtst = [xproto, libx11, libxext]

src = files(
  'src/XRecord.c',
  'src/XTest.c',
)

lib = library('Xtst', src,
  include_directories : inc_xtst,
  dependencies : dep_int_xtst,
  version : '6.1.0',
  install : true,
)

libxtst = declare_dependency(
  link_with : lib,
  include_directories : inc_xtst,
)

meson.override_dependency('xtst', libxtst)

install_headers(
  [
    'include/X11/extensions/XTest.h',
    'include/X11/extensions/record.h',
  ],
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'The Xtst Library',
  version: ver_xtst,
  filebase : 'xtst',
  requires : 'xproto',
  requires_private: ['xproto', 'x11', 'xext', 'xi']
)

