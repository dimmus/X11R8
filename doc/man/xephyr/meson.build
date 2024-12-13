manpage_config = configuration_data()
manpage_config.set('vendorversion', '"Xserver @0@ Xephyr"  Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '4')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '1')
manpage_config.set('miscmansuffix', '1')

install_man(configure_file(
    input:  'Xephyr.man',
    output: 'Xephyr.4',
    configuration: manpage_config,
))