ver_xtst = '1.2.5'

dep_int_xtst = [xproto, libx11, libxext]

src = files(
  'XRecord.c',
  'XTest.c',
)

lib = library('Xtst', src,
  include_directories : inc_ext,
  dependencies : dep_int_xtst,
  version : '6.1.0',
  install : true,
)

libxtst = declare_dependency(
  link_with : lib,
  include_directories : inc_ext,
)

meson.override_dependency('xtst', libxtst)

pkg.generate(lib,
  description : 'The Xtst Library',
  version: ver_xtst,
  filebase : 'xtst',
  requires : 'xproto',
  requires_private: ['xproto', 'x11', 'xext', 'xi']
)

