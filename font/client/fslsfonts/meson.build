ver_fsls = '1.0.7'

h_check += 'bsd/stdlib.h'
f_check += 'reallocarray'

dep_int_fsls = [xproto, libx11, libfs]

executable('fslsfonts', 'fslsfonts.c',
    dependencies: dep_int_fsls,
    c_args: '-DFSLSFONTS_PACKAGE_STRING="@0@"'.format(ver_fsls),
    install: true
)
