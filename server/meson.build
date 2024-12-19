libselinux_req  = '>= 2.0.86'
xext_req        = '>= 1.0.99.4'
xproto_req      = '>= 7.0.31'
wl_req          = '>= 1.21.0'
wl_proto_req    = '>= 1.34'
gbm_req         = '>= 10.2'
xshmfence_req   = '>= 1.1'

build_systemd = get_option('systemd_notify') == 'true'
# libsystemd-daemon was moved into libsystemd in version 209
dep_libsystemd_daemon = dependency('libsystemd', version: '>= 209', required: false)
if not dep_libsystemd_daemon.found()
    dep_libsystemd_daemon = dependency('libsystemd-daemon', required: false)
endif

build_hashtable = false

# Resolve default values of some options
xkb_dir = get_option('xkb_dir')
if xkb_dir == ''
    if dep_xkbcomp.found() and dep_xkbcomp.type_name() == 'pkgconfig'
        xkb_dir = dep_xkbcomp.get_variable(pkgconfig: 'xkbconfigdir')
    endif
    if xkb_dir == ''
        xkb_dir = dir_prefix / 'share' / 'X11' / 'xkb'
    endif
endif

xkb_output_dir = get_option('xkb_output_dir')
if xkb_output_dir == ''
    xkb_output_dir = xkb_dir / 'compiled'
endif

xkb_bin_dir = get_option('xkb_bin_dir')
if xkb_bin_dir == ''
    if dep_xkbcomp.found() and dep_xkbcomp.type_name() == 'pkgconfig'
        xkb_bin_dir = dep_xkbcomp.get_variable(pkgconfig: 'bindir')
    endif
    if xkb_bin_dir == ''
        xkb_bin_dir = dir_bin
    endif
endif

dfp = get_option('default_font_path')
if dfp == ''
    fontrootdir = get_option('fontrootdir')
    if fontrootdir == ''
        if dep_fontutil.found()
            fontrootdir = dep_fontutil.get_variable(pkgconfig: 'fontrootdir')
        else
            fontrootdir = dir_data / 'fonts' / 'X11'
        endif
    endif
    dfp_elements = [
        fontrootdir / 'misc',
        fontrootdir / 'TTF',
        fontrootdir / 'OTF',
        fontrootdir / 'Type1',
        fontrootdir / '100dpi',
        fontrootdir / '75dpi',
    ]
    if host_machine.system() == 'darwin'
       dfp_elements += [
       '/Library/Fonts',
       '/System/Library/Fonts',
    ]
    endif
    default_font_path = ','.join(dfp_elements)
else
    default_font_path = dfp
endif

glamor_option = get_option('glamor')

hal_option = get_option('hal')
if ['windows', 'darwin', 'cygwin'].contains(host_machine.system())
    hal_option = 'false'
endif

build_udev = get_option('udev')
build_udev_kms = get_option('udev_kms')
if ['windows', 'darwin', 'cygwin', 'freebsd', 'netbsd', 'openbsd', 'sunos'].contains(host_machine.system())
    build_udev = false
    build_udev_kms = false
endif

if get_option('systemd_logind') == 'auto'
    build_systemd_logind = build_udev_kms and dep_dbus.found()
else
    build_systemd_logind = get_option('systemd_logind') == 'true'
endif

with_dtrace = get_option('dtrace')
if with_dtrace
    dtrace = find_program('dtrace', required: true)
endif

build_xorg = false
if (host_machine.system() != 'windows')
    if get_option('xorg') == 'auto'
        build_xorg = (host_machine.system() != 'darwin' and
                      host_machine.system() != 'windows')
    else
        build_xorg = get_option('xorg') == 'true'
    endif
endif

xorgsdkdir = dir_include / 'xorg'

build_xwayland = false
if (host_machine.system() != 'darwin' and
    host_machine.system() != 'windows' and
    get_option('xwayland') == true)
    xwayland_required = get_option('xwayland') == true
    build_glamor = get_option('glamor')

    xwayland_path = get_option('xwayland-path')
    if (xwayland_path == '')
        xwayland_path = dir_bin
    endif

    dep_xwayland = [
        dependency('wayland-client', version: wl_req, required: xwayland_required),
        dependency('wayland-protocols', version: wl_proto_req, required: xwayland_required),
        libxcvt,
    ]
    if build_glamor
        dep_xwayland += dependency('xshmfence', version: xshmfence_req, required: xwayland_required)
        dep_xwayland += dep_drm
        dep_xwayland += dependency('epoxy', required: xwayland_required)
    endif

    build_xwayland = true
    # check for all the deps being found, to handle 'auto' mode.
    foreach d: dep_xwayland
        if not d.found()
            build_xwayland = false
        endif
    endforeach
endif

## configure Xnest - nesting X server
build_xnest = get_option('xnest')
xnest_required = get_option('xnest')
dep_xnest = [libxext, libx11, libxau]

build_xwin = false
if get_option('xwin') == 'auto'
    if (host_machine.system() == 'cygwin' or
        host_machine.system() == 'windows')
            build_xwin = true
    endif
else
    build_xwin = get_option('xwin') == 'true'
endif

build_xquartz = false
if get_option('xquartz') == 'auto'
    if host_machine.system() == 'darwin'
            build_xquartz = true
    endif
else
    build_xquartz = get_option('xquartz') == 'true'
endif

build_rootless = false
if build_xquartz
    build_rootless = true
endif

# IPv6 support
have_AF_INET6 = cc.compiles('''
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
int main(void) { int foo = AF_INET6; return foo; }''')
if get_option('ipv6') == 'auto'
    build_ipv6 = cc.has_function('getaddrinfo') and have_AF_INET6
else
    build_ipv6 = get_option('ipv6') == 'true'
endif
if build_ipv6 and not have_AF_INET6
    error('ipv6 support needs AF_INET6')
endif
message('IPv6 support: ' + (build_ipv6 ? 'YES': 'NO'))

int10 = get_option('int10')
if int10 == 'auto'
    int10 = 'x86emu'
    if host_machine.cpu() == 'ppc' and host_machine.system() == 'freebsd'
        int10 = 'stub'
    endif
    if host_machine.cpu() == 'arm'
        int10 = 'stub'
    endif
endif

dep_hal = []
if hal_option == 'auto'
    if not build_udev
        dep_hal = dependency('hal', required: false)
        build_hal = dep_hal.found()
    else
        build_hal = false
    endif
else
    build_hal = hal_option == 'true'
    if build_hal
        dep_hal = dependency('hal')
    endif
endif

if build_udev and build_hal
    error('Hotplugging through both libudev and hal not allowed')
endif

build_dbus = build_hal or build_systemd_logind

dep_udev = dep_null
if build_udev or build_udev_kms
    dep_udev = dependency('libudev', version: '>= 143')
endif

log_dir = get_option('log_dir')
if log_dir == ''
    log_dir = get_option('prefix') / get_option('localstatedir') / 'log'
endif

module_dir = get_option('libdir') / get_option('module_dir')

build_glamor = get_option('glamor')

dep_gbm = dep_null
dep_epoxy = dep_null
if build_glamor
    dep_gbm = dependency('gbm', version: gbm_req, required: false)
    dep_epoxy = dependency('epoxy', required: false)
endif

if build_xwayland
    dep_libdecor = dependency('libdecor-0', required: false)
    libdecor_option = get_option('libdecor')
    if libdecor_option == 'auto'
        have_libdecor = dep_libdecor.found()
    else
        have_libdecor = libdecor_option == 'true'
        if have_libdecor and not dep_libdecor.found()
            error('libdecor support requested but not found')
        endif
    endif
else
    have_libdecor = false
endif

if build_xwayland
    dep_libei = dependency('libei-1.0', version: '>= 1.0.0', required: get_option('xwayland_ei') in ['portal', 'socket'])
    dep_liboeffis = dependency('liboeffis-1.0', version: '>= 1.0.0', required: get_option('xwayland_ei') == 'portal')

    build_ei = dep_libei.found() and get_option('xwayland_ei') != 'false'
    build_ei_portal = dep_liboeffis.found() and get_option('xwayland_ei') in ['portal', 'auto']
else
    build_ei = false
    build_ei_portal = false
endif

# Lots of sha1 options, because Linux is about choice :)

# The idea behind the ordering here is that we should first prefer system
# builtin providers, and then smaller implementations of over larger ones.
test_sha1 = [
    'libc',          # libmd API is in libc on some BSDs
    'CommonCrypto',  # darwin API
    'CryptoAPI',     # windows API
    'libmd',         # other BSDs & Solaris
    'libsha1',       # "a tiny library providing a SHA1 implementation, created for facilitating X server compilation on embedded devices where larger libraries containing SHA1 implementations are not needed"
    'libnettle',
    'libgcrypt',     # in debian base system
    'libcrypto',
]

if get_option('sha1') != 'auto'
    test_sha1 = [get_option('sha1')]
endif

sha1_found = false
foreach t: test_sha1
    if t == 'libc'
        if cc.has_function('SHA1Init')
            sha1_found = true
            dep_sha1 = dep_null
        endif
    elif t == 'CommonCrypto'
        if cc.has_function('CC_SHA1_Init')
            sha1_found = true
            dep_sha1 = dep_null
        endif
    elif t == 'CryptoAPI'
        if cc.has_header('wincrypt.h')
            sha1_found = true
            dep_sha1 = dep_null
        endif
    elif t == 'libmd'
        dep_md = cc.find_library('md', required: false)
        if dep_md.found()
            sha1_found = true
            dep_sha1 = dep_md
        endif
    elif t == 'libsha1'
        dep_libsha1 = dependency('libsha1', required: false)
        if dep_libsha1.found()
            sha1_found = true
            dep_sha1 = dep_libsha1
        endif
    elif t == 'libnettle'
        dep_nettle = dependency('nettle', required: false)
        if dep_nettle.found()
            sha1_found = true
            dep_sha1 = dep_nettle
        endif
    elif t == 'libgcrypt'
        dep_gcrypt = dependency('libgcrypt', required: false)
        if dep_gcrypt.found()
            sha1_found = true
            dep_sha1 = dep_gcrypt
        endif
    elif t == 'libcrypto'
        # we don't need all of OpenSSL, just libcrypto
        dep_libcrypto = cc.find_library('crypto', required: false)
        dep_openssl = dependency('openssl', required: false)
        if dep_libcrypto.found() or dep_openssl.found()
            sha1_found = true
            if dep_libcrypto.found()
               dep_sha1 = dep_libcrypto
            else
               dep_sha1 = dep_openssl
            endif
        endif
    endif

    if sha1_found
        sha1 = t
        break
    endif
endforeach

if sha1_found
    message('Using @0@ SHA1 functions'.format(sha1))
else
    if get_option('sha1') != 'auto'
        error('@0@ SHA1 requested, but not found'.format(get_option('sha1')))
    else
        error('No suitable SHA1 implementation found')
    endif
endif

has_xdm_auth = get_option('xdm-auth-1')

build_glx = get_option('glx')
if build_glx
    build_hashtable = true
endif

if get_option('dri1') == 'auto'
    build_dri1 = xproto.found() and dep_drm.found()
else
    build_dri1 = get_option('dri1') == 'true'
endif

if get_option('dri2') == 'auto'
    build_dri2 = xproto.found() and dep_drm.found()
else
    build_dri2 = get_option('dri2') == 'true'
endif

if host_machine.system() in ['freebsd', 'openbsd']
   dep_epoll = dependency('epoll-shim')
else
   dep_epoll = []
endif

have_eventfd = cc.has_header('sys/eventfd.h', dependencies: dep_epoll)
if get_option('dri3') == 'auto'
    build_dri3 = xproto.found() and dep_xshmfence.found() and dep_drm.found() and have_eventfd
else
    build_dri3 = get_option('dri3') == 'true'
    if build_dri3
       if not dep_xshmfence.found()
           error('DRI3 requested, but xshmfence not found')
       endif
       if not have_eventfd
           error('DRI3 requested, but sys/eventfd.h not found')
       endif
    endif
endif

libdrm_required = (build_dri1 or build_dri2 or build_dri3) and get_option('drm') == true
if not dep_drm.found() and libdrm_required
    error('DRI requested, but LIBDRM not found')
endif

build_modesetting = dep_drm.found() and xproto.found()

build_vgahw = false
if get_option('vgahw') == 'auto'
    if (host_machine.system() != 'darwin' and
        host_machine.system() != 'windows' and
        host_machine.system() != 'cygwin')
        build_vgahw = true
    endif
else
    build_vgahw = get_option('vgahw') == 'true'
endif

build_dpms = get_option('dpms')
if build_xquartz
    build_dpms = false
endif

build_xf86bigfont = get_option('xf86bigfont')
build_screensaver = get_option('screensaver')
build_res = get_option('xres')
if build_res
    build_hashtable = true
endif

build_xace = get_option('xace')
build_xinerama = get_option('xinerama')

build_xsecurity = get_option('xcsecurity')
if build_xsecurity
    if not build_xace
        error('cannot build Security extension without X-ACE')
    endif
endif

build_xv = get_option('xv')
build_xvmc = get_option('xvmc')
if not build_xv
    build_xvmc = false
endif

build_xdmcp = get_option('xdmcp')

build_dga = false
if get_option('dga') == 'auto' or get_option('dga') == 'true'
    build_dga = true
endif

build_apm = false
if get_option('linux_apm') and host_machine.system() == 'linux'
    if cc.has_header('linux/apm_bios.h')
        build_apm = true
    endif
endif

build_acpi = false
if get_option('linux_acpi') and host_machine.system() == 'linux'
    if (host_machine.cpu() == 'x86' or
       host_machine.cpu() == 'x86_64' or
       host_machine.cpu() == 'ia64')
        build_acpi = true
    endif
endif

build_mitshm = false
if get_option('mitshm') == 'auto'
    build_mitshm = cc.has_header('sys/shm.h')
elif get_option('mitshm') == 'true'
    build_mitshm = true
endif

dep_common = [
    xproto,
    dep_libsystemd_daemon,
    dep_pixman,
    dep_libbsd,
    libxkbfile,
    libxfont,
    libxdmcp,
]

inc = [
    inc_x11,
    inc_lib,
    inc_font,
    include_directories(
        '.',
        'Xext',
        'Xi',
        'composite',
        'damageext',
        'exa',
        'fb',
        'glamor',
        'mi',
        'miext/damage',
        'miext/shadow',
        'miext/sync',
        'dbe',
        'dix',
        'dri3',
        'include',
        'present',
        'randr',
        'render',
        'xfixes',
    )
]

build_xselinux = false
if get_option('xselinux') != 'false'
    dep_selinux = dependency('libselinux', version: libselinux_req,
			     required: get_option('xselinux') == 'true')
    dep_audit = dependency('audit', required: get_option('xselinux') == 'true')
    if get_option('xselinux') == 'true'
        build_xselinux = true
    else
        build_xselinux = dep_selinux.found() and dep_audit.found()
    endif

    if build_xselinux
        dep_common += dep_selinux
        dep_common += dep_audit
    endif
endif

dep_socket = []
if host_machine.system() == 'windows'
    dep_socket = meson.get_compiler('c').find_library('ws2_32')
    dep_common += dep_socket
endif

if get_option('libunwind')
    dep_common += dependency('libunwind', required: true)
endif

glx_inc = include_directories('glx')
top_dir_inc = include_directories('.')

serverconfigdir = get_option('serverconfigdir')
if serverconfigdir == ''
    serverconfigdir = dir_lib / 'xorg'
endif

# Include must come first, as it sets up dix-config.h
subdir('include')

# X server core
subdir('config')
subdir('dix')
subdir('dri3')
subdir('glx')
subdir('os')
subdir('mi')
subdir('render')
subdir('fb')

# X extensions
subdir('composite')
subdir('damageext')
subdir('dbe')
subdir('miext' / 'damage')
subdir('miext' / 'shadow')
subdir('miext' / 'sync')
if build_rootless
    subdir('miext' / 'rootless')
endif
subdir('present')
if build_xwin or build_xquartz
    subdir('pseudoramiX')
endif
subdir('randr')
subdir('record')
subdir('xfixes')
subdir('xkb')
subdir('Xext')
subdir('Xi')

# other
if build_glamor
    subdir('glamor')
endif
if build_xorg or get_option('xephyr')
    subdir('exa')
endif

# Common static libraries of all X servers
libxserver = [
    libxserver_mi,
    libxserver_dix,
    libxserver_composite,
    libxserver_damageext,
    libxserver_dbe,
    libxserver_randr,
    libxserver_miext_damage,
    libxserver_render,
    libxserver_present,
    libxserver_xext,
    libxserver_miext_sync,
    libxserver_xfixes,
    libxserver_xi,
    libxserver_xkb,
    libxserver_record,
    libxserver_os,
    libxserver_dri3,
]

subdir('hw')

if host_machine.system() != 'windows'
    # subdir('test')
endif

if build_xorg
    sdkconfig = configuration_data()
    awk = find_program('awk')

    sdkconfig.set('prefix', get_option('prefix'))
    sdkconfig.set('exec_prefix', '${prefix}')
    sdkconfig.set('libdir', '${exec_prefix}' / get_option('libdir'))
    sdkconfig.set('includedir', '${prefix}' / get_option('includedir'))
    sdkconfig.set('datarootdir', '${prefix}' / get_option('datadir'))
    sdkconfig.set('moduledir', '${exec_prefix}' / module_dir)
    sdkconfig.set('sdkdir', '${prefix}' / get_option('includedir') / 'xorg')
    sdkconfig.set('sysconfigdir', '${datarootdir}' / 'X11' / 'xorg.conf.d')
    sdkconfig.set('abi_ansic',
        run_command(awk, '-F', '[(,)]',
                    '/^#define ABI_ANSIC.*SET/ { printf "%d.%d", $2, $3 }',
                    files('hw/xfree86/common/xf86Module.h'),
                    check: false
        ).stdout()
    )
    sdkconfig.set('abi_videodrv',
        run_command(awk, '-F', '[(,)]',
                    '/^#define ABI_VIDEODRV.*SET/ { printf "%d.%d", $2, $3 }',
                    files('hw/xfree86/common/xf86Module.h'),
                    check: false
        ).stdout()
    )
    sdkconfig.set('abi_xinput',
        run_command(awk, '-F', '[(,)]',
                    '/^#define ABI_XINPUT.*SET/ { printf "%d.%d", $2, $3 }',
                    files('hw/xfree86/common/xf86Module.h'),
                    check: false
        ).stdout()
    )
    sdkconfig.set('abi_extension',
        run_command(awk, '-F', '[(,)]',
                    '/^#define ABI_EXTENSION.*SET/ { printf "%d.%d", $2, $3 }',
                    files('hw/xfree86/common/xf86Module.h'),
                    check: false
        ).stdout()
    )

    sdk_required_modules = [
      'pixman-1 >= 0.27.2',
      f'xproto @xproto_req@',
    ]

    # XXX this isn't trying very hard, but hard enough.
    sdkconfig.set('PACKAGE_VERSION', meson.project_version())
    sdkconfig.set('SDK_REQUIRED_MODULES', ' '.join(sdk_required_modules))
    sdkconfig.set('symbol_visibility', '-fvisibility=hidden')
    sdkconfig.set('XORG_DRIVER_LIBS', '')

    # On Windows, modules built with the SDK will need to link with server and
    # module implibs to resolve symbols
    if (host_machine.system() == 'cygwin' or
        host_machine.system() == 'windows')
        sdkconfig.set('XORG_DRIVER_LIBS', '-lXorg.exe -L\${moduledir} -lshadow -no-undefined')
    endif

    configure_file(
        input: 'xorg-server.pc.in',
        output: 'xorg-server.pc',
        configuration: sdkconfig,
        install_dir: dir_lib / 'pkgconfig',
    )
endif