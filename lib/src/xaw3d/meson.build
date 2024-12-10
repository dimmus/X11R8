# version : 1.6.6

lib_args = ['-fvisibility=hidden']

lib_args = [
  '-DXAW_INTERNATIONALIZATION',
  '-DXAW_MULTIPLANE_PIXMAPS',
  '-DXAW_GRAY_BLKWHT_STIPPLES',
  '-DXAW_ARROW_SCROLLBARS',
]

inc_xaw3d = [
  inc_config,
  include_directories('.'),
  include_directories('src'),
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/Xaw3d'),
]

f_check += ['iswspace']
h_check += ['wctype.h', 'wchar.h', 'widec.h']

dep_int_xaw3d = [libx11, xproto, libxext, libxt, libxmu, libxpm, libi18n]

src = []

subdir('src')

# src_lex = files(
#   'src/laygram.y',
#   'src/laylex.l',
# )

lib = library('xaw3d', src,
  c_args : lib_args,
  include_directories : inc_xaw3d,
  dependencies : dep_int_xaw3d,
  version : '8.0.0',
  install : true,
)

libxaw3d = declare_dependency(
  link_with : lib,
  include_directories : inc_xaw3d,
)

meson.override_dependency('xaw3d', libxaw3d)

hdr = files(
  'include/X11/Xaw3d/MultiSrc.h',
  'include/X11/Xaw3d/MultiSrcP.h',
  'include/X11/Xaw3d/MultiSink.h',
  'include/X11/Xaw3d/MultiSinkP.h',
  'include/X11/Xaw3d/VendorEP.h',
  'include/X11/Xaw3d/XawImP.h',
  'include/X11/Xaw3d/AllWidgets.h',
  'include/X11/Xaw3d/AsciiSink.h',
  'include/X11/Xaw3d/AsciiSinkP.h',
  'include/X11/Xaw3d/AsciiSrc.h',
  'include/X11/Xaw3d/AsciiSrcP.h',
  'include/X11/Xaw3d/AsciiText.h',
  'include/X11/Xaw3d/AsciiTextP.h',
  'include/X11/Xaw3d/Box.h',
  'include/X11/Xaw3d/BoxP.h',
  'include/X11/Xaw3d/Cardinals.h',
  'include/X11/Xaw3d/Command.h',
  'include/X11/Xaw3d/CommandP.h',
  'include/X11/Xaw3d/Dialog.h',
  'include/X11/Xaw3d/DialogP.h',
  'include/X11/Xaw3d/Form.h',
  'include/X11/Xaw3d/FormP.h',
  'include/X11/Xaw3d/Grip.h',
  'include/X11/Xaw3d/GripP.h',
  'include/X11/Xaw3d/Label.h',
  'include/X11/Xaw3d/LabelP.h',
  'include/X11/Xaw3d/Layout.h',
  'include/X11/Xaw3d/LayoutP.h',
  'include/X11/Xaw3d/List.h',
  'include/X11/Xaw3d/ListP.h',
  'include/X11/Xaw3d/MenuButton.h',
  'include/X11/Xaw3d/MenuButtoP.h',
  'include/X11/Xaw3d/Paned.h',
  'include/X11/Xaw3d/PanedP.h',
  'include/X11/Xaw3d/Panner.h',
  'include/X11/Xaw3d/PannerP.h',
  'include/X11/Xaw3d/Porthole.h',
  'include/X11/Xaw3d/PortholeP.h',
  'include/X11/Xaw3d/Repeater.h',
  'include/X11/Xaw3d/RepeaterP.h',
  'include/X11/Xaw3d/Reports.h',
  'include/X11/Xaw3d/Scrollbar.h',
  'include/X11/Xaw3d/ScrollbarP.h',
  'include/X11/Xaw3d/Simple.h',
  'include/X11/Xaw3d/SimpleMenP.h',
  'include/X11/Xaw3d/SimpleMenu.h',
  'include/X11/Xaw3d/SimpleP.h',
  'include/X11/Xaw3d/SmeBSB.h',
  'include/X11/Xaw3d/SmeBSBP.h',
  'include/X11/Xaw3d/Sme.h',
  'include/X11/Xaw3d/SmeLine.h',
  'include/X11/Xaw3d/SmeLineP.h',
  'include/X11/Xaw3d/SmeP.h',
  'include/X11/Xaw3d/SmeThreeD.h',
  'include/X11/Xaw3d/SmeThreeDP.h',
  'include/X11/Xaw3d/StripCharP.h',
  'include/X11/Xaw3d/StripChart.h',
  'include/X11/Xaw3d/Text.h',
  'include/X11/Xaw3d/TextP.h',
  'include/X11/Xaw3d/TextSink.h',
  'include/X11/Xaw3d/TextSinkP.h',
  'include/X11/Xaw3d/TextSrc.h',
  'include/X11/Xaw3d/TextSrcP.h',
  'include/X11/Xaw3d/ThreeD.h',
  'include/X11/Xaw3d/ThreeDP.h',
  'include/X11/Xaw3d/Tip.h',
  'include/X11/Xaw3d/TipP.h',
  'include/X11/Xaw3d/Toggle.h',
  'include/X11/Xaw3d/ToggleP.h',
  'include/X11/Xaw3d/Tree.h',
  'include/X11/Xaw3d/TreeP.h',
  'include/X11/Xaw3d/Viewport.h',
  'include/X11/Xaw3d/ViewportP.h',
  'include/X11/Xaw3d/Xaw3dP.h',
  'include/X11/Xaw3d/XawInit.h',
  'include/X11/Xaw3d/Template.h',
  'include/X11/Xaw3d/TemplateP.h',
)

install_headers(hdr,
  subdir : 'X11/xaw3d',
)

pkg.generate(lib,
  description : 'X 3D Athena Widgets Library',
  version: '1.6.6',
  filebase : 'xrender',
  requires : ['xproto', 'xmu', 'xt'],
  requires_private: ['x11', 'xext']
)

# subdir('doc')
