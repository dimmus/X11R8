srcs_fb = files(
	'fballpriv.c',
	'fbarc.c',
	'fbbits.c',
	'fbblt.c',
	'fbbltone.c',
	'fbcmap_mi.c',
	'fbcopy.c',
	'fbfill.c',
	'fbfillrect.c',
	'fbfillsp.c',
	'fbgc.c',
	'fbgetsp.c',
	'fbglyph.c',
	'fbimage.c',
	'fbline.c',
	'fboverlay.c',
	'fbpict.c',
	'fbpixmap.c',
	'fbpoint.c',
	'fbpush.c',
	'fbscreen.c',
	'fbseg.c',
	'fbsetsp.c',
	'fbsolid.c',
	'fbtile.c',
	'fbtrap.c',
	'fbutil.c',
	'fbwindow.c',
)

hdrs_fb = files(
	'fb.h',
	'fboverlay.h',
	'fbpict.h',
	'fbrop.h',
	'wfbrename.h'
)

libxserver_fb = static_library('libxserver_fb',
	srcs_fb,
	include_directories: inc_server,
	dependencies: dep_common,
	c_args: XSERVER_CFLAGS,
	pic: true,
)

libxserver_wfb = static_library('libxserver_wfb',
	srcs_fb,
	c_args: [XSERVER_CFLAGS, '-DFB_ACCESS_WRAPPER'],
	include_directories: inc_server,
	dependencies: dep_common,
	pic: true,
	build_by_default: false,
)

install_data(hdrs_fb, install_dir: dir_xorg)
