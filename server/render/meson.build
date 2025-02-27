srcs_render = files(
    'animcur.c',
    'filter.c',
    'glyph.c',
    'matrix.c',
    'miindex.c',
    'mipict.c',
    'mirect.c',
    'mitrap.c',
    'mitri.c',
    'picture.c',
    'render.c',
)

hdrs_render = files(
    'glyphstr.h',
    'mipict.h',
    'picture.h',
    'picturestr.h',
)

libxserver_render = static_library('libxserver_render',
    srcs_render,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

install_data(hdrs_render, install_dir: dir_xorg)