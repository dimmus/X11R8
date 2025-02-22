ver_vboxvideo = '1.0.1'

f_check += ['strlcat', 'strlcpy', 'timingsafe_memcmp']
conf.set('HAVE_ISA', false)

lib_args = [
    '-Wno-declaration-after-statement',
    '-Wno-unused-but-set-variable',
    '-Wno-unused-value',
]

moduledir = dir_lib / 'xorg' / 'modules'

lib_args += [
    '-DHAVE_ISA',
    '-DDRIVER_NAME=vboxvideo'
]

src = files(
    'edid.c',
    'getmode.c',
    'HGSMIBase.c',
    'HGSMIBuffers.c',
    'HGSMICommon.c',
    'hgsmimemalloc.c',
    'Modesetting.c',
    'pointer.c',
    'setmode.c',
    'vboxvideo.c',
    'VBVABase.c',
    'vbva.c',
)

shared_module('vboxvideo_drv',
    src,
    c_args: lib_args,
	name_prefix: '',
	include_directories: [include_directories('.'), inc_config, inc_server],
	dependencies: xproto,
	install: true,
	install_dir: dir_xorg_module,
)