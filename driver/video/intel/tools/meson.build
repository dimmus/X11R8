if with_tools
  executable('intel-virtual-output',
	     sources : 'virtual.c',
	     dependencies : [
	       libx11,
	       libxext,
	       libxfixes,
	       libxrender,
	       libxdamage,
	       libxrandr,
	       libxrender,
	       libxcursor,
	       libxscrnsaver,
	       libxinerama,
	       libxtst,
	       dep_pixman,
	     ],
	     c_args : [
	       '-Wno-unused-parameter',
	     ],
	     install : true)

  configure_file(input : 'intel-virtual-output.man',
		 output : 'intel-virtual-output.4',
		 command : [
		 'sed',
		 '-e',
		 's/__appmansuffix__/@0@/g'.format(man_config.get('appmansuffix')),
		 '-e',
		 's/__filemansuffix__/@0@/g'.format(man_config.get('filemansuffix')),
		 '-e',
		 's/__drivermansuffix__/@0@/g'.format(man_config.get('drivermansuffix')),
		 '-e',
		 's/__miscmansuffix__/@0@/g'.format(man_config.get('miscmansuffix')),
		 '-e',
		 's/__xservername__/@0@/g'.format(man_config.get('xservername')),
		 '-e',
		 's/__xconfigfile__/@0@/g'.format(man_config.get('xconfigfile')),
		 '-e',
		 's/__vendorversion__/@0@/g'.format(man_config.get('vendorversion')),
		 '@INPUT@'
	       ],
	       capture : true,
	       install_dir: dir_man / 'man4',
	       install : true)

  executable('cursor',
	     sources : 'cursor.c',
	     dependencies : [
	       libx11,
	       libxfixes,
	       dependency('libpng', required : true),
	     ],
	     c_args : [
	       '-Wno-unused-parameter',
	     ],
	     install : false)
endif

if with_tools and with_dri3
  executable('dri3info',
	     sources : 'dri3info.c',
	     dependencies : [
	       libx11-xcb,
	       dependency('xcb-dri3', required : true),
	       libx11,
	       libxrandr,
	       libxxf86vm,
	       xproto,
	       dependency('dri', required : true),
	       dependency('libdrm', required : true),
	     ],
	     install : false)
endif

if with_backlight_helper
  executable('xf86-video-intel-backlight-helper',
	     sources : 'backlight_helper.c',
	     install_dir : dir_libexec,
	     install_mode : [ 'rws--x--x', 'root', 'root' ],
	     c_args : [
	       '-DMAJOR_IN_SYSMACROS',
	     ],
	     install : true)

  polkit_config = configuration_data()
  polkit_config.set('LIBEXEC_PATH', dir_libexec)

  configure_file(input : 'org.x.xf86-video-intel.backlight-helper.policy.in',
		 output : 'org.x.xf86-video-intel.backlight-helper.policy',
		 configuration : polkit_config,
		 install_dir : join_paths(dir_data, 'polkit-1/actions'),
		 install : true)
endif
