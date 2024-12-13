manpage_config = configuration_data()
manpage_config.set('vendorversion', '"Xfixes @0@"  Version 11"'.format(ver_xfixes))
manpage_config.set('drivermansuffix', '1')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '1')

install_man(configure_file(
    input:  'Xfixes.man',
    output: 'Xfixes.1',
    configuration: manpage_config,
))