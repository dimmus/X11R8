ver_xawplus = '3.1.0'

dep_int_xawplus = [libx11, xproto, libxext, libxt, libxmu, libxpm]

src = files(
    'AsciiSink.c',
    'AsciiSrc.c',
    'AsciiText.c',
    'Box.c',
    'Command.c',
    'Dialog.c',
    'DrawingArea.c',
    'Form.c',
    'Grip.c',
    'Label.c',
    'List.c',
    'LocPixmap.c',
    'MenuButton.c',
    'MultiSink.c',
    'MultiSrc.c',
    'Paned.c',
    'Panner.c',
    'Porthole.c',
    'Repeater.c',
    'Scrollbar.c',
    'Simple.c',
    'SimpleMenu.c',
    'Sme.c',
    'SmeBSB.c',
    'SmeLine.c',
    'StrToPmap.c',
    'StripChart.c',
    'Text.c',
    'TextAction.c',
    'TextPop.c',
    'TextSink.c',
    'TextSrc.c',
    'TextTr.c',
    'Toggle.c',
    'Tree.c',
    'UTF8.c',
    'Vendor.c',
    'Viewport.c',
    'XawI18n.c',
    'XawIm.c',
    'XawInit.c',
)

lib = library('XawPlus', src,
  include_directories: inc_lib,
  dependencies: dep_int_xawplus,
  link_with: lib_i18n,
  version: '1.0.0',
  install: true,
)

libxawplus = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)