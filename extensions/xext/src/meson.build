src = files(
	'DPMS.c',
	'MITMisc.c',
	'XAppgroup.c',
	'XEVI.c',
	'XLbx.c',
	'XMultibuf.c',
	'XSecurity.c',
	'XShape.c',
	'XShm.c',
	'XSync.c',
	'XTestExt1.c',
	'Xcup.c',
	'Xdbe.c',
    'Xge.c',
	'extutil.c',
	'extutilP.h',
	'reallocarray.c',
	'reallocarray.h',
    'globals.c',
)

lib = library('Xext', src,
  include_directories : inc_xext,
  dependencies : libx11,
  version : '6.4.0',
  install : true,
)

libxext = declare_dependency(
  link_with : lib,
  include_directories : inc_xext,
)