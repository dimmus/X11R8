f_check += ['uname', 'malloc_usable_size']
h_check += 'malloc.h'

dep_int_xmu  = [libxt, libxext, libx11, xproto]
dep_int_xmuu = libx11

src_muu = files(
  'ClientWin.c',
  'CursorName.c',
  'DefErrMsg.c',
  'GetHost.c',
  'Lower.c',
)

src_mu = files(
  'AllCmap.c',
  'Atoms.c',
  'Clip.c',
  'CloseHook.c',
  'CmapAlloc.c',
  'CrCmap.c',
  'CrPixFBit.c',
  'CvtCache.c',
  'CvtStdSel.c',
  'DelCmap.c',
  'DisplayQue.c',
  'Distinct.c',
  'DrawLogo.c',
  'DrRndRect.c',
  'EditresCom.c',
  'ExtAgent.c',
  'FToCback.c',
  'GrayPixmap.c',
  'Initer.c',
  'LocBitmap.c',
  'Lookup.c',
  'LookupCmap.c',
  'RdBitF.c',
  'ScrOfWin.c',
  'ShapeWidg.c',
  'StdCmap.c',
  'StrToBS.c',
  'StrToBmap.c',
  'StrToCurs.c',
  'StrToGrav.c',
  'StrToJust.c',
  'StrToLong.c',
  'StrToOrnt.c',
  'StrToShap.c',
  'StrToWidg.c',
  'UpdMapHint.c',
  'VisCmap.c',
  'WidgetNode.c',
  'Xct.c',
)

src_mu += src_muu

lib_muu = library('Xmuu', src_muu,
  include_directories: inc_lib,
  dependencies: dep_int_xmu,
  version: '1.0.0',
  install: true,
)

libxmuu = declare_dependency(
  link_with: lib_muu,
  include_directories: inc_lib,
)

lib_mu = library('Xmu', src_mu,
  include_directories: inc_lib,
  dependencies: dep_int_xmu,
  version: '6.2.0',
  install: true,
)

libxmu = declare_dependency(
  link_with: lib_mu,
  include_directories: inc_lib,
)

pkg.generate(name: 'Xmuu',
  description: 'Mini Xmu Library.',
  filebase: 'xmuu',
  requires: ['xproto', 'x11'],
  requires_private: 'x11',
  version: ver_xmu,
)

pkg.generate(name: 'Xmu',
  description: 'Xmu Library.',
  filebase: 'xmu',
  requires: ['xproto', 'x11', 'xt'],
  requires_private: ['x11', 'xt', 'xext'],
  version: ver_xmu,
)