ver_vmmouse = '13.2.0'

driver_version = ver_vmmouse.split('.')
conf.set('VMMOUSE_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('VMMOUSE_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('VMMOUSE_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_XORG_SERVER_1_1_0', true)
conf.set('HAVE_XORG_SERVER_1_5_0', true)
conf.set('CALL_CONVERSION_PROC', true)
conf.set('ABS_VALUATOR_AXES', true)

# UDEVDIR   = dir_lib / 'udev' / 'rules.d'

f_check += ['ioperm', 'iopl']

lib_args = [
    # '-DHAVE_LIBUDEV', # defined already in config.h
    '-DVMMOUSE_OS_GENERIC',
    # '-DVMMOUSE_OS_SOLARIS',
    # '-DVMMOUSE_OS_BSD',
    # '-DUSE_DEV_IO', # freebsd
    # '-DUSE_X86_64_IOPL', # netbsd
    # '-DUSE_AMD64_IOPL', # openbsd
    '-DNO_MOUSE_MODULE', # Do not include built-in mouse module fallback
]

dep_int_vmmouse = [xproto, libx11, libxrandr, xserver, libxserver]
dep_ext_vmmouse = dep_udev

inc_vmmouse = [
    include_directories('.'),   
    inc_server,
    inc_lib, 
]

src = files(
    'vmmouse.c',
    'vmmouse_client.c',
    'vmmouse_proto.c',
)

shared_module('libvmmouse_drv',
    src,
	name_prefix: '',
	include_directories: inc_vmmouse,
	dependencies: [dep_int_vmmouse, dep_ext_vmmouse],
    c_args: lib_args,
	install: true,
	install_dir: dir_xorg_module / 'input',
)

# vmmouse = declare_dependency(
#     link_with: mod, include_directories: inc_config
# )

executable('vmmouse_detect',
    src + [
        'vmmouse_detect.c',
        'vmmouse_udev.c',
        'vmmouse_iopl.c',
    ],   
    include_directories: inc_vmmouse,
	dependencies: [dep_int_vmmouse, dep_ext_vmmouse],
    install: true,
)

install_data('50-vmmouse.conf', install_dir: dir_xorg_conf)

install_data('11-x11-vmmouse.fdi',
    install_dir: dir_sysconf / 'hal' / 'fdi' / 'policy' / '20thirdparty'
)

conf_vmmouse = configuration_data()
conf_vmmouse.set('__BIN_PREFIX__', dir_bin)
conf_vmmouse.set('__HAL_BIN_PREFIX__', dir_bin)

configure_file(
    input: 'hal-probe-vmmouse.in',
    output: 'hal-probe-vmmouse',
    configuration: conf_vmmouse,
    install: true,
    install_dir: dir_data,
)

configure_file(
    input: '69-xorg-vmmouse.rules.in',
    output: '69-xorg-vmmouse.rules',
    configuration: conf_vmmouse,
    install: true,
    install_dir: dir_data,
)