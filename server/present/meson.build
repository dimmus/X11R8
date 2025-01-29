srcs_present = [
    'present.c',
    'present_event.c',
    'present_execute.c',
    'present_fake.c',
    'present_fence.c',
    'present_notify.c',
    'present_request.c',
    'present_scmd.c',
    'present_screen.c',
    'present_vblank.c',
]

hdrs_present = [
    'present.h',
    'presentext.h',
]

libxserver_present = static_library('libxserver_present',
    srcs_present,
    include_directories: inc_server,
    dependencies: [dep_common, dep_epoll],
)

install_data(hdrs_present, install_dir: dir_xorg)