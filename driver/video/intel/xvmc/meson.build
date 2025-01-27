xvmc_sources = files(
  'intel_xvmc.c',
  'intel_xvmc_dump.c',
  'i915_xvmc.c',
  'i965_xvmc.c',
  'xvmc_vld.c',
  'intel_batchbuffer.c',
)

shared_library('IntelXvMC', xvmc_sources,
	soversion : '1',
	version : '1.0.0',
	dependencies : [dep_int_intel, dep_ext_intel],
	c_args : [
		'-DFALSE=0',
		'-DTRUE=1',
		'-Wno-unused-but-set-variable',
		'-Wno-unused-parameter',
		'-Wno-sign-compare',
		'-Wno-pointer-sign',
	],
	install : true
)
