ver_xau = '1.0.11'

inc_xau = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
]

f_check += ['explicit_bzero', 'explicit_memset', 'pathconf']
h_check += ['unistd.h']

# TODO: implement
# if test "x$xthreads" = "xyes" ; then
#     AC_DEFINE(XTHREADS,1,[Whether libXau is compiled with thread support])
#     AC_CHECK_LIB(c, gethostbyname_r, [mtsafe=yes])
#     if test "x$mtsafe" = "x" ; then
# 	AC_CHECK_LIB(nsl, gethostbyname_r, [mtsafe=yes])
#     fi
#     if test "x$mtsafe" = "xyes" ; then
# 	AC_DEFINE(XUSE_MTSAFE_API, 1,
# 		  [Whether libXau needs to use MT safe API's])
#     fi

# # XXX incomplete, please fill this in
#     case $host_os in
#     solaris*)
# 	XTHREAD_CFLAGS="-D_REENTRANT -D_POSIX_PTHREAD_SEMANTICS" ;;
#     esac
#     XAU_CFLAGS="$XAU_CFLAGS $XTHREAD_CFLAGS"
# fi

lib = library('Xau',
  [
    'AuDispose.c',
    'AuFileName.c',
    'AuGetAddr.c',
    'AuGetBest.c',
    'AuLock.c',
    'AuRead.c',
    'AuUnlock.c',
    'AuWrite.c',
  ],
  include_directories : inc_xau,
  dependencies : xproto,
  version : '6.0.0',
  install : true,
)

test('autest',
  executable('autest',
    'Autest.c',
    link_with : lib,
    include_directories : inc_xau,
    dependencies : xproto,
  )
)

libxau = declare_dependency(
  link_with : lib,
  include_directories : inc_xau,
)

meson.override_dependency('xau', libxau)

install_headers(
  'include/X11/Xauth.h',
  subdir : 'X11',
)

pkg.generate(lib,
  description : 'X authorization file management library',
  version: ver_xau,
  filebase : 'xau',
  requires : 'xproto',
)