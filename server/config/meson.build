srcs_config = [
    'config.c',
]

dep_config = [dep_common]

if build_dbus
    srcs_config += 'dbus-core.c'
    dep_config += dep_dbus
endif

if build_hal
    srcs_config += 'hal.c'
    dep_config += dep_hal
endif

if build_udev
    srcs_config += 'udev.c'
    dep_config += dep_udev
endif

if host_machine.system() == 'netbsd' or host_machine.system() == 'openbsd'
    srcs_config += 'wscons.c'
endif

install_data('10-quirks.conf', install_dir: dir_data / 'X11' / 'xorg.conf.d')

libxserver_config = static_library('libxserver_config',
    srcs_config,
    include_directories: inc_server,
    dependencies: dep_config,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)
