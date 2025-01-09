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
  'Actions.c',
  'AllWidgets.c',
  'AsciiSink.c',
  'AsciiSrc.c',
  'AsciiText.c',
  'Box.c',
  'Command.c',
  'Converters.c',
  'Dialog.c',
  'DisplayList.c',
  'Form.c',
  'Grip.c',
  'Label.c',
  'List.c',
  'MenuButton.c',
  'MultiSrc.c',
  'MultiSink.c',
  'OS.c',
  'Paned.c',
  'Panner.c',
  'Pixmap.c',
  'Porthole.c',
  'Repeater.c',
  'Scrollbar.c',
  'Simple.c',
  'SimpleMenu.c',
  'Sme.c',
  'SmeBSB.c',
  'SmeLine.c',
  'StripChart.c',
  'Text.c',
  'TextSink.c',
  'TextSrc.c',
  'TextAction.c',
  'TextPop.c',
  'TextTr.c',
  'Tip.c',
  'Toggle.c',
  'Tree.c',
  'Vendor.c',
  'Viewport.c',
  'XawIm.c',
  'XawInit.c',
  'XawI18n.c',
)

lib = library('Xaw', src,
  include_directories: inc_x11,
  dependencies: dep_int_xaw,
  version: '7.0.0',
  install: true,
)

libxaw = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

if BUILD_XAW6
  pkg.generate(lib,
    description: 'X Athena Widgets Library, version 6',
    version: ver_xaw,
    filebase: 'xrender',
    requires: ['xproto', 'xt'],
    requires_private: ['x11', 'xext', 'xt', 'xmu']
  )
endif

if BUILD_XAW7
  pkg.generate(lib,
    description: 'X Athena Widgets Library, version 7',
    version: ver_xaw,
    filebase: 'xrender',
    requires: ['xproto', 'xt'],
    requires_private: ['x11', 'xext', 'xt', 'xmu', 'xpm']
  )
endif