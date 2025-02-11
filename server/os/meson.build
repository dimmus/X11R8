srcs_os = files(
    'WaitFor.c',
    'access.c',
    'alloc.c',
    'auth.c',
    'backtrace.c',
    'client.c',
    'connection.c',
    'fmt.c',
    'inputthread.c',
    'io.c',
    'mitauth.c',
    'osinit.c',
    'ospoll.c',
    'serverlock.c',
    'string.c',
    'utils.c',
    'xdmauth.c',
    'xsha1.c',
    'xstrans.c',
    'xprintf.c',
    'log.c',
    'xdmcp.c',
    'busfault.c',
    'timingsafe_memcmp.c',
    'xserver_poll.c'
)

srcs_libc = files(
    'reallocarray.c',
    'strcasecmp.c',
    'strcasestr.c',
    'strlcat.c',
    'strlcpy.c',
    'strndup.c',
)

dep_os = []
os_c_args = []

if get_option('xres')
    os_c_args += '-DCLIENTIDS'
    if host_machine.system() == 'openbsd'
        dep_os += cc.find_library('kvm')
    endif
endif

libxlibc = static_library('libxlibc',
    srcs_libc,
    include_directories: inc_server,
    dependencies: xproto,
)

if enable_input_thread
    dep_os += cc.find_library('pthread')
endif

libxserver_os = static_library('libxserver_os',
    srcs_os,
    include_directories: inc_server,
    dependencies: [
        dep_dtrace,
        dep_common,
        dep_dl,
        dep_sha1,
        dep_os,
        libxau,
    ],
    c_args: os_c_args,
    link_with: libxlibc,
)