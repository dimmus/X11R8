ver_vmware = '13.4.0'
driver_version = ver_vmware.split('.')

f_check += ['strlcat', 'strlcpy', 'timingsafe_memcmp']

conf.set('VMWARE_PACKAGE_VERSION_MAJOR', driver_version[0])
conf.set('VMWARE_PACKAGE_VERSION_MINOR', driver_version[1])
conf.set('VMWARE_PACKAGE_VERSION_PATCHLEVEL', driver_version[2])
conf.set('HAVE_XORG_SERVER_1_1_0', true)
conf.set('HAVE_XORG_SERVER_1_2_0', true)
conf.set('HAVE_XORG_SERVER_1_5_0', true)
conf.set('HAVE_XORG_SERVER_1_7_0', true)
conf.set('HAVE_XORG_SERVER_1_12_0', true)
conf.set('HAVE_LIBDRM_2_4_74', true)
conf.set('HAVE_LIBDRM_2_4_96', true)
conf.set('BUILD_VMWGFX', true)
conf.set('HAVE_LIBUDEV', true)
# conf.set('HAVE_XA_2', true) # mesa

dep_int_vmware = [xproto, libx11, libxext, xserver, libxserver, libvgahw]
dep_ext_vmware = [dep_drm, dep_udev, dep_xa]

inc_vmware = [
	inc_lib,
	inc_server, # <dix-config.h>
	include_directories(
		'saa',
		'src',
		'vmwarectrl',
		'vmwgfx'
	)
]

subdir('saa')

src = files(
    'src/bits2pixels.c',
    'src/vmware.c',
    'src/vmwarecurs.c',
    'src/vmwarectrl.c',
    'src/vmwarexinerama.c',
    'src/vmwarevideo.c',
    'src/vmwaremodes.c',
    'src/vmware_bootstrap.c',
    'src/vmware_common.c',
)

subdir('vmwgfx')

shared_module('vmware_drv',
	src + src_vmwgfx,
	name_prefix: '',
	include_directories: inc_vmware,
	dependencies: [dep_int_vmware, dep_ext_vmware],
	link_with: libsaa,
	install: true,
	install_dir: dir_xorg_module / 'drivers',
)

subdir('vmwarectrl')