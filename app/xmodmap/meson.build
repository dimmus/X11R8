ver_xmodmap = '1.0.11'

f_check += 'asprintf'

dep_int_xmodmap = [libx11, xproto]

src = files(
    'exec.c',
    'handle.c',
    'pf.c',
    'xmodmap.c',
)

executable('xmodmap', src,
    c_args: '-DXMODMAP_PACKAGE_STRING="@0@"'.format(ver_xmodmap),
    include_directories: [inc_config, inc_lib],
    dependencies: dep_int_xmodmap,
    install: true,
)