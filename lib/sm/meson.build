ver_sm = '1.2.4'

inc_sm = [
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/SM')
]

f_check += ['uuid_create']

dep_uuid = dependency('uuid', required: false)
dep_ext_sm = [dep_uuid]
dep_int_sm = [xproto, libxtrans, libice]

src = files(
	'src/SMlibint.h',
	'src/sm_client.c',
	'src/sm_error.c',
	'src/sm_genid.c',
	'src/sm_manager.c',
	'src/sm_misc.c',
	'src/sm_process.c',
)

lib = library('SM', src,
  include_directories : inc_sm,
  dependencies : [dep_int_sm, dep_ext_sm],
  version : '6.0.1',
  install : true,
)

libsm = declare_dependency(
  link_with : lib,
  include_directories : inc_sm,
)

install_headers(
  files(
		'include/X11/SM/SM.h',
		'include/X11/SM/SMlib.h',
		'include/X11/SM/SMproto.h',
  ),
  subdir : 'X11/SM',
)

pkg.generate(lib,
  description : 'X Session Management Library',
  version: ver_sm,
  filebase : 'sm',
  requires_private : ['xproto', 'ice', 'uuid'],
)
