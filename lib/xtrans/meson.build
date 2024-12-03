ver_xtrans = '1.5.1'

lib_args = '-DHAS_STICKY_DIR_BIT'

f_check += ['fchown']

inc_xtrans = include_directories('.')

src = files(
	'Xtrans.h',
	'Xtrans.c',
	'Xtransint.h',
	'Xtranslcl.c',
	'Xtranssock.c',
	'Xtransutil.c',
	'transport.c',
)

install_headers(src,
  subdir : 'X11/Xtrans',
)

libxtrans = declare_dependency(
	include_directories: inc_xtrans
)

pkg.generate(
  name: 'xtrans',
  description : 'Abstract network code for X',
  filebase : 'xtrans',
  extra_cflags: [lib_args, '-D_DEFAULT_SOURCE']
)
