config_man = configuration_data()
config_man.set('VERSION', '@0@ @1@'.format(meson.project_name(), meson.project_version()))

configure_file(
	input: 'man/libinput.man',
	output: 'libinput.4',
	configuration: config_man,
	install_dir: dir_man / 'man4'
)