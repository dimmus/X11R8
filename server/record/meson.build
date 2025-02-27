srcs_record = files(
	'record.c',
	'set.c',
)

libxserver_record = static_library('libxserver_record',
	srcs_record,
	include_directories: inc_server,
	dependencies: dep_common,
	c_args: XSERVER_CFLAGS,
	link_args: XSERVER_LDFLAGS,
)
