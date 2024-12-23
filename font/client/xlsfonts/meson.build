ver_xlsfonts = '1.0.8'

conf.set_quoted('XLSFONTS_VERSION', ver_xlsfonts)

# Checks for library functions
# AC_SEARCH_LIBS([reallocarray], [bsd])
# AS_IF([test "x$ac_cv_search_reallocarray" = "x-lbsd"],
#       [AC_CHECK_HEADERS([bsd/stdlib.h])])
# AC_CHECK_FUNCS([reallocarray])

dep_int_xlsfonts = [xproto, libx11]

src = files(
    'dsimple.c',
    'xlsfonts.c',
)

executable('xlsfonts', src,
    dependencies: dep_int_xlsfonts,
    install: true
)