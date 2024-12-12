manpage_config.set('vendorversion', '"XServer @0@ Exa" "X Version 11"'.format(ver_xserver))
manpage_config.set('drivermansuffix', '4')

install_man(configure_file(
    input:  'exa.man',
    output: 'exa.4',
    configuration: manpage_config,
))