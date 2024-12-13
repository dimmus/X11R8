manpage_config = configuration_data()
manpage_config.set('vendorversion', '"X11-XCB @0@"  Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '1')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '1')

install_man(configure_file(
    input:  'xcb-examples.man',
    output: 'xcb-examples.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input:  'xcb-requests.man',
    output: 'xcb-requests.1',
    configuration: manpage_config,
))