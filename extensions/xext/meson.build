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

inc_xext = [
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

hdr = files(
  'include/X11/extensions/dpms.h',
  'include/X11/extensions/extutil.h',
  'include/X11/extensions/MITMisc.h',
  'include/X11/extensions/multibuf.h',
  'include/X11/extensions/security.h',
  'include/X11/extensions/shape.h',
  'include/X11/extensions/sync.h',
  'include/X11/extensions/Xag.h',
  'include/X11/extensions/Xcup.h',
  'include/X11/extensions/Xdbe.h',
  'include/X11/extensions/XEVI.h',
  'include/X11/extensions/Xext.h',
  'include/X11/extensions/Xge.h',
  'include/X11/extensions/XLbx.h',
  'include/X11/extensions/XShm.h',
  'include/X11/extensions/xtestext1.h',
)

install_headers(hdr,
  subdir : 'X11/extensions',
)

pkg.generate(
  name : 'Xext',
  description : 'Misc X Extension Library.',
  version: ver_xext,
  filebase : 'xext',
  requires : 'x11',
)

subdir('src')
# subdir('spec')
