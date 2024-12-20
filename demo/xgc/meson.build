ver_xgc = '1.0.6'

gram = custom_target('gram.[ch]',
  input:   ['gram.y'],
  output:  ['gram.c', 'gram.h'],
  command: [
    find_program('bison'),
    '-y',
    '-d',
    '-o',
    '@OUTPUT0@',
    '@INPUT@',
  ],
)

lex = custom_target('lex.c',
  input:   ['lex.l', gram[1]],
  output:  'lex.yy.c',
  command: [
    find_program('flex'),
    '-o',
    '@OUTPUT@',
    '@INPUT0@',
  ],
)

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
    lex,
    gram,
)

executable('xgc', src,
    dependencies: [libxmu, libxext, libx11, libxt, libxaw, dep_m],
    include_directories: inc_x11,
    install: false
)