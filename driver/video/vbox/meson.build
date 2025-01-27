ver_vboxvideo = '1.0.1'

f_check += ['strlcat', 'strlcpy', 'timingsafe_memcmp']

c_args = [
    '-Wno-declaration-after-statement',
    '-Wno-unused-but-set-variable',
    '-Wno-unused-value',
]

moduledir = dir_lib / 'xorg' / 'modules'

c_args += [
    '-DHAVE_ISA',
    '-DDRIVER_NAME=vboxvideo'
]

src = files(
    'src/edid.c',
    'src/getmode.c',
    'src/HGSMIBase.c',
    'src/HGSMIBuffers.c',
    'src/HGSMICommon.c',
    'src/hgsmimemalloc.c',
    'src/Modesetting.c',
    'src/pointer.c',
    'src/setmode.c',
    'src/vboxvideo.c',
    'src/VBVABase.c',
    'src/vbva.c',
)

shared_module('vboxvideo_drv', src,
    c_args: c_args,
	name_prefix: '',
	include_directories: [include_directories('src'), inc_config, inc_server],
	dependencies: [xproto, xserver],
	install: true,
	install_dir: dir_xorg_module,
)