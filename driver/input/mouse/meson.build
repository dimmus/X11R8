ver_mouse = '1.9.5'
driver_version = ver_mouse.split('.')

conf.set('MOUSE_VERSION_MAJOR',      driver_version[0])
conf.set('MOUSE_VERSION_MINOR',      driver_version[1])
conf.set('MOUSE_VERSION_PATCHLEVEL', driver_version[2])

# OS_MOUSE_NAME = 'lnx'
# OS_MOUSE_NAME = 'bsd'  # freebsd*|kfreebsd*-gnu|dragonfly*|netbsd*|openbsd*
# OS_MOUSE_NAME = 'sun'  # solaris*
# OS_MOUSE_NAME = 'hurd' # gnu*

f_check += ['asprintf', 'timingsafe_memcmp']

src = files(
	'mouse.c',
	'pnp.c',
)

# TODO: implement OS specific drivers
# if BSD
# src += files('mouse_bsd.c')
# endif

# if HURD # Gnu
# src += files('mouse_hurd.c')
# endif

# if LINUX
src += files('mouse_lnx.c')
# endif

# if SUN
# src += files('mouse_sun.c')
# endif

shared_module('libmouse_drv',
	src,
	name_prefix: '',
	include_directories: [include_directories('.'), inc_server, inc_lib],
	dependencies: [xserver, dep_pixman],
	install: true,
	install_dir: dir_xorg_module / 'input',
)

pkg.generate(
  name: 'xorg-mouse',
  description: 'X.Org mouse input driver for non-evdev OS\'es',
  version: ver_mouse,
)