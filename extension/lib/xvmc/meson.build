lib_args = [
  '-DXVMC_CONFIGDIR=@0@/X11'.format(get_option('sysconfdir')),
  '-DXVMC_SOVERSION=".1.0"',
  '-DXV_SOVERSION=".1.0"',
]

if cc.has_function('shmat')
  conf.set('HAVE_SHMAT', true)
endif

dep_ext_xvmc = [dep_dl]
dep_int_xvmc = [xproto, libx11, libxv, libxext]

xvmc = library('XvMC',
  'XvMC.c',
  include_directories: inc_ext,
  dependencies: [dep_ext_xvmc, dep_int_xvmc],
  version: '1.0.0',
  darwin_versions : ['2.0.0', '2.0.0'],
  install: true,
)

libxvmc = declare_dependency(
  link_with: xvmc,
  include_directories: inc_ext,
)

xvmcw = library('XvMCW',
  'XvMCWrapper.c',
  c_args: lib_args,
  include_directories: inc_ext,
  dependencies: [dep_ext_xvmc, dep_int_xvmc],
  version: '1.0.0',
  darwin_versions : ['2.0.0', '2.0.0'],
  install: true,
)

libxvmcw = declare_dependency(
  link_with: xvmcw,
  include_directories: inc_ext,
)

meson.override_dependency('xvmc', libxvmc)
meson.override_dependency('xvmc-wrapper', libxvmcw)

pkg.generate(xvmc,
  filebase: 'xvmc',
  description: 'The XvMC Library',
  version: ver_xvmc,
  requires: 'xproto',
  requires_private: ['x11', 'xext', 'xv']
)

pkg.generate(xvmcw,
  name: 'XvMCWrapper',
  filebase: 'xvmc-wrapper',
  description: 'XvMC wrapper library',
  version: ver_xvmc,
  requires: 'xproto',
  requires_private: ['x11', 'xext', 'xv']
)