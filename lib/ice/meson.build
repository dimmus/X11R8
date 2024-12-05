ver_ice = '1.1.1'

inc_ice = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11/ICE')
]

f_check += ['asprintf', 'arc4random_buf', 'getentropy']

dep_int_ice = [xproto, libxtrans]

lib_args = ['-DICE_t', '-DTRANS_CLIENT', '-DTRANS_SERVER']

src = files(
	'src/ICElibint.h',
	'src/accept.c',
	'src/authutil.c',
	'src/connect.c',
	'src/error.c',
	'src/getauth.c',
	'src/globals.h',
	'src/iceauth.c',
	'src/icetrans.c',
	'src/listen.c',
	'src/listenwk.c',
	'src/locking.c',
	'src/misc.c',
	'src/ping.c',
	'src/process.c',
	'src/protosetup.c',
	'src/register.c',
	'src/replywait.c',
	'src/setauth.c',
	'src/shutdown.c',
	'src/watch.c',
)

lib = library('ICE', src,
  c_args : lib_args,
  include_directories : inc_ice,
  dependencies : dep_int_ice,
  version : '6.3.0',
  install : true,
)

libice = declare_dependency(
  link_with : lib,
  include_directories : inc_ice,
)

hdr = files(
  'include/X11/ICE/ICE.h',
  'include/X11/ICE/ICEconn.h',
  'include/X11/ICE/ICElib.h',
  'include/X11/ICE/ICEmsg.h',
  'include/X11/ICE/ICEproto.h',
  'include/X11/ICE/ICEutil.h',
)

install_headers(hdr,
  subdir : 'X11/ICE',
)

pkg.generate(lib,
  description : 'X Inter Client Exchange Library',
  version: ver_ice,
  filebase : 'ice',
  requires : 'xproto',
)