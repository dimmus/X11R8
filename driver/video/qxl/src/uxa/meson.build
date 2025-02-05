src = files(
    'uxa.c',
    'uxa-accel.c',
    'uxa-glyphs.c',
    'uxa-render.c',
    'uxa-unaccel.c',
    'uxa-damage.c',
)

libqxl_uxa = static_library('uxa', src,
    dependencies: [dep_int_qxl, dep_ext_qxl],
    include_directories: inc_qxl,
    install: false,
)