fb = static_library('fb',
	sources : [
		'fbarc.c',
		'fbbitmap.c',
		'fbblt.c',
		'fbbltone.c',
		'fbclip.c',
		'fbcopy.c',
		'fbfill.c',
		'fbgc.c',
		'fbglyph.c',
		'fbimage.c',
		'fbline.c',
		'fbpict.c',
		'fbpoint.c',
		'fbpush.c',
		'fbseg.c',
		'fbspan.c',
		'fbstipple.c',
		'fbtile.c',
		'fbutil.c',
	],
	dependencies : [
		libx11,
		dep_pixman,
	],
	include_directories: inc_intel,
	c_args : [
		'-Wno-unused-parameter',
		'-Wno-sign-compare',
	],
	install : false
)
