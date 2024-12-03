install_man(configure_file(
    input: 'Xorg.man',
    output: 'Xorg.1',
    configuration: manpage_config,
))

if get_option('suid_wrapper')
    install_man(configure_file(
        input: 'Xorg.wrap.man',
        output: 'Xorg.wrap.1',
        configuration: manpage_config,
    ))

    install_man(configure_file(
        input: 'Xwrapper.config.man',
        output: 'Xwrapper.config.5',
        configuration: manpage_config,
    ))
endif

install_man(configure_file(
    input: 'xorg.conf.man',
    output: 'xorg.conf.5',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xorg.conf.d.man',
    output: 'xorg.conf.d.5',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'utils/gtf.man',
    output: 'gtf.1',
    configuration: manpage_config,
))