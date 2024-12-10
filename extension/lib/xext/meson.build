ver_xext = '1.3.6'

# TODO: need?
# Determine .so library version per platform
# based on SharedXextRev in monolith xc/config/cf/*Lib.tmpl
# if test "x$XEXT_SOREV" = "x" ; then
#     case $host_os in
# 	openbsd*)	XEXT_SOREV=8:0 		;;
# 	solaris*)       XEXT_SOREV=0 		;;
# 	*)              XEXT_SOREV=6:4:0 	;;
#     esac
# fi
# AC_SUBST(XEXT_SOREV)
# AX_GCC_BUILTIN([__builtin_popcountl])
# AC_REPLACE_FUNCS([reallocarray])

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
  include_directories: inc_ext,
  dependencies: libx11,
  version: '6.4.0',
  install: true,
)

libxext = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

pkg.generate(
  name: 'Xext',
  description: 'Misc X Extension Library.',
  version: ver_xext,
  filebase: 'xext',
  requires: 'x11',
)
