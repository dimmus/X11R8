inc_server += include_directories('.')

if host_machine.system() == 'linux'
    srcs_fbdevhw = 'fbdevhw.c'
else
    srcs_fbdevhw = 'fbdevhwstub.c'
endif

mod_fbdevhw = shared_module('fbdevhw',
    srcs_fbdevhw,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_xorg_module,
    link_with: exe_xorg,
)

install_data('fbdevhw.h', install_dir: dir_xorg)