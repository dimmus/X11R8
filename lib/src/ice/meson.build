ver_ice = '1.1.1'

f_check += ['asprintf', 'arc4random_buf', 'getentropy']

dep_int_ice = [xproto]

lib_args = ['-DICE_t', '-DTRANS_CLIENT', '-DTRANS_SERVER']

src = files(
  'accept.c',
  'authutil.c',
  'connect.c',
  'error.c',
  'getauth.c',
  'iceauth.c',
  'icetrans.c',
  'listen.c',
  'listenwk.c',
  'locking.c',
  'misc.c',
  'ping.c',
  'process.c',
  'protosetup.c',
  'register.c',
  'replywait.c',
  'setauth.c',
  'shutdown.c',
  'watch.c',
)

lib = library('ICE', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_ice,
  version: '6.3.0',
  install: true,
)

libice = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X Inter Client Exchange Library',
  version: ver_ice,
  filebase: 'ice',
  requires: 'xproto',
)