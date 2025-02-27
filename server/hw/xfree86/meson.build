inc_server += include_directories(
    'common',
    'ddc',
    'dri2',
    'i2c',
    'int10',
    'loader',
    'modes',
    'os-support',
    'os-support/bus',
    'parser',
    'ramdac',
    'vgahw',
)

XFREE86_CFLAGS = [
    XSERVER_CFLAGS,
    '-DXORG_NO_SDKSYMS'
]

# subdirs for convenience libraries statically linked into Xorg
subdir('common')
subdir('ddc')
subdir('dri')
subdir('dri2')
subdir('i2c')
subdir('loader')
subdir('modes')
subdir('os-support')
subdir('parser')
subdir('ramdac')
subdir('xkb')

srcs_xorg = files(
    '../../mi/miinitext.c',
    '../../mi/miinitext.h',
)

# Extract all the objects so that all symbols get brought into the
# server.  This prevents us from needing a global table of all symbols
# that should be exported to Xorg modules, at the expense of all
# symbols being included and public

xorg_link = [
    libxserver,
    libglxvnd,
    xorg_common,
    xorg_loader,
    xorg_ddc,
    xorg_dri,
    xorg_dri2,
    xorg_xkb,
    xorg_i2c,
    xorg_modes,
    xorg_os_support,
    xorg_parser,
    xorg_ramdac,
    libxserver_fb,
    libxserver_xext_vidmode,
    libxserver_main,
    libxserver_config,
]

if host_machine.system() == 'cygwin'
    linker_export_flags = '-Wl,--export-all-symbols'
elif host_machine.system() == 'sunos' or host_machine.system() == 'darwin'
    linker_export_flags = []
else
    linker_export_flags = '-Wl,--export-dynamic'
endif

dep_xorg = [
    dep_pixman,
    dep_m,
    dep_dl,
    dep_pciaccess,
    dep_sha1,
    dep_config,
    dep_drm,
    libxshmfence,
    libxau,
    libxcomposite,
    libxrandr,
    libxrender,
    libxfixes,
    libxdmcp,
    libxfont,
    libxcvt,
]

if get_option('suid_wrapper')
    xorg_install_dir = get_option('libexecdir')
else
    xorg_install_dir = get_option('bindir')
endif

exe_xorg = executable(
    'Xorg',
    srcs_xorg,
    include_directories: inc_server,
    dependencies: dep_xorg,
    link_whole: xorg_link,
    link_args: linker_export_flags,
    c_args: XFREE86_CFLAGS,
    install: true,
    install_dir: xorg_install_dir,
    implib: true,
)

# subdirs for modules loadable by Xorg
subdir('dixmods')
subdir('exa')
subdir('fbdevhw')
if dep_gbm.found()
    subdir('glamor_egl')
endif
if int10 != 'false'
    if int10 == 'x86emu'
        subdir('x86emu')
    endif
    subdir('int10')
endif
subdir('shadowfb')
if build_vgahw
    subdir('vgahw')
endif
if build_modesetting
   subdir('drivers/modesetting')
endif
if get_option('xf86-input-inputtest')
    subdir('drivers/inputtest')
endif

meson.add_install_script(
    'sh', '-c',
    'ln -fs Xorg @0@@1@'.format(
        '${DESTDIR}',
        dir_bin / 'X'
    )
)

if get_option('suid_wrapper')
    executable('Xorg.wrap',
        'xorg-wrapper.c',
        include_directories: inc_server,
        dependencies: dep_xorg,
        c_args: XFREE86_CFLAGS,
        link_args: XSERVER_LDFLAGS,
        install: true,
        install_dir: dir_libexec,
        install_mode: ['r-sr-xr-x', 0, 0],
    )

    # meson gets confused when there are two targets of the same name
    # within the same directory, so we use a different intermediate name.
    xorg_sh = configure_file(
        input: 'Xorg.sh.in',
        output: 'Xorg.sh',
        configuration: conf_server,
    )

    install_data(
        xorg_sh,
        install_mode: 'rwxr-xr-x',
        install_dir: dir_bin,
        rename: 'Xorg',
    )
endif

executable('gtf',
    'utils/gtf/gtf.c',
    include_directories: inc_server,
    dependencies: dep_xorg,
    c_args: XFREE86_CFLAGS,
    link_args: XSERVER_LDFLAGS,
    install: true,
)

lib = shared_library('xorgserver',
    srcs_xorg,
    include_directories: inc_server,
    link_whole: xorg_link,
    dependencies: dep_xorg,
    link_args: [linker_export_flags, XSERVER_LDFLAGS],
    c_args: XFREE86_CFLAGS,
    install: false,
)

libxorg = declare_dependency(link_with: lib)
