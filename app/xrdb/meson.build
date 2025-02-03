ver_xrdb = '1.2.2'

f_check += ['mkstemp', 'asprintf', 'reallocarray']

dep_int_xrdb = [libxmuu, libx11, xproto]

executable('xrdb', 'xrdb.c',
    c_args: '-DXRDB_PACKAGE_STRING="@0@"'.format(ver_xrdb),
    include_directories: [inc_config, inc_lib],
    dependencies: dep_int_xrdb,
    install: true,
)