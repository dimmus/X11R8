srcs_dbe = [
	'dbe.c',
	'midbe.c',
]

libxserver_dbe = static_library('libxserver_dbe',
	srcs_dbe,
	include_directories: inc_server,
	dependencies: dep_common,
	c_args: XSERVER_CFLAGS,
)
