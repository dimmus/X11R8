ver_xi = '1.8.2'

dep_int_xi = [xproto, libx11, libxext, libxfixes]

src_xi2 = files(
  'XIAllowEvents.c',
  'XIGrabDevice.c',
  'XIQueryVersion.c',
  'XIQueryDevice.c',
  'XISetDevFocus.c',
  'XIGetDevFocus.c',
  'XIPassiveGrab.c',
  'XIProperties.c',
  'XISelEv.c',
  'XISetCPtr.c',
  'XIWarpPointer.c',
  'XIHierarchy.c',
  'XIDefineCursor.c',
  'XIQueryPointer.c',
  'XIBarrier.c',
)

src = files(
  'XAllowDv.c',
  'XChDProp.c',
  'XChgDCtl.c',
  'XChgFCtl.c',
  'XChgKbd.c',
  'XChgKMap.c',
  'XChgPnt.c',
  'XChgProp.c',
  'XCloseDev.c',
  'XDelDProp.c',
  'XDevBell.c',
  'XExtToWire.c',
  'XGetBMap.c',
  'XGetCPtr.c',
  'XGetDCtl.c',
  'XGetDProp.c',
  'XGetFCtl.c',
  'XGetKMap.c',
  'XGetMMap.c',
  'XGetProp.c',
  'XGetVers.c',
  'XGMotion.c',
  'XGrabDev.c',
  'XGrDvBut.c',
  'XGrDvKey.c',
  'XGtFocus.c',
  'XGtSelect.c',
  'XListDev.c',
  'XListDProp.c',
  'XOpenDev.c',
  'XQueryDv.c',
  'XSelect.c',
  'XSetBMap.c',
  'XSetDVal.c',
  'XSetMMap.c',
  'XSetMode.c',
  'XSndExEv.c',
  'XStFocus.c',
  'XUngrDev.c',
  'XUngrDvB.c',
  'XUngrDvK.c',
  'XExtInt.c',
  # 'XFreeLst.c',
)

src += src_xi2

lib = library('Xi', src,
  include_directories: inc_ext,
  dependencies: dep_int_xi,
  version: '6.1.0',
  install: true,
)

libxi = declare_dependency(
  link_with: lib,
  include_directories: inc_ext,
)

meson.override_dependency('xi', libxi)

pkg.generate(lib,
  description: 'X Input Extension Library',
  version: ver_xi,
  filebase: 'xinput',
  requires: 'xproto',
  requires_private: ['x11', 'xext', 'xfixes']
)

