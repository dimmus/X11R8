ver_xserver     = '21.1.99.1'
libselinux_req  = '>= 2.0.86'
gbm_req         = '>= 10.2'

build_systemd_notify = get_option('systemd_notify') == 'true'
# libsystemd-daemon was moved into libsystemd in version 209
dep_libsystemd_daemon = dep_systemd
if not dep_systemd.found()
    dep_libsystemd_daemon = dependency('libsystemd-daemon', required: false)
endif

build_hashtable = false

xkb_dir = dir_prefix / 'share' / 'X11' / 'xkb'

xkb_output_dir = get_option('xkb_output_dir')
if xkb_output_dir == ''
    xkb_output_dir = xkb_dir / 'compiled'
endif

xkb_bin_dir = get_option('xkb_bin_dir')
if xkb_bin_dir == ''
    xkb_bin_dir = dir_bin
endif

dfp = get_option('default_font_path')
if dfp == ''
    if dep_fontutil.found()
        fontrootdir = dep_fontutil.get_variable(pkgconfig: 'fontrootdir')
    else
        fontrootdir = dir_data / 'fonts' / 'X11'
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

hal_option = get_option('hal')
if host_machine.system() == 'darwin'
    hal_option = 'false'
endif

build_udev = get_option('udev')
build_udev_kms = get_option('udev_kms')
if ['darwin', 'freebsd', 'netbsd', 'openbsd', 'sunos'].contains(host_machine.system())
    build_udev = false
    build_udev_kms = false
endif

if get_option('systemd_logind') == 'auto'
    build_systemd_logind = build_udev_kms and dep_dbus.found()
else
    build_systemd_logind = get_option('systemd_logind') == 'true'
endif

# IPv6 support
have_af_inet6 = cc.compiles('''
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
int main(void) { int foo = AF_INET6; return foo; }''')
if get_option('ipv6') == 'auto'
    build_ipv6 = cc.has_function('getaddrinfo') and have_af_inet6
else
    build_ipv6 = get_option('ipv6') == 'true'
endif
if build_ipv6 and not have_af_inet6
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

log_dir = get_option('log_dir')
if log_dir == ''
    log_dir = dir_prefix / get_option('localstatedir') / 'log'
endif

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
    elif t == 'libmd'
        dep_md = cc.find_library('md', required: false)
        if dep_md.found()
            sha1_found = true
            dep_sha1 = dep_md
        endif
    elif t == 'libsha1'
        if dep_libsha1.found()
            sha1_found = true
            dep_sha1 = dep_libsha1
        endif
    elif t == 'libnettle'
        if dep_nettle.found()
            sha1_found = true
            dep_sha1 = dep_nettle
        endif
    elif t == 'libgcrypt'
        if dep_gcrypt.found()
            sha1_found = true
            dep_sha1 = dep_gcrypt
        endif
    elif t == 'libcrypto'
        # we don't need all of OpenSSL, just libcrypto
        dep_libcrypto = cc.find_library('crypto', required: false)
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

build_glx = get_option('glx')
if build_glx
    build_hashtable = true
endif

if host_machine.system() in ['freebsd', 'openbsd']
   dep_epoll = dependency('epoll-shim')
else
   dep_epoll = []
endif

build_dri2 = get_option('dri2')
build_dri3 = get_option('dri3')

if build_dri3
   if not cc.has_header('sys/eventfd.h', dependencies: dep_epoll)
       error('DRI3 requested, but sys/eventfd.h not found')
   endif
endif

build_modesetting = dep_drm.found()

build_dpms = get_option('dpms')
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
    libxkbfile,
    libxfont,
    libxdmcp,
    dep_libsystemd_daemon,
    dep_pixman,
    dep_libbsd,
]

inc_server = [
    inc_lib,
    inc_font,
    inc_pixman,
    inc_epoxy,
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

if get_option('libunwind')
    dep_common += dep_libunwind
endif

inc_server_glx = include_directories('glx')

serverconfigdir = get_option('serverconfigdir')
if serverconfigdir == ''
    serverconfigdir = dir_lib / 'xorg'
endif

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
subdir('present')
subdir('randr')
subdir('record')
subdir('xfixes')
subdir('xkb')
subdir('Xext')
subdir('Xi')

# other
subdir('glamor')
subdir('exa')

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

xserver = declare_dependency(link_with: libxserver)

subdir('hw')
if WITH_TESTS
    subdir('test')
endif

sdkconfig = configuration_data()
sdkconfig.set('prefix',      dir_prefix)
sdkconfig.set('libdir',      dir_lib)
sdkconfig.set('includedir',  dir_include)
sdkconfig.set('datarootdir', dir_data)
sdkconfig.set('moduledir',   dir_xorg_module)
sdkconfig.set('sdkdir',      dir_include / 'xorg')
sdkconfig.set('sysconfigdir', '${datarootdir}' / 'X11' / 'xorg.conf.d')
sdkconfig.set('abi_ansic',
    run_command(exe_awk, '-F', '[(,)]',
                '/^#define ABI_ANSIC.*SET/ { printf "%d.%d", $2, $3 }',
                files('hw/xfree86/common/xf86Module.h'),
                check: false
    ).stdout()
)
sdkconfig.set('abi_videodrv',
    run_command(exe_awk, '-F', '[(,)]',
                '/^#define ABI_VIDEODRV.*SET/ { printf "%d.%d", $2, $3 }',
                files('hw/xfree86/common/xf86Module.h'),
                check: false
    ).stdout()
)
sdkconfig.set('abi_xinput',
    run_command(exe_awk, '-F', '[(,)]',
                '/^#define ABI_XINPUT.*SET/ { printf "%d.%d", $2, $3 }',
                files('hw/xfree86/common/xf86Module.h'),
                check: false
    ).stdout()
)
sdkconfig.set('abi_extension',
    run_command(exe_awk, '-F', '[(,)]',
                '/^#define ABI_EXTENSION.*SET/ { printf "%d.%d", $2, $3 }',
                files('hw/xfree86/common/xf86Module.h'),
                check: false
    ).stdout()
)

# XXX this isn't trying very hard, but hard enough.
sdkconfig.set('PACKAGE_VERSION', ver_xserver)
sdkconfig.set('SDK_REQUIRED_MODULES', 'pixman xproto')
sdkconfig.set('symbol_visibility', '-fvisibility=hidden')
sdkconfig.set('XORG_DRIVER_LIBS', '')

configure_file(
    input: 'xorg-server.pc.in',
    output: 'xorg-server.pc',
    configuration: sdkconfig,
    install_dir: dir_lib / 'pkgconfig',
)