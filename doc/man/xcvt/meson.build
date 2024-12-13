manpage_config = configuration_data()
manpage_config.set('appmansuffix', '1')
manpage_config.set('filemansuffix', '5')
manpage_config.set('vendorversion', '"libxcvt @0@" "X Version 11"'.format(ver_xcvt))

install_man(configure_file(
	input: 'cvt.man',
	output: 'cvt.1',
	# install_dir: join_paths(man, 'man1'),
	configuration: manpage_config
))
