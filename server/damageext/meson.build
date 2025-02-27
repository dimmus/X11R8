srcs_damageext = [
	'damageext.c',
]

libxserver_damageext = static_library('libxserver_damageext',
	srcs_damageext,
	include_directories: inc_server,
	dependencies: dep_common,
	c_args: XSERVER_CFLAGS,
	link_args: XSERVER_LDFLAGS,
)
