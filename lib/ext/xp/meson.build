src = files(
	'XpAttr.c',
	'XpContext.c',
	'XpDoc.c',
	'XpExtUtil.c',
	'XpExtVer.c',
	'XpGetData.c',
	'XpImageRes.c',
	'XpInput.c',
	'XpJob.c',
	'XpLocale.c',
	'XpNotifyPdm.c',
	'XpPage.c',
	'XpPageDim.c',
	'XpPrinter.c',
	'XpPutData.c',
	'XpScreens.c',
)

dep_int_xp = [xproto, libx11, libxext, libxau]

lib = library('Xp',
  src,
  include_directories: inc_lib,
  dependencies: dep_int_xp,
  version: '0.0.1',
  install: true,
)

libxp = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'The Xp Library',
  version: ver_xp,
  filebase: 'xp',
  requires: 'xproto',
  requires_private: 'x11'
)