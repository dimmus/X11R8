srcs = files(
    'xwayland.c',
    'xwayland-input.c',
    'xwayland-cursor.c',
    'xwayland-drm-lease.c',
    'xwayland-pixmap.c',
    'xwayland-present.c',
    'xwayland-screen.c',
    'xwayland-shm.c',
    'xwayland-output.c',
    'xwayland-cvt.c',
    'xwayland-vidmode.c',
    'xwayland-window.c',
    'xwayland-window-buffers.c',
    '../../mi/miinitext.c',
)

dep_scanner = dependency('wayland-scanner', native: true)
scanner = find_program(dep_scanner.get_variable(pkgconfig: 'wayland_scanner'))

dep_protocols = dependency('wayland-protocols', version: wl_proto_req)
protodir = dep_protocols.get_variable(pkgconfig: 'pkgdatadir')

viewporter_xml          = protodir / 'stable'   / 'viewporter' / 'viewporter.xml'
xdg_shell_xml           = protodir / 'stable'   / 'xdg-shell' / 'xdg-shell.xml'
pointer_xml             = protodir / 'unstable' / 'pointer-constraints' / 'pointer-constraints-unstable-v1.xml'
relative_xml            = protodir / 'unstable' / 'relative-pointer' / 'relative-pointer-unstable-v1.xml'
gestures_xml            = protodir / 'unstable' / 'pointer-gestures' / 'pointer-gestures-unstable-v1.xml'
tablet_xml              = protodir / 'unstable' / 'tablet' / 'tablet-unstable-v2.xml'
kbgrab_xml              = protodir / 'unstable' / 'xwayland-keyboard-grab' / 'xwayland-keyboard-grab-unstable-v1.xml'
xdg_output_xml          = protodir / 'unstable' / 'xdg-output' / 'xdg-output-unstable-v1.xml'
dmabuf_xml              = protodir / 'unstable' / 'linux-dmabuf' / 'linux-dmabuf-unstable-v1.xml'
shortcuts_inhibit_xml   = protodir / 'unstable' / 'keyboard-shortcuts-inhibit' / 'keyboard-shortcuts-inhibit-unstable-v1.xml'
drm_lease_xml           = protodir / 'staging'  / 'drm-lease' / 'drm-lease-v1.xml'
xwayland_shell_xml      = protodir / 'staging'  / 'xwayland-shell' / 'xwayland-shell-v1.xml'
tearing_xml             = protodir / 'staging'  / 'tearing-control' / 'tearing-control-v1.xml'
fractional_scale_xml    = protodir / 'staging'  / 'fractional-scale' / 'fractional-scale-v1.xml'
syncobj_xml             = protodir / 'staging'  / 'linux-drm-syncobj' / 'linux-drm-syncobj-v1.xml'

proto_xml = [
    relative_xml,
    pointer_xml,
    gestures_xml,
    tablet_xml,
    kbgrab_xml,
    xdg_output_xml,
    dmabuf_xml,
    viewporter_xml,
    xdg_shell_xml,
    drm_lease_xml,
    shortcuts_inhibit_xml,
    xwayland_shell_xml,
    tearing_xml,
    fractional_scale_xml,
    syncobj_xml,
]

client_header = generator(scanner,
    output: '@BASENAME@-client-protocol.h',
    arguments: ['client-header', '@INPUT@', '@OUTPUT@']
)

if dep_scanner.version().version_compare('>= 1.14.91')
    scanner_argument = 'private-code'
else
    scanner_argument = 'code'
endif

code = generator(scanner,
    output: '@BASENAME@-protocol.c',
    arguments: [scanner_argument, '@INPUT@', '@OUTPUT@']
)

foreach xml: proto_xml
    srcs += client_header.process(xml)
    srcs += code.process(xml)
endforeach

if build_ei
    dep_xwayland += dep_libei
    srcs += [ 'xwayland-xtest.c', 'xwayland-xtest.h' ]

    if build_ei_portal
        dep_xwayland += dep_liboeffis
    endif
endif

xwayland_glamor = []
if build_xwayland_glamor
    srcs += [
        'xwayland-glamor.c',
        'xwayland-dmabuf.h',
        'xwayland-dmabuf.c',
        'xwayland-glamor-gbm.c',
        'xwayland-glamor-gbm.h'
    ]

    if build_xv
        srcs += 'xwayland-glamor-xv.c'
    endif

    srcs += client_header.process('drm.xml')
    srcs += code.process('drm.xml')
    dep_xwayland += dep_gbm
    xwayland_glamor += glamor
endif

wayland_inc = [ inc_server, ]
if build_glx
    wayland_inc += glx_inc
endif

if dep_drm.found()
    dep_xwayland += dep_drm
endif

if have_libdecor
    dep_xwayland += dep_libdecor
endif

xwayland_server = executable(
    'Xwayland',
    srcs,
    include_directories: wayland_inc,
    dependencies: [
        dep_common,
        dep_epoll,
        dep_xwayland,
        xproto,
    ],
    link_with: [
        libxserver_main,
        xwayland_glamor,
        libxserver_fb,
        libxserver,
        libxserver_xext_vidmode,
        libxserver_xkb_stubs,
        libxserver_xi_stubs,
        libxserver_glx,
        libglxvnd,
    ],
    install: true,
    install_dir: xwayland_path
)

xwayland_vars = [
    'have_glamor=' + build_glamor.to_string(),
    'have_glamor_api=' + build_glamor.to_string(),
    'have_eglstream=false',
    'have_initfd=true',
    'have_listenfd=true',
    'have_verbose=true',
    'have_terminate_delay=true',
    'have_no_touch_pointer_emulation=true',
    'have_force_xrandr_emulation=true',
    'have_geometry=true',
    'have_fullscreen=true',
    'have_host_grab=true',
    'have_decorate=' + have_libdecor.to_string(),
    'have_enable_ei_portal=' + build_ei_portal.to_string(),
    'have_byteswappedclients=true',
    'have_hidpi=true',
]

pkg.generate(
    filebase: 'xwayland',
    name: 'Xwayland',
    description: 'X Server for Wayland',
    dataonly: true,
    variables: [
        'exec_prefix=${prefix}',
        'xwayland=' + xwayland_path / xwayland_server.name(),
    ] + xwayland_vars,
)

desktop_data = configuration_data()
desktop_data.set('XWAYLAND', xwayland_path / xwayland_server.name())
desktop_data.set('DECORATE', have_libdecor ? '-decorate': '')
desktop_file = configure_file(
    input: 'desktop/org.freedesktop.Xwayland.desktop.in',
    output: 'org.freedesktop.Xwayland.desktop',
    configuration: desktop_data,
)
install_data(desktop_file, install_dir: dir_data / 'applications')

meson.override_find_program('Xwayland', xwayland_server)
meson.override_dependency('xwayland', declare_dependency(
    variables: [
        'xwayland=' + xwayland_server.full_path(),
    ] + xwayland_vars,
))
