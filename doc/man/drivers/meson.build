manpage_config = configuration_data()
manpage_config.set('vendorversion', '"XServer @0@ InputTest Driver" "X Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '4')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '5')
manpage_config.set('miscmansuffix', '7')
manpage_config.set('xconfigfile', 'xorg.conf')
manpage_config.set('xservername', 'Xorg')

install_man(configure_file(
    input:  'inputtestdrv.man',
    output: 'inputtestdrv.4',
    configuration: manpage_config,
))

install_man(configure_file(
    input:  'modesetting.man',
    output: 'modesetting.4',
    configuration: manpage_config,
))