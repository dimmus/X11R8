src = files(
  'XKB.c',
  'XKBBind.c',
  'XKBCompat.c',
  'XKBCtrls.c',
  'XKBCvt.c',
  'XKBGetMap.c',
  'XKBGetByName.c',
  'XKBNames.c',
  'XKBRdBuf.c',
  'XKBSetMap.c',
  'XKBUse.c',
  'XKBleds.c',
  'XKBBell.c',
  'XKBGeom.c',
  'XKBSetGeom.c',
  'XKBExtDev.c',
  'XKBList.c',
  'XKBMisc.c',
  'XKBMAlloc.c',
  'XKBGAlloc.c',
  'XKBAlloc.c',
  'XKBlibint.h',
)

lib = static_library('xkb', src,
  c_args: lib_args,
  include_directories: inc_x11,
  dependencies: dep_ext_x11,
  install: true,
)

libxkb = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)