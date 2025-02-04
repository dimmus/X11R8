ver_vesa = '2.6.0'
driver_version = ver_vesa.split('.')

f_check += ['strlcat', 'strlcpy', 'timingsafe_memcmp']

conf.set('VESA_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('VESA_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('VESA_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_ISA', false)

dep_int_vesa = [xproto, xserver]

shared_module('vesa_drv', 'vesa.c',
	name_prefix: '',
	include_directories: [include_directories('.'), inc_server, inc_lib],
	dependencies: dep_int_vesa,
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)