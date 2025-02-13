inc_server += include_directories('.')

lib = shared_library('vgahw',
    [ 'vgaHW.c', 'vgaHWmodule.c'],
    include_directories: inc_server,
    dependencies: dep_common,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_xorg_module,
    override_options: ['b_lundef=false'],
)

libvgahw = declare_dependency(
  link_with: lib,
  include_directories: inc_server,
)

install_data('vgaHW.h', install_dir: dir_xorg)
