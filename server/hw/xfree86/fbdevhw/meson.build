inc_server += include_directories('.')

if host_machine.system() == 'linux'
    srcs_fbdevhw = 'fbdevhw.c'
else
    srcs_fbdevhw = 'fbdevhwstub.c'
endif

shared_module('fbdevhw',
    srcs_fbdevhw,
    include_directories: [ inc_server, inc_server ],
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: module_dir,
    link_with: e,
)

install_data('fbdevhw.h', install_dir: dir_xorg)