ver_xi = '1.8.2'

inc_xi = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('include/X11/extensions'),
]

dep_int_xi = [xproto, libx11, libxext, libxfixes]

src_xi2 = files(
  'src/XIAllowEvents.c',
  'src/XIGrabDevice.c',
  'src/XIQueryVersion.c',
  'src/XIQueryDevice.c',
  'src/XISetDevFocus.c',
  'src/XIGetDevFocus.c',
  'src/XIPassiveGrab.c',
  'src/XIProperties.c',
  'src/XISelEv.c',
  'src/XISetCPtr.c',
  'src/XIWarpPointer.c',
  'src/XIHierarchy.c',
  'src/XIDefineCursor.c',
  'src/XIQueryPointer.c',
  'src/XIBarrier.c',
)

src = files(
  'src/XAllowDv.c',
  'src/XChDProp.c',
  'src/XChgDCtl.c',
  'src/XChgFCtl.c',
  'src/XChgKbd.c',
  'src/XChgKMap.c',
  'src/XChgPnt.c',
  'src/XChgProp.c',
  'src/XCloseDev.c',
  'src/XDelDProp.c',
  'src/XDevBell.c',
  'src/XExtToWire.c',
  'src/XGetBMap.c',
  'src/XGetCPtr.c',
  'src/XGetDCtl.c',
  'src/XGetDProp.c',
  'src/XGetFCtl.c',
  'src/XGetKMap.c',
  'src/XGetMMap.c',
  'src/XGetProp.c',
  'src/XGetVers.c',
  'src/XGMotion.c',
  'src/XGrabDev.c',
  'src/XGrDvBut.c',
  'src/XGrDvKey.c',
  'src/XGtFocus.c',
  'src/XGtSelect.c',
  'src/XListDev.c',
  'src/XListDProp.c',
  'src/XOpenDev.c',
  'src/XQueryDv.c',
  'src/XSelect.c',
  'src/XSetBMap.c',
  'src/XSetDVal.c',
  'src/XSetMMap.c',
  'src/XSetMode.c',
  'src/XSndExEv.c',
  'src/XStFocus.c',
  'src/XUngrDev.c',
  'src/XUngrDvB.c',
  'src/XUngrDvK.c',
  'src/XExtInt.c',
  'src/XIint.h',
  # 'src/XFreeLst.c',
)

src += src_xi2

lib = library('Xi', src,
  include_directories : inc_xi,
  dependencies : dep_int_xi,
  version : '6.1.0',
  install : true,
)

libxi = declare_dependency(
  link_with : lib,
  include_directories : inc_xi,
)

meson.override_dependency('xi', libxi)

install_headers(
  [
    'include/X11/extensions/XInput.h',
    'include/X11/extensions/XInput2.h',
  ],
  subdir : 'X11/extensions',
)

pkg.generate(lib,
  description : 'X Input Extension Library',
  version: ver_xi,
  filebase : 'xinput',
  requires : 'xproto',
  requires_private: ['x11', 'xext', 'xfixes']
)

