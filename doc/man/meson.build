manpage_config = configuration_data()

# subdir('dmx') # TODO: man - dmx
subdir('drivers')
subdir('exa')
subdir('fbdevhw')

# TODO: man - proto

install_man(configure_file(
    input: 'vfb/Xvfb.man',
    output: 'Xvfb.1',
    configuration: manpage_config,
))

# TODO: man - x11

subdir('xau')

install_man(configure_file(
    input: 'xaw/Xaw.man',
    output: 'Xaw.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xephyr/Xephyr.man',
    output: 'Xephyr.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xephyr/Xephyr.man',
    output: 'Xephyr.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xnest/Xnest.man',
    output: 'Xnest.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xquartz/Xquartz.man',
    output: 'Xquartz.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xwayland/Xwayland.man',
    output: 'Xwayland.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xwin/XWin.man',
    output: 'XWin.1',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xwin/XWinrc.man',
    output: 'XWinrc.5',
    configuration: manpage_config,
))

install_man(configure_file(
    input: 'xwin/xwinclip.man',
    output: 'xwinclip.1',
    configuration: manpage_config,
))
