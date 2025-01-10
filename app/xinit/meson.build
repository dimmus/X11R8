ver_xinit = '1.4.2'

conf.set_quoted('BINDIR', dir_bin)

executable('xinit', 'xinit.c',
    include_directories: [inc_config, inc_lib],
    dependencies: [xserver, libx11],
    install: true,
)