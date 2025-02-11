ver_xauth = '1.1.3'

f_check += ['getaddrinfo', 'inet_ntop', 'reallocarray', 'strlcpy']
h_check += 'net/errno.h'

dep_int_xauth = [libxmuu, libx11, xproto, libxext, libxau]

src = files(
    'gethost.c',
    'parsedpy.c',
    'process.c',
    'xauth.c',
)

executable('xauth', src,
    c_args: '-DXAUTH_PACKAGE_VERSION="@0@"'.format(ver_xauth),
    dependencies: dep_int_xauth,
    install: true,
)