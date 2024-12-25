ver_xinit = '1.4.2'

conf.set_quoted('BINDIR', dir_bin)

src = files(
    'xinit.c',
)

executable('xinit', src,
    include_directories: [inc_config, inc_x11],
    dependencies: [xserver, libx11],
    install: true,
)