manpage_config = configuration_data()
manpage_config.set('vendorversion', '"xorg-server @0@" "X Version 11"'.format(ver_xserver))
manpage_config.set('xorgversion', '"xorg-server @0@" "X Version 11"'.format(ver_xserver))
manpage_config.set('xservername', 'Xorg')
manpage_config.set('xconfigfile', 'xorg.conf')
manpage_config.set('projectroot', dir_prefix)
manpage_config.set('apploaddir', '$(appdefaultdir)')
manpage_config.set('appmansuffix', '1')
manpage_config.set('drivermansuffix', '4')
manpage_config.set('adminmansuffix', '8')
manpage_config.set('libmansuffix', '3')
manpage_config.set('miscmansuffix', '7')
manpage_config.set('filemansuffix', '5')
manpage_config.set('logdir', log_dir)
manpage_config.set('datadir', dir_data)
manpage_config.set('mandir', dir_man)
manpage_config.set('sysconfdir', dir_sysconf)
manpage_config.set('xconfigdir', 'xorg.conf.d')
manpage_config.set('xkbdir', xkb_dir)
manpage_config.set('XKB_DFLT_RULES', get_option('xkb_default_rules'))
manpage_config.set('XKB_DFLT_MODEL', get_option('xkb_default_model'))
manpage_config.set('XKB_DFLT_LAYOUT', get_option('xkb_default_layout'))
manpage_config.set('XKB_DFLT_VARIANT', get_option('xkb_default_variant'))
manpage_config.set('XKB_DFLT_OPTIONS', get_option('xkb_default_options'))
manpage_config.set('bundle_id_prefix', '...')
manpage_config.set('modulepath', module_dir)
manpage_config.set('suid_wrapper_dir', dir_libexec)
manpage_config.set('default_font_path', default_font_path)

install_man(configure_file(
    input: 'Xserver.man',
    output: 'Xserver.1',
    configuration: manpage_config,
))

if WITH_DOC_MAN
    docxmlconfig = configuration_data()
    docxmlconfig.set('PACKAGE_VERSION', ver_xserver)
    docxmlconfig.set('RELEASE_DATE', '2021-07-05')
    configure_file(
        input: 'xserver.ent.in',
        output: 'xserver.ent',
        configuration: docxmlconfig
    )
endif