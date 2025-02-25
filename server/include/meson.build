version_split = '21.0.99'.split('.')
major = version_split[0].to_int()
minor = version_split[1].to_int()
patch = version_split[2].to_int()

# convert to the old-style 1.x.y version scheme used up to 1.20.x for backwards compatibility
release = 10000000 + (major * 100000) + (minor * 1000) + patch
conf.set('XORG_VERSION_CURRENT', release)

conf_server = configuration_data()
xorg_data = configuration_data()

conf_server.set('_DIX_CONFIG_H_', '1')

conf_server.set('MONOTONIC_CLOCK', cc.has_function('clock_gettime') and
cc.compiles('''
    #define _POSIX_C_SOURCE 200112L
    #include <time.h>
    #include <unistd.h>
    #ifndef CLOCK_MONOTONIC
    #error CLOCK_MONOTONIC not defined
    #endif
''',
    name: 'CLOCK_MONOTONIC') ? '1' : false)

conf_server.set('XSERVER_DTRACE', WITH_DTRACE ? '1' : false)
conf_server.set('X_BYTE_ORDER', host_machine.endian() == 'little' ? 'X_LITTLE_ENDIAN' : 'X_BIG_ENDIAN')

# Defining _XSERVER64 on 64bit builds is VITAL, since otherwise Xlib headers
# would define lots X types (eg. Atom, XID, etc) as 64 bit, but inside the
# Xserver we really need them to be 32 bit (CARD32). When _SERVER64 is defined
# the xlib headers will typedef them exactly to CARD32.
glx_align64 = []
if cc.sizeof('unsigned long') == 8
   conf_server.set('_XSERVER64', true)
   xorg_data.set('_XSERVER64', true)
   glx_align64 = '-D__GLX_ALIGN64'
endif

# autoconf checks for /dev/xf86 here, but the test should be based on
# the target, not the build system.  Could we get rid of this and just
# ifdef for openbsd?
conf_server.set('HAS_APERTURE_DRV', host_machine.system() == 'openbsd' ? '1' : false)

enable_input_thread = cc.has_header_symbol('pthread.h', 'PTHREAD_MUTEX_RECURSIVE')
conf_server.set('INPUTTHREAD', enable_input_thread ? '1' : false)

if cc.compiles('''
    #define _GNU_SOURCE 1
    #include <pthread.h>
    void foo(int bar) { pthread_setname_np(pthread_self(), "example"); }
''',
    args: '-Werror-implicit-function-declaration',
    name: 'pthread_setname_np(tid, name)')
    conf_server.set('HAVE_PTHREAD_SETNAME_NP_WITH_TID', 1)
elif cc.compiles('''
    #define _GNU_SOURCE 1
    #include <pthread.h>
    void foo(int bar) { pthread_setname_np("example"); }
''',
    args: '-Werror-implicit-function-declaration',
    name: 'pthread_setname_np(name)')
    conf_server.set('HAVE_PTHREAD_SETNAME_NP_WITHOUT_TID', 1)
endif

conf_server.set('HAVE_LIBBSD', dep_libbsd.found() ? '1' : false)
conf_server.set('HAVE_SYSTEMD_DAEMON', build_systemd_notify ? '1' : false)
conf_server.set('CONFIG_UDEV', build_udev ? '1' : false)
conf_server.set('CONFIG_UDEV_KMS', build_udev_kms ? '1' : false)
conf_server.set('HAVE_DBUS', build_dbus ? '1' : false)
conf_server.set('CONFIG_HAL', build_hal ? '1' : false)
conf_server.set('SYSTEMD_LOGIND', build_systemd_logind ? '1' : false)
conf_server.set('NEED_DBUS', build_systemd_logind or build_hal ? '1' : false)
conf_server.set('CONFIG_WSCONS', host_machine.system() in ['openbsd', 'netbsd'] ? '1' : false)
conf_server.set('HAVE_XSHMFENCE', true)
conf_server.set('WITH_LIBDRM', true)
conf_server.set('GLXEXT', build_glx ? '1' : false)
conf_server.set('GLAMOR', '1')
conf_server.set('GLAMOR_HAS_EGL_QUERY_DMABUF', dep_epoxy.found() and dep_epoxy.version().version_compare('>= 1.4.4') ? '1' : false)
conf_server.set('GLAMOR_HAS_EGL_QUERY_DRIVER', dep_epoxy.found() and dep_epoxy.version().version_compare('>= 1.5.4') ? '1' : false)
conf_server.set('GLAMOR_HAS_GBM', dep_gbm.found() ? '1' : false)
conf_server.set('GLAMOR_HAS_GBM_LINEAR',  dep_gbm.found() and dep_gbm.version().version_compare('>= 10.6') ? '1' : false)
conf_server.set('GBM_BO_WITH_MODIFIERS',  dep_gbm.found() and dep_gbm.version().version_compare('>= 17.1') ? '1' : false)
conf_server.set('GBM_BO_FD_FOR_PLANE',    dep_gbm.found() and dep_gbm.version().version_compare('>= 21.1') ? '1' : false)
conf_server.set('GBM_BO_WITH_MODIFIERS2', dep_gbm.found() and dep_gbm.version().version_compare('>= 21.3') ? '1' : false)
conf_server.set('XORG_VERSION_CURRENT', release)
conf_server.set('HASXDMAUTH', '1')
conf_server.set_quoted('SERVER_MISC_CONFIG_PATH', serverconfigdir)
conf_server.set_quoted('PROJECTROOT', dir_prefix)
conf_server.set_quoted('SYSCONFDIR', dir_sysconf)
conf_server.set_quoted('SUID_WRAPPER_DIR', dir_libexec)
conf_server.set_quoted('COMPILEDDEFAULTFONTPATH', default_font_path)
conf_server.set('HAVE_REALLOCARRAY',  cc.has_function('reallocarray', dependencies: dep_libbsd))
conf_server.set('HAVE_STRNDUP',       cc.has_function('strndup') and cc.has_header_symbol('string.h', 'strndup'))
conf_server.set('HAVE_XUCRED_CR_PID', cc.has_member('struct xucred', 'cr_pid', prefix: '#include <sys/ucred.h>'))
conf_server.set('HAVE_STRLCAT',       cc.has_function('strlcat', dependencies: dep_libbsd))
conf_server.set('HAVE_STRLCPY',       cc.has_function('strlcpy', dependencies: dep_libbsd))
conf_server.set('HAVE_SOCKLEN_T',     cc.has_type('socklen_t', prefix: '#include <sys/socket.h>') ? '1' : false)
conf_server.set('LOCK_SERVER', '1')
conf_server.set('_XTYPEDEF_POINTER', true) # Don't let X dependencies typedef 'pointer'
conf_server.set('_XITYPEDEF_POINTER', '1')
conf_server.set('LISTEN_TCP',   get_option('listen_tcp'))
conf_server.set('LISTEN_UNIX',  get_option('listen_unix'))
conf_server.set('LISTEN_LOCAL', get_option('listen_local'))
conf_server.set('XTRANS_SEND_FDS', cc.has_header_symbol('sys/socket.h', 'SCM_RIGHTS') ? '1' : false)
conf_server.set('NO_LOCAL_CLIENT_CRED', cc.has_header_symbol('sys/socket.h', 'SO_PEERCRED', args: '-D_GNU_SOURCE'))
conf_server.set('TCPCONN',       '1')
conf_server.set('UNIXCONN',      '1')
conf_server.set('BIGREQS',       '1')
conf_server.set('COMPOSITE',     '1')
conf_server.set('DAMAGE',        '1')
conf_server.set('DBE',           '1')
conf_server.set('IPv6',          build_ipv6 ? '1' : false)
conf_server.set('DGA',           build_dga  ? '1' : false)
conf_server.set('DPMSExtension', build_dpms ? '1' : false)
conf_server.set('DRI2',          true)
conf_server.set('DRI3',          build_dri3 ? '1' : false)
conf_server.set_quoted('DRI_DRIVER_PATH', build_glx ? dep_dri.get_variable(pkgconfig: 'dridriverdir') : '')
conf_server.set('PRESENT',       '1')
conf_server.set('RANDR',         '1')
conf_server.set('RENDER',        '1')
conf_server.set('SHAPE',         '1')
conf_server.set('XCMISC',        '1')
conf_server.set('XDMCP',         '1')
conf_server.set('XF86VIDMODE',   '1')
conf_server.set('XFIXES',        '1')
conf_server.set('XINPUT',        '1')
conf_server.set('XRECORD',       '1')
conf_server.set('XSYNC',         '1')
conf_server.set('XTEST',         '1')
conf_server.set('MITSHM',        build_mitshm)
conf_server.set('PANORAMIX',     build_xinerama)
conf_server.set('RES',           build_res)
conf_server.set('SCREENSAVER',   build_screensaver)
conf_server.set('XACE',          build_xace)
conf_server.set('XCSECURITY',    build_xsecurity)
conf_server.set('XF86BIGFONT',   build_xf86bigfont)
conf_server.set('XF86DRI',       true) # DRI1 support removed
conf_server.set('XFreeXDGA',     build_dga)
conf_server.set('XINERAMA',      build_xinerama)
conf_server.set('XSELINUX',      build_xselinux)
conf_server.set('XV',            build_xv)
conf_server.set('XvExtension',   build_xv)
conf_server.set('XvMCExtension', build_xvmc)
conf_server.set('X_REGISTRY_RESOURCE', (build_xselinux or build_res) ? '1' : false)
conf_server.set('X_REGISTRY_REQUEST', (build_xselinux or build_xsecurity or WITH_DTRACE) ? '1' : false)
conf_server.set('HAVE_SHA1_IN_' + sha1.to_upper(), '1', description: 'Use @0@ SHA1 functions'.format(sha1))
conf_server.set('HAVE_LIBUNWIND', get_option('libunwind'))
conf_server.set('HAVE_APM', (build_apm or build_acpi) ? '1' : false)
conf_server.set('HAVE_ACPI', build_acpi ? '1' : false)
conf_server.set('DEBUG', get_option('buildtype') == 'debug' ? '1' : false)
conf_server.set_quoted('XVENDORNAME',           get_option('vendor_name'))
conf_server.set_quoted('XVENDORNAMESHORT',      get_option('vendor_name_short'))
conf_server.set_quoted('__VENDORDWEBSUPPORT__', get_option('vendor_web'))

h_check_server = [
    'dlfcn.h', 'execinfo.h', 'fnmatch.h', 'linux/agpgart.h', 'strings.h',
    'sys/agpgart.h', 'sys/ucred.h', 'sys/un.h', 'sys/utsname.h', 'sys/sysmacros.h',
]

foreach h: h_check_server
    conf_server.set('HAVE_@0@'.format(h.underscorify().to_upper()), cc.has_header(h))
    xorg_data.set('HAVE_@0@'.format(h.underscorify().to_upper()), cc.has_header(h))
endforeach

f_check_server = [
    'backtrace', 'cbrt', 'epoll_create1', 'getuid', 'geteuid', 'isastream',
    'issetugid', 'getaddrinfo', 'getifaddrs', 'getpeereid', 'getpeerucred',
    'getprogname', 'getzoneid', 'inet_ntop', 'memfd_create', 'mkostemp',
    'mmap', 'open_device', 'poll', 'pollset_create', 'posix_fallocate',
    'port_create', 'reallocarray', 'seteuid', 'setitimer', 'shmctl64',
    'sigaction', 'sigprocmask', 'strcasecmp', 'strcasestr', 'strncasecmp',
    'timingsafe_memcmp', 'vasprintf', 'vsnprintf', 'walkcontext', 
]

foreach f: f_check_server
    conf_server.set('HAVE_@0@'.format(f.to_upper()), cc.has_function(f))
    xorg_data.set('HAVE_@0@'.format(f.to_upper()), cc.has_function(f))
endforeach

summary_srv += {'XSERVER_DTRACE':         WITH_DTRACE}
summary_srv += {'X_BYTE_ORDER':           conf_server.get('X_BYTE_ORDER')}
summary_srv += {'INPUTTHREAD':            enable_input_thread}
summary_srv += {'HAVE_LIBBSD':            dep_libbsd.found()}
summary_srv += {'SYSTEMD_DAEMON':         build_systemd_notify}
summary_srv += {'SYSTEMD_LOGIND':         build_systemd_logind}
summary_srv += {'CONFIG_UDEV':            build_udev}
summary_srv += {'CONFIG_UDEV_KMS':        build_udev_kms}
summary_srv += {'HAVE_DBUS':              build_dbus}
summary_srv += {'CONFIG_HAL':             build_hal}
summary_srv += {'NEED_DBUS':              build_systemd_logind or build_hal}
summary_srv += {'GLXEXT':                 build_glx}
summary_srv += {'EGL_QUERY_DMABUF':       dep_epoxy.found() and dep_epoxy.version().version_compare('>= 1.4.4')}
summary_srv += {'EGL_QUERY_DRIVER':       dep_epoxy.found() and dep_epoxy.version().version_compare('>= 1.5.4')}
summary_srv += {'GBM':                    dep_gbm.found()}
summary_srv += {'GBM_LINEAR':             dep_gbm.found() and dep_gbm.version().version_compare('>= 10.6')}
summary_srv += {'GBM_BO_WITH_MODIFIERS':  dep_gbm.found() and dep_gbm.version().version_compare('>= 17.1')}
summary_srv += {'GBM_BO_FD_FOR_PLANE':    dep_gbm.found() and dep_gbm.version().version_compare('>= 21.1')}
summary_srv += {'GBM_BO_WITH_MODIFIERS2': dep_gbm.found() and dep_gbm.version().version_compare('>= 21.3')}
summary_srv += {'IPv6': build_ipv6}
summary_srv += {'DGA': build_dga}
summary_srv += {'DPMSExtension': build_dpms}
summary_srv += {'DRI2': true}
summary_srv += {'DRI3': build_dri3}
if build_glx
summary_srv += {'DRI_DRIVER_PATH': dir_lib / 'dri'}
endif
summary_srv += {'MITSHM': build_mitshm}
summary_srv += {'PANORAMIX': build_xinerama}
summary_srv += {'RES': build_res}
summary_srv += {'SCREENSAVER': build_screensaver}
summary_srv += {'XACE': build_xace}
summary_srv += {'XCSECURITY': build_xsecurity}
summary_srv += {'XF86BIGFONT': build_xf86bigfont}
summary_srv += {'XFreeXDGA': build_dga}
summary_srv += {'XINERAMA': build_xinerama}
summary_srv += {'XSELINUX': build_xselinux}
summary_srv += {'XV': build_xv}
summary_srv += {'XvExtension': build_xv}
summary_srv += {'XvMCExtension': build_xvmc}
summary_srv += {'HAVE_APM': build_apm or build_acpi}
summary_srv += {'HAVE_ACPI': build_acpi}

#
# for xorg-server.h only
#
defines_svr4 = '''#if !defined(SVR4) && !defined(__svr4__) && !defined(__SVR4)
#error "I am not SVR4"
#endif
'''

# BSD specifics
supports_pccons = false
supports_pcvt = false
supports_syscons = false
supports_wscons = false
csrg_based = false

if host_machine.system() == 'freebsd' or host_machine.system() == 'dragonfly'
  supports_pccons = true
  supports_pcvt = true
  supports_syscons = true
  csrg_based = true
endif

if host_machine.system() == 'netbsd'
  supports_pccons = true
  supports_pcvt = true
  supports_wscons = true
  csrg_based = true
endif

if host_machine.system() == 'openbsd'
  supports_pcvt = true
  supports_wscons = true
  csrg_based = true
endif

if host_machine.system() == 'darwin'
  csrg_based = true
endif

conf_server.set('SVR4', cc.compiles(defines_svr4) ? '1' : false)
conf_server.set_quoted('XKB_DFLT_RULES', get_option('xkb_default_rules'))
conf_server.set_quoted('XCONFIGFILE', 'xorg.conf')
conf_server.set_quoted('__XSERVERNAME__', 'Xorg')
conf_server.set('CSRG_BASED', csrg_based ? '1' : false)
conf_server.set('PCCONS_SUPPORT', supports_pccons ? '1' : false)
conf_server.set('PCVT_SUPPORT', supports_pcvt ? '1' : false)
conf_server.set('SYSCONS_SUPPORT', supports_syscons ? '1' : false)
conf_server.set('WSCONS_SUPPORT', supports_wscons ? '1' : false)
conf_server.set('XSERVER_LIBPCIACCESS', get_option('pciaccess'))
conf_server.set('XSERVER_PLATFORM_BUS', build_udev_kms)
conf_server.set('HAVE_OPENSSL3', dep_openssl.version().version_compare('>= 3'))

summary_srv += {'XKB_DFLT_RULES': get_option('xkb_default_rules')}
summary_srv += {'SVR4': cc.compiles(defines_svr4)}
if ['freebsd', 'netbsd', 'openbsd', 'sunos'].contains(host_machine.system())
summary_srv += {'CSRG_BASED (BSD)': csrg_based}
summary_srv += {'PCCONS_SUPPORT (BSD)': supports_pccons}
summary_srv += {'PCVT_SUPPORT (BSD)': supports_pcvt}
summary_srv += {'SYSCONS_SUPPORT (BSD)': supports_syscons}
summary_srv += {'WSCONS_SUPPORT (BSD)': supports_wscons}
endif
summary_srv += {'LIBPCIACCESS': get_option('pciaccess')}
summary_srv += {'UDEV_KMS': build_udev_kms}

configure_file(output: 'dix-config.h',  configuration: conf_server)
configure_file(output: 'xorg-server.h', configuration: conf_server,
               install: true,
               install_dir: dir_xorg)

version_data = configuration_data()
version_data.set('VENDOR_RELEASE', '@0@'.format(release))
version_data.set_quoted('VENDOR_NAME',       get_option('vendor_name'))
version_data.set_quoted('VENDOR_NAME_SHORT', get_option('vendor_name_short'))
version_data.set_quoted('VENDOR_WEB',        get_option('vendor_web'))
version_data.set_quoted('VENDOR_MAN_VERSION', 'Version @0@.@1@.@2@'.format(major, minor, patch))
configure_file(output: 'version-config.h', configuration: version_data)

xkb_data = configuration_data()
xkb_data.set_quoted('XKB_BIN_DIRECTORY', xkb_bin_dir)
xkb_data.set_quoted('XKB_BASE_DIRECTORY', xkb_dir)
xkb_data.set_quoted('XKB_DFLT_RULES',   get_option('xkb_default_rules'))
xkb_data.set_quoted('XKB_DFLT_MODEL',   get_option('xkb_default_model'))
xkb_data.set_quoted('XKB_DFLT_LAYOUT',  get_option('xkb_default_layout'))
xkb_data.set_quoted('XKB_DFLT_VARIANT', get_option('xkb_default_variant'))
xkb_data.set_quoted('XKB_DFLT_OPTIONS', get_option('xkb_default_options'))
xkb_data.set_quoted('XKM_OUTPUT_DIR', xkb_output_dir + '/')
configure_file(output: 'xkb-config.h', configuration: xkb_data)

xorg_data.set_quoted('XORG_BIN_DIRECTORY', dir_bin)
xorg_data.set('XORG_VERSION_CURRENT', release)
xorg_data.set_quoted('XCONFIGFILE', 'xorg.conf')
xorg_data.set_quoted('XCONFIGDIR', 'xorg.conf.d')
xorg_data.set_quoted('DEFAULT_XDG_DATA_HOME', '.local/share')
xorg_data.set_quoted('DEFAULT_XDG_DATA_HOME_LOGDIR', 'xorg')
xorg_data.set_quoted('DEFAULT_LOGDIR', log_dir)
xorg_data.set_quoted('DEFAULT_LOGPREFIX', 'Xorg.')
xorg_data.set_quoted('DEFAULT_MODULE_PATH', dir_xorg_module)
xorg_data.set_quoted('DEFAULT_LIBRARY_PATH', dir_lib)
xorg_data.set_quoted('__XSERVERNAME__', 'Xorg')
xorg_data.set('XSERVER_LIBPCIACCESS', get_option('pciaccess'))
xorg_data.set_quoted('PCI_TXT_IDS_PATH', '')
xorg_data.set('XSERVER_PLATFORM_BUS', build_udev_kms)
xorg_data.set('WSCONS_SUPPORT', host_machine.system() == 'netbsd' or host_machine.system() == 'openbsd' ? '1' : false)
xorg_data.set('HAVE_STROPTS_H', cc.has_header('stropts.h') ? '1' : false)
xorg_data.set('HAVE_SYS_KD_H', cc.has_header('sys/kd.h') ? '1' : false)
xorg_data.set('HAVE_SYS_VT_H', cc.has_header('sys/vt.h') ? '1' : false)
xorg_data.set('HAVE_MODESETTING_DRIVER', build_modesetting)
xorg_data.set_quoted('FALLBACK_INPUT_DRIVER', 'libinput')
xorg_data.set('XF86DRI', true)
xorg_data.set('DRI2', true)
xorg_data.set('WITH_LIBDRM', true)
xorg_data.set('', true)

if host_machine.system() == 'freebsd' or host_machine.system() == 'dragonfly'
    if host_machine.cpu_family() == 'x86' or host_machine.cpu_family() == 'x86_64' or host_machine.cpu_family() == 'aarch64'
        xorg_data.set('USE_DEV_IO', '1')
    endif
elif host_machine.system() == 'netbsd' or host_machine.system() == 'openbsd'
    if host_machine.cpu_family() == 'x86'
        xorg_data.set('USE_I386_IOPL', '1')
    endif
    if host_machine.cpu_family() == 'x86_64'
        xorg_data.set('USE_AMD64_IOPL', '1')
    endif
endif

configure_file(output: 'xorg-config.h',
               input:  'xorg-config.h.meson.in',
               configuration: xorg_data)

# summary_org += {'XORG_BIN_DIRECTORY': xorg_data.get('XORG_BIN_DIRECTORY')}
# summary_org += {'XORG_VERSION_CURRENT': xorg_data.get('XORG_VERSION_CURRENT')}
# summary_org += {'XCONFIGFILE': xorg_data.get('XCONFIGFILE')}
# summary_org += {'XCONFIGDIR': xorg_data.get('XCONFIGDIR')}
# summary_org += {'XDG_DATA_HOME': xorg_data.get('DEFAULT_XDG_DATA_HOME')}
# summary_org += {'XDG_DATA_HOME_LOGDIR': xorg_data.get('DEFAULT_XDG_DATA_HOME_LOGDIR')}
# summary_org += {'LOGDIR': xorg_data.get('DEFAULT_LOGDIR')}
# summary_org += {'LOGPREFIX': xorg_data.get('DEFAULT_LOGPREFIX')}
# summary_org += {'MODULE_PATH': xorg_data.get('DEFAULT_MODULE_PATH')}
# summary_org += {'LIBRARY_PATH': xorg_data.get('DEFAULT_LIBRARY_PATH')}
# summary_org += {'__XSERVERNAME__': xorg_data.get('__XSERVERNAME__')}
# summary_org += {'MODESETTING_DRIVER': build_modesetting}

dtrace_hdr = []
dtrace_tmpl = files('Xserver.d')
if WITH_DTRACE
    dtrace_header = generator(exe_dtrace,
        output: '@BASENAME@-dtrace.h',
        arguments: ['-h', '-s', '@INPUT@', '-o', '@OUTPUT@']
    )
    dtrace_hdr += dtrace_header.process(dtrace_tmpl)
endif

install_data(
    'Xprintf.h',
    'callback.h',
    'client.h',
    'closure.h',
    'colormap.h',
    'colormapst.h',
    'hotplug.h',
    'cursor.h',
    'cursorstr.h',
    'dix.h',
    'dixaccess.h',
    'dixevents.h',
    'dixfont.h',
    'dixfontstr.h',
    'dixstruct.h',
    'events.h',
    'exevents.h',
    'extension.h',
    'extinit.h',
    'extnsionst.h',
    'fourcc.h',
    'gc.h',
    'gcstruct.h',
    'globals.h',
    'glxvndabi.h',
    'input.h',
    'inputstr.h',
    'list.h',
    'misc.h',
    'miscstruct.h',
    'opaque.h',
    'nonsdk_extinit.h',
    'optionstr.h',
    'os.h',
    'pixmap.h',
    'pixmapstr.h',
    'privates.h',
    'property.h',
    'propertyst.h',
    'ptrveloc.h',
    'region.h',
    'regionstr.h',
    'resource.h',
    'rgb.h',
    'screenint.h',
    'scrnintstr.h',
    'selection.h',
    'servermd.h',
    'validate.h',
    'displaymode.h',
    'window.h',
    'windowstr.h',
    'xkbsrv.h',
    'xkbstr.h',
    'xkbrules.h',
    'Xprintf.h',
    'xserver-properties.h',
    install_dir: dir_xorg,
)
