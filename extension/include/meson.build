inc_ext += [
    inc_config,
    include_directories('.'),
    include_directories('X11'),
    include_directories('X11' / 'extensions'),
]

headers = files(
  'X11/extensions/dmxext.h',
  'X11/extensions/Xcomposite.h',
  'X11/extensions/Xdamage.h',
  'X11/extensions/xf86vmode.h',
  'X11/extensions/Xfixes.h',
  'X11/extensions/XInput.h',
  'X11/extensions/XInput2.h',
  'X11/extensions/Xinerama.h',
  'X11/extensions/panoramiXext.h',
  'X11/extensions/Xrandr.h',
  'X11/extensions/Xrender.h',
  'X11/extensions/XRes.h',
  'X11/extensions/scrnsaver.h',
  'X11/extensions/Xvlib.h',
)

# Xext
headers += files(
  'X11/extensions/dpms.h',
  'X11/extensions/extutil.h',
  'X11/extensions/MITMisc.h',
  'X11/extensions/multibuf.h',
  'X11/extensions/security.h',
  'X11/extensions/shape.h',
  'X11/extensions/sync.h',
  'X11/extensions/Xag.h',
  'X11/extensions/Xcup.h',
  'X11/extensions/Xdbe.h',
  'X11/extensions/XEVI.h',
  'X11/extensions/Xext.h',
  'X11/extensions/Xge.h',
  'X11/extensions/XLbx.h',
  'X11/extensions/XShm.h',
  'X11/extensions/xtestext1.h',
)

# XF86dga
headers += files(
  'X11/extensions/Xxf86dga.h',
  'X11/extensions/xf86dga1.h',
)

# XKBfile
headers += files(
  'X11/extensions/XKM.h',
  'X11/extensions/XKBrules.h',
  'X11/extensions/XKBbells.h',
  'X11/extensions/XKBconfig.h',
  'X11/extensions/XKMformat.h',
  'X11/extensions/XKBfile.h',
)

# Xtst
headers += files(
  'X11/extensions/XTest.h',
  'X11/extensions/record.h',
)

# XvMC
headers += files(
  'X11/extensions/vldXvMC.h',
  'X11/extensions/XvMClib.h',
)

install_headers(headers,
  subdir: 'X11/extensions',
)

