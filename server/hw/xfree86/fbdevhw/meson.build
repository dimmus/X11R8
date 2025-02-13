inc_server += include_directories('.')

if host_machine.system() == 'linux'
    srcs_fbdevhw = 'fbdevhw.c'
else
    srcs_fbdevhw = 'fbdevhwstub.c'
endif

lib = shared_library('fbdevhw',
    srcs_fbdevhw,
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_xorg_module,
    # link_with: exe_xorg,
    override_options: ['b_lundef=false'],
)

libfbdevhw = declare_dependency(
  link_with: lib,
  include_directories: inc_server,
)

install_data('fbdevhw.h', install_dir: dir_xorg)