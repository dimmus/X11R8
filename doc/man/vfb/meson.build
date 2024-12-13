manpage_config = configuration_data()
manpage_config.set('vendorversion', '"XServer @0@ Xvfb" "X Version 11"'.format(ver_xserver))
manpage_config.set('xorgversion', '"xorg-server @0@" "X Version 11"'.format(meson.project_version()))
manpage_config.set('drivermansuffix', '4')
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '1')
manpage_config.set('miscmansuffix', '1')

install_man(configure_file(
    input:  'Xvfb.man',
    output: 'Xvfb.4',
    configuration: manpage_config,
))