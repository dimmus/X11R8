ver_twm = '1.0.12'

conf.set_quoted('APP_VERSION', ver_twm)
conf.set_quoted('DATA_DIR', dir_data)
conf.set('HAVE_XRANDR', 1)

f_check += ['mkstemp']

twm_dependencies = [
    libx11,
    libxext,
    libxt,
    libxmu,
    libice,
    libsm,
    libxrandr,
    libxkbfile,
    xproto,
]

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
    link_with: lib_i18n,
    install: true,
)

install_data('system.twmrc', install_dir: dir_data / 'X11' / 'twm/')

# configure_file(
#     input: 'system.twmrc',
#     output: 'system.twmrc',
#     copy: true,
#     install: true,
#     install_dir: dir_data / 'X11/twm/',
# )

