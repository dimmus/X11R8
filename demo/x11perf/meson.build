ver_x11pef = '1.7.0'

conf.set('XRENDER', true)
conf.set('XFT', true)
conf.set('MITSHM', true)
conf.set_quoted('X11PERF_PACKAGE_STRING', ver_x11pef)

dep_ext_x11perf = [dep_m, dep_freetype2, dep_fontconfig]
dep_int_x11perf = [libx11, libxmuu, xproto, libxrender, libxft, libxext]

src = files(
    'bitmaps.c',
    'do_arcs.c',
    'do_blt.c',
    'do_complex.c',
    'do_dots.c',
    'do_lines.c',
    'do_movewin.c',
    'do_rects.c',
    'do_segs.c',
    'do_simple.c',
    'do_tests.c',
    'do_text.c',
    'do_traps.c',
    'do_tris.c',
    'do_valgc.c',
    'do_windows.c',
    'x11perf.c',
)

executable('x11perf', src,
    dependencies: [dep_int_x11perf, dep_ext_x11perf],
    include_directories: inc_lib,
    install: true
)