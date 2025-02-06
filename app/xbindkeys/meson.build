ver_xbindkeys = '1.8.7'

h_check += ['fcntl.h', 'stdlib.h', 'string.h', 'unistd.h']
f_check += ['strcasecmp', 'strchr', 'strrchr', 'strstr', 'strtol']

lib_args = [
    '-DFORK_FLAG',
    '-DXBK_PACKAGE_VERSION="@0@"'.format(ver_xbindkeys)
]

src = files(
    'xbindkeys.c',
    'keys.c',
    'options.c',
    'get_key.c',
    'grab_key.c',
)

executable('xbindkeys', src,
    dependencies: libx11,
    c_args: lib_args,
    install: true,
)