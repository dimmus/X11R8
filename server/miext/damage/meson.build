srcs_miext_damage = files(
	'damage.c',
)

hdrs_miext_damage = files(
	'damage.h',
	'damagestr.h',
)

libxserver_miext_damage = static_library('libxserver_miext_damage',
	srcs_miext_damage,
	include_directories: inc_server,
	dependencies: dep_common,
	c_args: XSERVER_CFLAGS,
)

install_data(hdrs_miext_damage, install_dir: dir_xorg)