srcs_xorg_int10 = [
    'vbe.c',
    'vbeModes.c',
    'helper_exec.c',
    'helper_mem.c',
    'xf86int10.c',
    'xf86int10module.c',
]

int10_c_args = [XFREE86_CFLAGS]
int10_link = []

if host_machine.cpu() == 'i386' or host_machine.cpu() == 'x86_64'
    int10_c_args += '-D_PC'
endif

if int10 == 'stub'
    srcs_xorg_int10 += 'stub.c'
    int10_c_args += '-D_VM86_LINUX'
endif

if int10 == 'x86emu'
    srcs_xorg_int10 += [
        'generic.c',
        'xf86x86emu.c',
        'x86emu.c',
    ]
    int10_c_args += '-D_X86EMU'
    int10_c_args += '-DNO_SYS_HEADERS'

    # Silence some useless warnings from x86emu
    if cc.has_argument('-Wno-format-nonliteral')
        int10_c_args += '-Wno-format-nonliteral'
    endif

    int10_link += xorg_x86emu
endif

if int10 == 'vm86'
    srcs_xorg_int10 += [
        'vm86/linux_vm86.c',
        'linux.c',
    ]
    int10_c_args += '-D_VM86_LINUX'
endif

shared_module('int10',
    srcs_xorg_int10,
    include_directories: [
        inc_server,
        include_directories('../x86emu')
    ],
    dependencies: [dep_common, dep_pciaccess],
    link_with: int10_link,
    c_args: int10_c_args,
    install: true,
    install_dir: dir_xorg_module,
)

install_data('xf86int10.h', install_dir: dir_xorg)
install_data('vbe.h',       install_dir: dir_xorg)
install_data('vbeModes.h',  install_dir: dir_xorg)
