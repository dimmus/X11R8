src = files(
    'saa.c',
    'saa_pixmap.c',
    'saa_unaccel.c',
    'saa_render.c',
    'saa_accel.c',
)

libsaa = static_library('saa', 
    sources: src,
    dependencies: [dep_int_vmware, dep_ext_vmware],
    include_directories: inc_vmware,
    install: false
)