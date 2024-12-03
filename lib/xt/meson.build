ver_xt = '1.3.0'

inc_xt = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
]

lib_args = ['-DXKB', '-DXT_GEO_TATTLER']

f_check += ['reallocarray']
h_check += ['alloca.h']

dep_int_xt = [libsm, libice, libx11, xproto]

hdr = files(
  'include/X11/Composite.h',
  'include/X11/CompositeP.h',
  'include/X11/ConstrainP.h',
  'include/X11/Constraint.h',
  'include/X11/Core.h',
  'include/X11/CoreP.h',
  'include/X11/Intrinsic.h',
  'include/X11/IntrinsicP.h',
  'include/X11/Object.h',
  'include/X11/ObjectP.h',
  'include/X11/RectObj.h',
  'include/X11/RectObjP.h',
  'include/X11/ResConfigP.h',
  'include/X11/ShellP.h',
  'include/X11/Vendor.h',
  'include/X11/VendorP.h',
  'include/X11/CallbackI.h',
  'include/X11/ConvertI.h',
  'include/X11/CreateI.h',
  'include/X11/EventI.h',
  'include/X11/HookObjI.h',
  'include/X11/InitialI.h',
  'include/X11/IntrinsicI.h',
  'include/X11/PassivGraI.h',
  'include/X11/ResourceI.h',
  'include/X11/SelectionI.h',
  'include/X11/ShellI.h',
  'include/X11/ThreadsI.h',
  'include/X11/TranslateI.h',
  'include/X11/VarargsI.h',
  'include/X11/Xtos.h',
)

install_headers(hdr,
  subdir : 'X11',
)

# Generate StringDefs.h
# Example
# $ ./makestrs -i /home/dimmus/dev/c/xorg/src/lib/xt < /home/dimmus/dev/c/xorg/src/lib/xt/util/string.list > StringDefs.c
subdir('util')
stringdefs_h = custom_target('makestrs',
  command: [makestrs_exe, '-i', meson.current_source_dir()],
  # build_by_default: true,
  feed: true,
  capture: true,
  input: meson.current_source_dir() / 'util'/ 'string.list',
  output: 'StringDefs.c'
)

stringdefs = declare_dependency(
  include_directories: inc_xt,
  sources : stringdefs_h,
)

src = files(
  'src/ActionHook.c',
  'src/Alloc.c',
  'src/ArgList.c',
  'src/Callback.c',
  'src/ClickTime.c',
  'src/Composite.c',
  'src/Constraint.c',
  'src/Convert.c',
  'src/Converters.c',
  'src/Core.c',
  'src/Create.c',
  'src/Destroy.c',
  'src/Display.c',
  'src/Error.c',
  'src/Event.c',
  'src/EventUtil.c',
  'src/Functions.c',
  'src/GCManager.c',
  'src/Geometry.c',
  'src/GetActKey.c',
  'src/GetResList.c',
  'src/GetValues.c',
  'src/HookObj.c',
  'src/Hooks.c',
  'src/Initialize.c',
  'src/Intrinsic.c',
  'src/Keyboard.c',
  'src/Manage.c',
  'src/NextEvent.c',
  'src/Object.c',
  'src/PassivGrab.c',
  'src/Pointer.c',
  'src/Popup.c',
  'src/PopupCB.c',
  'src/RectObj.c',
  'src/ResConfig.c',
  'src/Resources.c',
  'src/Selection.c',
  'src/SetSens.c',
  'src/SetValues.c',
  'src/SetWMCW.c',
  'src/Shell.c',
  'src/TMaction.c',
  'src/TMgrab.c',
  'src/TMkey.c',
  'src/TMparse.c',
  'src/TMprint.c',
  'src/TMstate.c',
  'src/Threads.c',
  'src/VarCreate.c',
  'src/VarGet.c',
  'src/Varargs.c',
  'src/Vendor.c',
)

lib = library('Xt', src,
  c_args : lib_args,
  include_directories : inc_xt,
  dependencies : [dep_int_xt, stringdefs],
  version : '6.0.0',
  install : true,
)

libxt = declare_dependency(
  link_with : lib,
  include_directories : inc_xt
)

pkg.generate(lib,
  description : 'X Toolkit Library.',
  filebase : 'xt',
  requires : ['xproto', 'x11'],
  requires_private: ['ice', 'sm'],
  version : ver_xt,
)

# implement
# subdir('test')