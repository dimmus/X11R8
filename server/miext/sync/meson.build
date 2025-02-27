srcs_miext_sync = files(
    'misync.c',
    'misyncfd.c',
)

hdrs_miext_sync = files(
    'misync.h',
    'misyncfd.h',
    'misyncshm.h',
    'misyncstr.h',
)

if build_dri3
    srcs_miext_sync += 'misyncshm.c'
endif

libxserver_miext_sync = static_library('libxserver_miext_sync',
    srcs_miext_sync,
    include_directories: inc_server,
    dependencies: [dep_common, libxshmfence],
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

install_data(hdrs_miext_sync, install_dir: dir_xorg)