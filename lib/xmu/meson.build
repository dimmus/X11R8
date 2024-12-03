ver_xmu = '1.2.1'

inc_xmu = [
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/Xmu'),
]

f_check += ['uname']

dep_ext_xmu = [libxt, libxext, libx11, xproto]
dep_ext_xmuu = [libx11]

# TODO: need?
# AC_REPLACE_FUNCS([reallocarray])

if WITH_UNIT_TESTS
  f_check += 'malloc_usable_size'
  h_check += 'malloc.h'
endif

hdr = files(
	'include/X11/Xmu/Xmu.h',
	'include/X11/Xmu/Atoms.h',
	'include/X11/Xmu/CharSet.h',
	'include/X11/Xmu/CloseHook.h',
	'include/X11/Xmu/Converters.h',
	'include/X11/Xmu/CurUtil.h',
	'include/X11/Xmu/CvtCache.h',
	'include/X11/Xmu/DisplayQue.h',
	'include/X11/Xmu/Drawing.h',
	'include/X11/Xmu/Editres.h',
	'include/X11/Xmu/EditresP.h',
	'include/X11/Xmu/Error.h',
	'include/X11/Xmu/ExtAgent.h',
	'include/X11/Xmu/Initer.h',
	'include/X11/Xmu/Lookup.h',
	'include/X11/Xmu/Misc.h',
	'include/X11/Xmu/StdSel.h',
	'include/X11/Xmu/StdCmap.h',
	'include/X11/Xmu/SysUtil.h',
	'include/X11/Xmu/WidgetNode.h',
	'include/X11/Xmu/WinUtil.h',
	'include/X11/Xmu/Xct.h',
	'include/X11/Xmu/WhitePoint.h',
)

install_headers(hdr,
  subdir : 'X11/Xmu',
)

src_muu = files(
  'src/ClientWin.c',
  'src/CursorName.c',
  'src/DefErrMsg.c',
  'src/GetHost.c',
  'src/Lower.c',
)

src_mu = src_muu + files(
  'src/Xmuint.h',
	'src/AllCmap.c',
	'src/Atoms.c',
	'src/Clip.c',
	'src/CloseHook.c',
	'src/CmapAlloc.c',
	'src/CrCmap.c',
	'src/CrPixFBit.c',
	'src/CvtCache.c',
	'src/CvtStdSel.c',
	'src/DelCmap.c',
	'src/DisplayQue.c',
	'src/Distinct.c',
	'src/DrawLogo.c',
	'src/DrRndRect.c',
	'src/EditresCom.c',
	'src/ExtAgent.c',
	'src/FToCback.c',
	'src/GrayPixmap.c',
	'src/Initer.c',
	'src/LocBitmap.c',
	'src/Lookup.c',
	'src/LookupCmap.c',
	'src/RdBitF.c',
	'src/ScrOfWin.c',
	'src/ShapeWidg.c',
	'src/StdCmap.c',
	'src/StrToBS.c',
	'src/StrToBmap.c',
	'src/StrToCurs.c',
	'src/StrToGrav.c',
	'src/StrToJust.c',
	'src/StrToLong.c',
	'src/StrToOrnt.c',
	'src/StrToShap.c',
	'src/StrToWidg.c',
	'src/UpdMapHint.c',
	'src/VisCmap.c',
	'src/WidgetNode.c',
	'src/Xct.c',
)

lib_muu = library('Xmuu', src_muu,
  c_args : lib_args,
  include_directories : inc_xmu,
  dependencies : dep_ext_xmu,
  version : '1.0.0',
  install : true,
)

libxmuu = declare_dependency(
  link_with : lib_muu,
  include_directories : inc_xmu,
)

lib_mu = library('Xmu', src_mu,
  c_args : lib_args,
  include_directories : inc_xmu,
  dependencies : dep_ext_xmu,
  version : '6.2.0',
  install : true,
)

libxmu = declare_dependency(
  link_with : lib_mu,
  include_directories : inc_xmu,
)

pkg.generate(name : 'Xmuu',
  description : 'Mini Xmu Library.',
  filebase : 'xmuu',
  requires : ['xproto', 'x11'],
  requires_private: 'x11',
  version : ver_xmu,
)

pkg.generate(name : 'Xmu',
  description : 'Xmu Library.',
  filebase : 'xmu',
  requires : ['xproto', 'x11', 'xt'],
  requires_private: ['x11', 'xt', 'xext'],
  version : ver_xmu,
)

# TODO: implement
# subdir('test')