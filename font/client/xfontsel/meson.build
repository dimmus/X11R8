ver_xfontsel = '1.1.1'

conf.set_quoted('XFONTSEL_VERSION', ver_xlsfonts)

# conf.set_quoted('USE_GETTEXT', 1)
# xfontsel.po: $(xfontsel_SOURCES:%=$(srcdir)/%)
# 	$(AM_V_GEN)xgettext -d xfontsel -c -n $(xfontsel_SOURCES:%=$(srcdir)/%)

dep_int_xfontsel = [xproto, libx11, libxaw, libxmu, libxt]

executable('xfontsel', ['ULabel.c', 'xfontsel.c'],
    dependencies: dep_int_xfontsel,
    install: true
)

install_data('app-defaults/XFontSel', install_dir: dir_sysconf / 'X11' / 'app-defaults')