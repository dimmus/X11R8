ver_mkfontscale = '1.2.3'

f_check += 'vasprintf'

conf.set('X_BZIP2_FONT_COMPRESSION', dep_bzip2.found())
conf.set_quoted('MKFONTSCALE_VERSION', ver_mkfontscale)

dep_ext_mkfontscale = [dep_freetype2, dep_zlib, dep_bzip2]
dep_int_mkfontscale = [xproto, libx11, libfontenc]

src = files(
    'constlist.c',
    'hash.c',
    'ident.c',
    'list.c',
    'mkfontscale.c',
)

executable('mkfontscale', src,
    dependencies: [dep_int_mkfontscale, dep_ext_mkfontscale],
    install: true
)

conf_mkfont = configuration_data()
conf_mkfont.set('BINDIR', dir_bin)
configure_file(
    input:  'mkfontdir.in',
    output: 'mkfontdir',
    install_dir: dir_bin,
    configuration: conf_mkfont,
)
