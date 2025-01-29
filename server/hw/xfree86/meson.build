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

xorg_c_args = ['-DHAVE_XORG_CONFIG_H', '-DXORG_NO_SDKSYMS']

# subdirs for convenience libraries statically linked into Xorg
subdir('common')
subdir('ddc')
if build_dri2
    subdir('dri2')
endif
subdir('i2c')
subdir('loader')
subdir('modes')
subdir('os-support')
subdir('parser')
subdir('ramdac')
subdir('xkb')

srcs_xorg = [
    '../../mi/miinitext.c',
    '../../mi/miinitext.h',
]

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
if build_dri2
    xorg_link += xorg_dri2
endif

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
]

exe_xorg = executable('Xorg',
    srcs_xorg,
    include_directories: inc_server,
    dependencies: dep_xorg,
    link_whole: xorg_link,
    link_args: linker_export_flags,
    c_args: xorg_c_args,
    install: true,
    install_dir: dir_bin,
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
subdir('vgahw')
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

executable('gtf',
    'utils/gtf/gtf.c',
    include_directories: inc_server,
    dependencies: dep_xorg,
    c_args: xorg_c_args,
    install: true,
)

# For symbol presence testing only
xorgserver_lib = shared_library('xorgserver',
    srcs_xorg,
    include_directories: inc_server,
    link_whole: xorg_link,
    dependencies: dep_xorg,
    link_args: linker_export_flags,
    c_args: xorg_c_args,
    install: false,
)

dep_xorgserver = declare_dependency(link_with: xorgserver_lib)