ver_xt = '1.3.0'

lib_args = ['-DXKB', '-DXT_GEO_TATTLER']

f_check += ['reallocarray']
h_check += ['alloca.h']

dep_int_xt = [libsm, libice, libx11, xproto]

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
  include_directories: inc_lib,
  sources: stringdefs_h,
)

src = files(
  'ActionHook.c',
  'Alloc.c',
  'ArgList.c',
  'Callback.c',
  'ClickTime.c',
  'Composite.c',
  'Constraint.c',
  'Convert.c',
  'Converters.c',
  'Core.c',
  'Create.c',
  'Destroy.c',
  'Display.c',
  'Error.c',
  'Event.c',
  'EventUtil.c',
  'Functions.c',
  'GCManager.c',
  'Geometry.c',
  'GetActKey.c',
  'GetResList.c',
  'GetValues.c',
  'HookObj.c',
  'Hooks.c',
  'Initialize.c',
  'Intrinsic.c',
  'Keyboard.c',
  'Manage.c',
  'NextEvent.c',
  'Object.c',
  'PassivGrab.c',
  'Pointer.c',
  'Popup.c',
  'PopupCB.c',
  'RectObj.c',
  'ResConfig.c',
  'Resources.c',
  'Selection.c',
  'SetSens.c',
  'SetValues.c',
  'SetWMCW.c',
  'Shell.c',
  'TMaction.c',
  'TMgrab.c',
  'TMkey.c',
  'TMparse.c',
  'TMprint.c',
  'TMstate.c',
  'Threads.c',
  'VarCreate.c',
  'VarGet.c',
  'Varargs.c',
  'Vendor.c',
)

lib = library('Xt', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: [dep_int_xt, stringdefs],
  version: '6.0.0',
  install: true,
)

libxt = declare_dependency(
  link_with: lib,
  include_directories: inc_lib
)

pkg.generate(lib,
  description: 'X Toolkit Library.',
  filebase: 'xt',
  requires: ['xproto', 'x11'],
  requires_private: ['ice', 'sm'],
  version: ver_xt,
)