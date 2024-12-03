ver_xaw = '1.0.16'

inc_xaw = [
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/Xaw'),
]

f_check += ['iswalnum', 'getpagesize']
h_check += ['wctype.h', 'wchar.h', 'widec.h']

BUILD_XAW6 = false
BUILD_XAW7 = true

if WITH_UNIT_TESTS
  f_check += 'malloc_usable_size'
  h_check += 'malloc.h'
endif

dep_int_xaw = [libx11, xproto, libxext, libxt, libxmu, libxpm, libi18n]

# TODO: implement
# AC_MSG_CHECKING(if C const-support is wanted)
# AC_ARG_ENABLE(const, AS_HELP_STRING([--disable-const], [Disable const-support]),
# 	USE_CONST="$enableval", USE_CONST="yes")
# AC_MSG_RESULT($USE_CONST)
# if test "x$USE_CONST" = "xyes" ; then
# 	AC_DEFINE(_CONST_X_STRING, 1, [Define to 1 to use standard C const feature.])
# fi

src = files(
  'src/Actions.c',
  'src/AllWidgets.c',
  'src/AsciiSink.c',
  'src/AsciiSrc.c',
  'src/AsciiText.c',
  'src/Box.c',
  'src/Command.c',
  'src/Converters.c',
  'src/Dialog.c',
  'src/DisplayList.c',
  'src/Form.c',
  'src/Grip.c',
  'src/Label.c',
  'src/List.c',
  'src/MenuButton.c',
  'src/MultiSrc.c',
  'src/MultiSink.c',
  'src/OS.c',
  'src/Paned.c',
  'src/Panner.c',
  'src/Pixmap.c',
  'src/Porthole.c',
  'src/Private.h',
  'src/Repeater.c',
  'src/Scrollbar.c',
  'src/Simple.c',
  'src/SimpleMenu.c',
  'src/Sme.c',
  'src/SmeBSB.c',
  'src/SmeLine.c',
  'src/StripChart.c',
  'src/Text.c',
  'src/TextSink.c',
  'src/TextSrc.c',
  'src/TextAction.c',
  'src/TextPop.c',
  'src/TextTr.c',
  'src/Tip.c',
  'src/Toggle.c',
  'src/Tree.c',
  'src/Vendor.c',
  'src/Viewport.c',
  'src/XawIm.c',
  'src/XawInit.c',
  'src/XawI18n.c',
  'src/XawI18n.h',
)

lib = library('Xaw', src,
  include_directories : inc_xaw,
  dependencies : dep_int_xaw,
  version : '7.0.0',
  install : true,
)

libxaw = declare_dependency(
  link_with : lib,
  include_directories : inc_xaw,
)

meson.override_dependency('xaw', libxaw)

hdr = files(
  'include/X11/Xaw/AllWidgets.h',
  'include/X11/Xaw/AsciiSink.h',
  'include/X11/Xaw/AsciiSinkP.h',
  'include/X11/Xaw/AsciiSrc.h',
  'include/X11/Xaw/AsciiSrcP.h',
  'include/X11/Xaw/AsciiText.h',
  'include/X11/Xaw/AsciiTextP.h',
  'include/X11/Xaw/Box.h',
  'include/X11/Xaw/BoxP.h',
  'include/X11/Xaw/Cardinals.h',
  'include/X11/Xaw/Command.h',
  'include/X11/Xaw/CommandP.h',
  'include/X11/Xaw/Dialog.h',
  'include/X11/Xaw/DialogP.h',
  'include/X11/Xaw/Form.h',
  'include/X11/Xaw/FormP.h',
  'include/X11/Xaw/Grip.h',
  'include/X11/Xaw/GripP.h',
  'include/X11/Xaw/Label.h',
  'include/X11/Xaw/LabelP.h',
  'include/X11/Xaw/List.h',
  'include/X11/Xaw/ListP.h',
  'include/X11/Xaw/MenuButton.h',
  'include/X11/Xaw/MenuButtoP.h',
  'include/X11/Xaw/MultiSrc.h',
  'include/X11/Xaw/MultiSrcP.h',
  'include/X11/Xaw/MultiSink.h',
  'include/X11/Xaw/MultiSinkP.h',
  'include/X11/Xaw/Paned.h',
  'include/X11/Xaw/PanedP.h',
  'include/X11/Xaw/Panner.h',
  'include/X11/Xaw/PannerP.h',
  'include/X11/Xaw/Porthole.h',
  'include/X11/Xaw/PortholeP.h',
  'include/X11/Xaw/Repeater.h',
  'include/X11/Xaw/RepeaterP.h',
  'include/X11/Xaw/Reports.h',
  'include/X11/Xaw/Scrollbar.h',
  'include/X11/Xaw/ScrollbarP.h',
  'include/X11/Xaw/Simple.h',
  'include/X11/Xaw/SimpleP.h',
  'include/X11/Xaw/SimpleMenu.h',
  'include/X11/Xaw/SimpleMenP.h',
  'include/X11/Xaw/Sme.h',
  'include/X11/Xaw/SmeP.h',
  'include/X11/Xaw/SmeBSB.h',
  'include/X11/Xaw/SmeBSBP.h',
  'include/X11/Xaw/SmeLine.h',
  'include/X11/Xaw/SmeLineP.h',
  'include/X11/Xaw/StripChart.h',
  'include/X11/Xaw/StripCharP.h',
  'include/X11/Xaw/Template.c',
  'include/X11/Xaw/Template.h',
  'include/X11/Xaw/TemplateP.h',
  'include/X11/Xaw/Text.h',
  'include/X11/Xaw/TextP.h',
  'include/X11/Xaw/TextSink.h',
  'include/X11/Xaw/TextSinkP.h',
  'include/X11/Xaw/TextSrc.h',
  'include/X11/Xaw/TextSrcP.h',
  'include/X11/Xaw/Tip.h',
  'include/X11/Xaw/TipP.h',
  'include/X11/Xaw/Toggle.h',
  'include/X11/Xaw/ToggleP.h',
  'include/X11/Xaw/Tree.h',
  'include/X11/Xaw/TreeP.h',
  'include/X11/Xaw/VendorEP.h',
  'include/X11/Xaw/Viewport.h',
  'include/X11/Xaw/ViewportP.h',
  'include/X11/Xaw/XawImP.h',
  'include/X11/Xaw/XawInit.h',
)

install_headers(hdr,
  subdir : 'X11/Xaw',
)

if BUILD_XAW6
  pkg.generate(lib,
    description : 'X Athena Widgets Library, version 6',
    version: ver_xaw,
    filebase : 'xrender',
    requires : ['xproto', 'xt'],
    requires_private: ['x11', 'xext', 'xt', 'xmu']
  )
endif

if BUILD_XAW7
  pkg.generate(lib,
    description : 'X Athena Widgets Library, version 7',
    version: ver_xaw,
    filebase : 'xrender',
    requires : ['xproto', 'xt'],
    requires_private: ['x11', 'xext', 'xt', 'xmu', 'xpm']
  )
endif

# TODO: implement
# subdir('examples')