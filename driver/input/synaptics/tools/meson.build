conf.set_quoted('SYNAPTICS_VERSION', ver_synaptics)

executable('synclient',
    sources : 'synclient.c',
    include_directories: include_directories('../include'),
    dependencies : [xproto, libx11, xserver, dep_evdev, libxi, libxtst],
    install : true
)

executable('syndaemon',
    sources : 'syndaemon.c',
    include_directories: include_directories('../include'),
    dependencies : [xproto, libx11, xserver, dep_evdev, libxi, libxtst],
    install : true
)