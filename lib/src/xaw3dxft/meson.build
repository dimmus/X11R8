h_check += ['wctype.h', 'wchar.h', 'widec.h']
f_check += 'iswspace'

inc_xaw3dxft = [inc_config, inc_lib, include_directories('.')]

dep_int_xaw3dxft = [libx11, libxt, libxmu, libxext, libxft, libxpm, libi18n]
dep_ext_xaw3dxft = dep_freetype2

lib_args = [
  '-DXAW_INTERNATIONALIZATION',
  '-DXAW_GRAY_BLKWHT_STIPPLES',
  '-DXAW_ARROW_SCROLLBARS',
]

src = files(
  'MultiSrc.c',
  'MultiSink.c',
  'XawIm.c',
  'XawI18n.c',
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
  'Xaw3dXft.c',
  'XawInit.c',
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

lib = library('Xaw3dxft', src,
  include_directories: inc_xaw3dxft,
  dependencies: [dep_int_xaw3dxft, dep_ext_xaw3dxft],
  version: '8.5.0',
  c_args: lib_args,
  install: true,
)

libxaw3dxft = declare_dependency(
  link_with: lib,
  include_directories: inc_xaw3dxft,
)

pkg.generate(lib,
  description: 'X 3D Athena Widgets Library (Xft support)',
  version: ver_xaw3dxft,
  filebase: 'xaw3dxft',
  requires: ['xproto', 'xmu', 'xt', 'xft', 'fontconfig'],
  requires_private: ['x11', 'xext'],
)