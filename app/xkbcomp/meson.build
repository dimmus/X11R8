ver_xkbcomp = '1.4.7'

f_check += ['asprintf', 'reallocarray', 'recallocarray']

dep_int_xkbcomp = [xproto, libx11, libxkbfile]

src = files(
    'action.c',
    'alias.c',
    'compat.c',
    'expr.c',
    'geometry.c',
    'indicators.c',
    'keycodes.c',
    'keymap.c',
    'keytypes.c',
    'listing.c',
    'misc.c',
    'parseutils.c',
    'symbols.c',
    'utils.c',
    'vmod.c',
    'vmod.h',
    'xkbcomp.c',
    'xkbpath.c',
    'xkbscan.c',
)

pgen = generator(
    exe_bison,
    output: ['@BASENAME@.c', '@BASENAME@.h'],
    arguments: ['@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']
)

pfiles = pgen.process('xkbparse.y')
src += pfiles

exe_xkbcomp = executable('xkbcomp',
    src,
    c_args: [
        '-DDFLT_XKB_CONFIG_ROOT="@0@"'.format(dir_data / 'X11' / 'xkb'),
        '-DXKBCOMP_PACKAGE_VERSION="@0@"'.format(ver_xkbcomp),
    ],
    dependencies: dep_int_xkbcomp,
    link_with: lib_xkb,
    install: true,
)

pkg.generate(
  name: 'xkbcomp',
  description: 'XKB keymap compiler',
  version: ver_xkbcomp,
)