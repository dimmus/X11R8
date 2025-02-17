with_dri2 = get_option('dri2')
if with_dri2
  if dep_dri.found()
    dridriverdir = dep_dri.get_variable('dridriverdir')
  else
    dridriverdir = dir_lib / 'dri'
  endif

  conf_intel.set('HAVE_DRI2', 1)
  conf_intel.set_quoted('DRI_DRIVER_PATH', dridriverdir)
endif

with_dri3 = get_option('dri3')
if with_dri3
  has_dri3 = (cc.has_header_symbol('xorg-server.h', 'DRI3') and
	            cc.has_header('misyncstr.h') and
	            cc.has_header('misyncshm.h'))
  conf_intel.set('HAVE_DRI3', 1)
endif

default_dri = get_option('default-dri')
conf_intel.set('DEFAULT_DRI_LEVEL', default_dri)

conf_intel.set('HAVE_PRESENT', 1)

if get_option('backlight')
  conf_intel.set('USE_BACKLIGHT', 1)
endif
with_backlight_helper = get_option('backlight-helper')
if with_backlight_helper
  conf_intel.set('USE_BACKLIGHT_HELPER', 1)
endif

debug = get_option('internal-debug')
if debug == 'sync'
  conf_intel.set('DEBUG_SYNC', 1)
endif
if debug == 'memory' or debug == 'full'
  conf_intel.set('DEBUG_MEMORY', 1)
endif
if debug == 'pixmap' or debug == 'full'
  conf_intel.set('DEBUG_PIXMAP', 1)
endif
if debug == 'full'
  conf_intel.set('HAS_DEBUG_FULL', 1)
endif

intel_drv_sources = [
  'backlight.c',
  'fd.c',
  'intel_device.c',
  'intel_options.c',
  'intel_module.c',
]

intel_drv_libs = []

default_accel = get_option('default-accel')

with_sna = get_option('sna')
if with_sna
  subdir('sna')
  intel_drv_libs += sna
elif default_accel == 'sna'
  error('SNA not available, so can\'t selected as the default acceleration method')
endif

with_uxa = get_option('uxa')
if with_uxa
  subdir('uxa')
  intel_drv_libs += uxa
elif default_accel == 'uxa'
  error('UXA not available, so can\'t selected as the default acceleration method')
endif

if default_accel == 'sna'
  conf_intel.set('DEFAULT_ACCEL_METHOD', 'SNA')
elif default_accel == 'uxa'
  conf_intel.set('DEFAULT_ACCEL_METHOD', 'UXA')
else
  conf_intel.set('DEFAULT_ACCEL_METHOD', 'NOACCEL')
endif

if with_valgrind
  dep_intel_drv += valgrind
endif

moduledir = dir_xorg_module

shared_module('intel_drv',
  sources : intel_drv_sources,
  dependencies : dep_intel_drv,
  include_directories: inc_intel,
  link_with : intel_drv_libs,
  c_args : [
    '-DMAJOR_IN_SYSMACROS',
    '-Wno-unused-parameter',
    '-Wno-sign-compare',
  ],
  name_prefix : '',
  install_dir : dir_xorg_module / 'drivers',
  install : true
)
