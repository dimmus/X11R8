ver_xaw3dn = '0.15.1'

inc_xaw3dn = [inc_lib, include_directories('.')]

dep_int_xaw3dn = [libx11, xproto, libxext, libxt, libxmu, libxpm, libi18n]

src = files(
  'AllWidgets.c',
  'AsciiSink.c',
  'AsciiSrc.c',
  'AsciiText.c',
  'Box.c',
  'Clock.c',
  'Command.c',
  'Dialog.c',
  'Form.c',
  'Grip.c',
  'Label.c',
  'Layout.c',
  'List.c',
  'MenuButton.c',
  'Misc.c',
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
  'SmeThreeD.c',
  'StripChart.c',
  'Text.c',
  'TextAction.c',
  'TextPop.c',
  'TextSink.c',
  'TextSrc.c',
  'TextTr.c',
  'TextTrOld.c',
  'ThreeD.c',
  'Toggle.c',
  'Traversal.c',
  'Tree.c',
  'Vendor.c',
  'Viewport.c',
  'XawI18n.c',
  'XawIm.c',
  'XawInit.c',
  'sharedlib.c',
)

lgen = generator(
  exe_flex,
  output: '@PLAINNAME@.c',
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

lib = library('neXtaw', src,
  c_args: ['-Wno-discarded-qualifiers', '-Wno-unused-function'],
  include_directories: inc_xaw3dn,
  dependencies: dep_int_xaw3dn,
  version: '0.0.1',
  install: true,
)

libxaw3dn = declare_dependency(
  link_with: lib,
  include_directories: inc_xaw3dn,
)

pkg.generate(lib,
  description: 'X 3D NexT Athena Widgets Library',
  version: ver_xaw3dn,
  filebase: 'xrender',
  requires: ['xproto', 'xmu', 'xt'],
  requires_private: ['x11', 'xext']
)