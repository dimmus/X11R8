
# Initialize Autoconf - requires at least 2.64 for m4_version_prereq
AC_PREREQ([2.64])
AC_INIT([libXaw3d], [1.6.6],
        [https://gitlab.freedesktop.org/xorg/lib/libxaw3d/-/issues], [libXaw3d])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Initialize Automake
AM_INIT_AUTOMAKE([foreign dist-xz])

# Initialize libtool
LT_INIT

# Require xorg-macros minimum of 1.8 for XORG_DEFAULT_OPTIONS with XORG_INSTALL
m4_ifndef([XORG_MACROS_VERSION],
          [m4_fatal([must install xorg-macros 1.8 or later before running autoconf/autogen])])
XORG_MACROS_VERSION(1.8)
XORG_DEFAULT_OPTIONS

# Set-up Lex and Yacc, generated code is distributed
AC_PROG_YACC
AC_PATH_PROG([YACC_INST], $YACC)
if test ! -f "$srcdir/src/laygram.c"; then
   if test -z "$YACC_INST"; then
      AC_MSG_ERROR([yacc not found - unable to compile laygram.y])
   fi
fi
m4_version_prereq([2.70], [AC_PROG_LEX(noyywrap)], [AC_PROG_LEX])
AC_PATH_PROG([LEX_INST], $LEX)
if test ! -f "$srcdir/src/laylex.c"; then
   if test -z "$LEX_INST"; then
      AC_MSG_ERROR([lex not found - unable to compile laylex.y])
   fi
fi

# Checks for header files.
PKG_CHECK_MODULES(X11, [x11 xt xmu xext xproto >= 7.0.22])
AC_CHECK_HEADERS([wctype.h wchar.h widec.h])
AC_CHECK_FUNCS([iswspace])
AC_TYPE_INTPTR_T

XAW3D_CPPFLAGS=

AC_ARG_ENABLE([internationalization],
    AS_HELP_STRING([--enable-internationalization], dnl
    [enable utf8 strings (default: yes)]),
    [XAW_I18N=$enableval], [XAW_I18N=yes])
if test "x$XAW_I18N" = xyes; then
    XAW3D_CPPFLAGS="${XAW3D_CPPFLAGS} -DXAW_INTERNATIONALIZATION"
fi
AM_CONDITIONAL(XAW_INTERNATIONALIZATION, [test "x$XAW_I18N" = xyes])

AC_ARG_ENABLE([multiplane-bitmaps],
    [AS_HELP_STRING([--enable-multiplane-bitmaps], [enable XPM support])],
    [],
    [enable_multiplane_bitmaps=no])

AS_IF([test "x$enable_multiplane_bitmaps" != xno],
     [XAW3D_CPPFLAGS="${XAW3D_CPPFLAGS} -DXAW_MULTIPLANE_PIXMAPS" dnl
      PKG_CHECK_MODULES(XPM, xpm)])

AC_ARG_ENABLE([gray-stipples],
    [AS_HELP_STRING([--enable-gray-stipples], [enable gray stipples])],
    [],
    [enable_gray_stipples=no])

AS_IF([test "x$enable_gray_stipples" != xno],
    [XAW3D_CPPFLAGS="${XAW3D_CPPFLAGS} -DXAW_GRAY_BLKWHT_STIPPLES"])

AC_ARG_ENABLE([arrow-scrollbars],
    [AS_HELP_STRING([--enable-arrow-scrollbars], [enable arrow scrollbars])],
    [],
    [enable_arrow_scrollbars=no])

AS_IF([test "x$enable_arrow_scrollbars" != xno],
    [XAW3D_CPPFLAGS="${XAW3D_CPPFLAGS} -DXAW_ARROW_SCROLLBARS"])

AC_SUBST(XAW3D_CPPFLAGS)

AC_CONFIG_FILES([Makefile
		include/Makefile
		src/Makefile
		xaw3d.pc])

AC_OUTPUT
