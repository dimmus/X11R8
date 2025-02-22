ver_xinit = '1.4.2'

conf.set_quoted('BINDIR', dir_bin)

executable('xinit', 'xinit.c',
    include_directories: [inc_config, inc_lib],
    dependencies: libx11,
    install: true,
)

install_data('startx',  install_dir: dir_bin)
install_data('xinitrc', install_dir: dir_sysconf / 'X11' / 'xinit')