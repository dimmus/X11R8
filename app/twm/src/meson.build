src = files(
    'add_window.c',
    'cursor.c',
    'events.c',
    'gc.c',
    'iconmgr.c',
    'icons.c',
    'list.c',
    'menus.c',
    'parse.c',
    'resize.c',
    'session.c',
    'twm.c',
    'util.c',
)

deftwmrc = custom_target(
    'deftwmrc.c',
    input:  'system.twmrc',
    output: 'deftwmrc.c',
    command: [
        find_program('gen_deftwmrc.sh'),
        '@OUTPUT@',
        '@INPUT@',
    ],
)
src += deftwmrc

# parser = custom_target(
#     'gram.[ch]',
#     input:   ['gram.y'],
#     output:  ['gram.c', 'gram.h'],
#     command: [
#         exe_bison,
#         '-y',
#         '-d',
#         '-o',
#         '@OUTPUT0@',
#         '@INPUT@',
#     ],
# )

# lexer = custom_target(
#     'lex.c',
#     input:  ['lex.l', parser[1]],
#     output: ['lex.c'],
#     command: [
#         exe_flex,
#         '-o',
#         '@OUTPUT@',
#         '@INPUT0@',
#     ],
# )

lgen = generator(
    exe_flex,
    output: '@PLAINNAME@.yy.c',
    arguments: ['-i', '-o', '@OUTPUT@', '@INPUT@']
)

lfiles = lgen.process('lex.l')
src += lfiles

pgen = generator(
    exe_bison,
    output: ['@BASENAME@.c', '@BASENAME@.h'],
    arguments: ['@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']
)

pfiles = pgen.process('gram.y')
src += pfiles

executable('twm', src,
    dependencies: twm_dependencies,
    install: true,
)

install_data(
    'system.twmrc',
    install_dir: dir_data / 'X11' / 'twm/',
)

# configure_file(
#     input: 'system.twmrc',
#     output: 'system.twmrc',
#     copy: true,
#     install: true,
#     install_dir: get_option('datadir') / 'X11/twm/',
# )
