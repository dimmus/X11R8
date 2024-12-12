manpage_config.set('vendorversion', '"XServer @0@ InputTest Driver" "X Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '4')

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