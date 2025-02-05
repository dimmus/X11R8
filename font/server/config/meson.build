xfs_config = configuration_data()

DEFAULT_FONT_PATH = [
    dir_data / 'X11' / 'fonts' / 'misc',
    dir_data / 'X11' / 'fonts' / 'OTF',
    dir_data / 'X11' / 'fonts' / 'TTF',
    dir_data / 'X11' / 'fonts' / 'Type1',
    dir_data / 'X11' / 'fonts' / '75dpi',
    dir_data / 'X11' / 'fonts' / '100dpi',
]

xfs_config.set('DEFAULTFONTPATH', ','.join(DEFAULT_FONT_PATH))
# xfs_config.set('DEFAULTFONTPATH', dir_sysconf / 'X11' / 'fontpath.d')
xfs_config.set('FSERRORS', '/var/log/xfs.log')

configure_file(
    input:  'config.in',
    output: 'config',
    configuration: xfs_config,
    install_dir: dir_sysconf / 'X11' / 'fs',
)