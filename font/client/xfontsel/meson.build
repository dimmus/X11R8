ver_xfontsel = '1.1.1'

conf.set_quoted('XFONTSEL_VERSION', ver_xlsfonts)

# conf.set_quoted('USE_GETTEXT', 1)
# xfontsel.po: $(xfontsel_SOURCES:%=$(srcdir)/%)
# 	$(AM_V_GEN)xgettext -d xfontsel -c -n $(xfontsel_SOURCES:%=$(srcdir)/%)

# App default files
# DISTCHECK_CONFIGURE_FLAGS = --with-appdefaultdir=\$${datadir}/X11/app-defaults

dep_int_xfontsel = [xproto, libx11, libxaw, libxmu, libxt]

src = files(
    'ULabel.c',
    'xfontsel.c',
)

executable('xfontsel', src,
    dependencies: dep_int_xfontsel,
    install: true
)