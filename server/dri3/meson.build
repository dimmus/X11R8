srcs_dri3 = [
	'dri3.c',
	'dri3_request.c',
	'dri3_screen.c',
]

libxserver_dri3 = []
if build_dri3
    libxserver_dri3 = static_library('libxserver_dri3',
        srcs_dri3,
        include_directories: inc_server,
        dependencies: [dep_common, dep_drm],
        c_args: XSERVER_CFLAGS,
        link_args: XSERVER_LDFLAGS,
    )
endif

install_data('dri3.h', install_dir: dir_xorg)