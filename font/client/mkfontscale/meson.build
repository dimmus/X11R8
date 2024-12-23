ver_mkfontscale = '1.2.3'

f_check += ['vasprintf']

if dep_bzip2.found()
    conf.set('X_BZIP2_FONT_COMPRESSION', 1)
endif

conf.set_quoted('MKFONTSCALE_VERSION', ver_mkfontscale)

# mkfontdir: mkfontdir.in
# 	$(AM_V_GEN)$(SED) $(DIR_SUBSTS) < $(srcdir)/mkfontdir.in > $@

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