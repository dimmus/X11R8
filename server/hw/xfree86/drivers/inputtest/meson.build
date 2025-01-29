inputtestdrv_srcs = [
    'xf86-input-inputtest.c',
]

shared_module(
    'inputtest_drv',
    inputtestdrv_srcs,
    name_prefix: '',
    include_directories: inc_server,
    c_args: xorg_c_args,
    dependencies: dep_common,
    install: true,
    install_dir: module_dir / 'input',
    link_with: exe_xorg,
)

install_data('xf86-input-inputtest-protocol.h', install_dir: dir_xorg)
