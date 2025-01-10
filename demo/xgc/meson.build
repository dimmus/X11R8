ver_xgc = '1.0.6'

src = files(
    'choice.c',
    'dashlist.c',
    'getfile.c',
    'interpret.c',
    'main.c',
    'planemask.c',
    'record.c',
    'testfrac.c',
    'tests.c',
    'text.c',
)

lgen = generator(
    exe_flex,
    output: '@PLAINNAME@.yy.c',
    arguments: ['-i', '-o', '@OUTPUT@', '@INPUT@']
)

lfiles = lgen.process('lex.l')
src += lfiles

pgen = generator(
    exe_bison,
    output:    ['@BASENAME@.c', '@BASENAME@.h'],
    arguments: ['@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']
)

pfiles = pgen.process('gram.y')
src += pfiles

executable('xgc', src,
    dependencies: [libxmu, libxext, libx11, libxt, libxaw, dep_m],
    include_directories: inc_lib,
    install: false
)