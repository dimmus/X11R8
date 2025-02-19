inc_xaw3d = [inc_config, include_directories('.')]

f_check += ['iswspace']
h_check += ['wctype.h', 'wchar.h', 'widec.h']

dep_int_xaw3d = [libx11, xproto, libxext, libxt, libxmu, libxpm, libi18n]

conf.set('XAW_ARROW_SCROLLBARS', true)
conf.set('XAW_MULTIPLANE_PIXMAPS', true)
conf.set('XAW_INTERNATIONALIZATION', true)
conf.set('XAW_GRAY_BLKWHT_STIPPLES', true)

src = files(
  'MultiSrc.c',
  'MultiSink.c',
  'XawIm.c',
  'XawI18n.c',
  'XawI18n.h',
  'AllWidgets.c',
  'AsciiSink.c',
  'AsciiSrc.c',
  'AsciiText.c',
  'Box.c',
  'Command.c',
  'Dialog.c',
  'Form.c',
  'Grip.c',
  'Label.c',
  'Layout.c',
  'LayYY.h',
  'List.c',
  'MenuButton.c',
  'Paned.c',
  'Panner.c',
  'Porthole.c',
  'Repeater.c',
  'Scrollbar.c',
  'Simple.c',
  'SimpleMenu.c',
  'SmeBSB.c',
  'Sme.c',
  'SmeLine.c',
  'SmeThreeD.c',
  'StripChart.c',
  'TextAction.c',
  'Text.c',
  'TextPop.c',
  'TextSink.c',
  'TextSrc.c',
  'TextTr.c',
  'ThreeD.c',
  'Tip.c',
  'Toggle.c',
  'Tree.c',
  'Vendor.c',
  'Viewport.c',
  'Xaw3dP.c',
  'XawInit.c',
  'Template.c',
)

lgen = generator(
    exe_flex,
    output: '@PLAINNAME@.yy.c',
    arguments: ['-i', '-o', '@OUTPUT@', '@INPUT@']
)

lfiles = lgen.process('laylex.l')
src += lfiles

pgen = generator(
    exe_bison,
    output: ['@BASENAME@.c', '@BASENAME@.h'],
    arguments: ['@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']
)

pfiles = pgen.process('laygram.y')
src += pfiles

lib = library('xaw3d', src,
  include_directories: inc_xaw3d,
  dependencies: dep_int_xaw3d,
  version: '8.0.0',
  install: true,
)

libxaw3d = declare_dependency(
  link_with: lib,
  include_directories: inc_xaw3d,
)

pkg.generate(lib,
  description: 'X 3D Athena Widgets Library',
  version: ver_xaw3d,
  filebase: 'xrender',
  requires: ['xproto', 'xmu', 'xt'],
  requires_private: ['x11', 'xext']
)