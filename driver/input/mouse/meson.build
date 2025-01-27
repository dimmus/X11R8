ver_mouse = '1.9.5'
driver_version = ver_mouse.split('.')

conf.set('MOUSE_VERSION_MAJOR',      driver_version[0])
conf.set('MOUSE_VERSION_MINOR',      driver_version[1])
conf.set('MOUSE_VERSION_PATCHLEVEL', driver_version[2])

f_check += ['asprintf', 'timingsafe_memcmp']

src = files(
	'src/mouse.c',
	'src/pnp.c',
)

# TODO: implement OS specific drivers
# if BSD
# src += files('bsd_mouse.c')
# endif

# if HURD # Gnu
# src += files('hurd_mouse.c')
# endif

# if LINUX
src += files('src/lnx_mouse.c')
# endif

# if SUN
# src += files('sun_mouse.c')
# endif

shared_module('libmouse_drv',
	src,
	name_prefix: '',
	include_directories: [include_directories('include'), inc_config, inc_server, inc_lib],
	dependencies: xserver,
	install: true,
	install_dir: dir_xorg_module / 'input',
)