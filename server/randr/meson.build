srcs_randr = files(
    'randr.c',
    'rrcrtc.c',
    'rrdispatch.c',
    'rrinfo.c',
    'rrlease.c',
    'rrmode.c',
    'rrmonitor.c',
    'rroutput.c',
    'rrpointer.c',
    'rrproperty.c',
    'rrprovider.c',
    'rrproviderproperty.c',
    'rrscreen.c',
    'rrsdispatch.c',
    'rrtransform.c',
)

hdrs_randr = files(
    'randrstr.h',
    'rrtransform.h',
)

if build_xinerama
    srcs_randr += 'rrxinerama.c'
endif

libxserver_randr = static_library('libxserver_randr',
    srcs_randr,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
)

install_data(hdrs_randr, install_dir: dir_xorg)