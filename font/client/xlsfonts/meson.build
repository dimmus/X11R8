ver_xlsfonts = '1.0.8'

conf.set_quoted('XLSFONTS_VERSION', ver_xlsfonts)

h_check += 'bsd/stdlib.h'
f_check += 'reallocarray'

dep_int_xlsfonts = [xproto, libx11]

executable('xlsfonts', ['dsimple.c', 'xlsfonts.c'],
    dependencies: dep_int_xlsfonts,
    install: true
)