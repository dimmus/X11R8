srcs_glamor = files(
    'glamor.c',
    'glamor_copy.c',
    'glamor_core.c',
    'glamor_dash.c',
    'glamor_font.c',
    'glamor_composite_glyphs.c',
    'glamor_image.c',
    'glamor_lines.c',
    'glamor_segs.c',
    'glamor_render.c',
    'glamor_gradient.c',
    'glamor_prepare.c',
    'glamor_program.c',
    'glamor_rects.c',
    'glamor_spans.c',
    'glamor_text.c',
    'glamor_transfer.c',
    'glamor_transform.c',
    'glamor_trapezoid.c',
    'glamor_triangles.c',
    'glamor_addtraps.c',
    'glamor_glyphblt.c',
    'glamor_points.c',
    'glamor_pixmap.c',
    'glamor_largepixmap.c',
    'glamor_picture.c',
    'glamor_vbo.c',
    'glamor_window.c',
    'glamor_fbo.c',
    'glamor_compositerects.c',
    'glamor_utils.c',
    'glamor_sync.c',
)

if build_glx
    srcs_glamor += 'glamor_glx_provider.c'
endif
if build_xv
    srcs_glamor += 'glamor_xv.c'
endif

glamor = static_library('glamor',
    srcs_glamor,
    include_directories: [inc_server, inc_server_glx, inc_epoxy],
    dependencies: [dep_common, dep_epoxy],
    c_args: XSERVER_CFLAGS,
    link_args: XSERVER_LDFLAGS,
)

install_data('glamor.h', install_dir: dir_xorg)