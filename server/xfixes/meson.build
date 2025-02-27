srcs_xfixes = files(
    'cursor.c',
    'disconnect.c',
    'region.c',
    'saveset.c',
    'select.c',
    'xfixes.c',
)

libxserver_xfixes = static_library('libxserver_xfixes',
    srcs_xfixes,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)
