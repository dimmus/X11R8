manpage_config = configuration_data()
manpage_config.set('vendorversion', '"Xaw @0@"  Version 11"'.format(ver_xaw))
manpage_config.set('drivermansuffix', '1')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '1')

install_man(configure_file(
    input:  'Xaw.man',
    output: 'Xaw.1',
    configuration: manpage_config,
))