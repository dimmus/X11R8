subdir('src' / 'xau')
subdir('src' / 'xdmcp')
subdir('xcb')
subdir('src' / 'x11')     # <- xcb
subdir('src' / 'ice')
subdir('src' / 'sm')
subdir('src' / 'xt')
subdir('src' / 'xcvt')
subdir('ext' / 'xrender')
subdir('ext' / 'xfixes')
subdir('src' / 'xft')     # <- ext/xrender
subdir('src' / 'xcursor') # <- ext/xrender, ext/xfixes
subdir('ext' / 'xext')
subdir('src' / 'xpm')     # <- ext/xext
subdir('src' / 'xmu')     # <- ext/xext
subdir('src' / 'xaw')     # <- ext/xext
subdir('src' / 'xaw3d')
subdir('ext' / 'xrandr')
subdir('ext' / 'xdamage')
subdir('ext' / 'xcomposite')
subdir('ext' / 'xinerama')
subdir('ext' / 'xkbfile')
subdir('ext' / 'xss')
subdir('ext' / 'xi')
subdir('ext' / 'xres')
subdir('ext' / 'xtst')
subdir('ext' / 'xv')
subdir('ext' / 'xvmc')
subdir('ext' / 'xf86dga')
subdir('ext' / 'xf86vm')
subdir('ext' / 'dmx')
if WITH_TESTS
subdir('test')
endif
subdir('example')

summary_lib += {'XTHREADS_DBG': WITH_XTHREAD_DBG}
summary_lib += {'XCMS': get_option('xcms')}
summary_lib += {'XLOCALE': get_option('xlocale')}
summary_lib += {'XF86BIGFONT': get_option('xf86bigfont')}
summary_lib += {'XKB': get_option('xkb')}
summary_lib += {'COMPOSECACHE': get_option('composecache')}
summary_lib += {'ZFILE-OPEN': get_option('zfile-open')}
summary_lib += {'ZFILE-STAT': get_option('zfile-stat')}
summary_lib += {'SXPM': get_option('sxpm')}
summary_lib += {'PIXMAN': WITH_INT_PIXMAN ? 'internal' : 'external'}
summary_lib += {'EPOXY':  WITH_INT_EPOXY  ? 'internal' : 'external'}
summary_lib += {'TEST': WITH_TESTS ? true : false}
summary_lib += {'DOC': WITH_DOC ? true : false}
if WITH_DOC
summary_lib += {'MAN': WITH_DOC_MAN ? true : false}
endif