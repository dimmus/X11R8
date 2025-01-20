src = files(
    'imCallbk.c',
    'imDefFlt.c',
    'imDefIc.c',
    'imDefIm.c',
    'imDefLkup.c',
    'imDispch.c',
    'imEvToWire.c',
    'imExten.c',
    'imImSw.c',
    'imInsClbk.c',
    'imInt.c',
    'imLcFlt.c',
    'imLcGIc.c',
    'imLcIc.c',
    'imLcIm.c',
    'imLcLkup.c',
    'imLcPrs.c',
    'imLcSIc.c',
    'imRmAttr.c',
    'imRm.c',
    'imThaiFlt.c',
    'imThaiIc.c',
    'imThaiIm.c',
    'imTrans.c',
    'imTransR.c',
    'imTrX.c',
)

lib_args += ['-DXIM_t', '-DTRANS_CLIENT']

lib = static_library('ximcp', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_x11,
  # link_with: lib_x11,
  # version: '2.0.0',
  install: true,
)

libximcp = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)