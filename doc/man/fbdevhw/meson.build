manpage_config = configuration_data()
manpage_config.set('vendorversion', '"XServer @0@ FBDevHW" "X Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '4')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '5')
manpage_config.set('miscmansuffix', '7')

install_man(configure_file(
    input:  'fbdevhw.man',
    output: 'fbdevhw.4',
    configuration: manpage_config,
))