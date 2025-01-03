windows = import('windows')

xwin_sys_libs = []
xwin_sys_libs += '-ldxguid'

if host_machine.system() == 'cygwin'
    server_name = 'XWin'
else
    server_name = 'Xming'
    xwin_sys_libs += ['-lpthread', '-lws2_32']
endif

xwin_c_args = []
xwin_c_args += '-DHAVE_XWIN_CONFIG_H'
xwin_c_args += '-Wno-bad-function-cast'

srcs_windows = [
    'winclipboardinit.c',
    'winclipboardwrappers.c',
]
subdir('winclipboard')

xwin_glx = []
xwin_windowsdri = []
if build_glx
    xwin_c_args += '-DXWIN_WINDOWS_DRI'
    subdir('dri')
    xwin_c_args += '-DXWIN_GLX_WINDOWS'
    xwin_sys_libs += '-lopengl32'
    subdir('glx')
endif

srcs_windows += [
     'winmultiwindowshape.c',
     'winmultiwindowwindow.c',
     'winmultiwindowwm.c',
     'winmultiwindowwndproc.c',
     'propertystore.h',
     'winSetAppUserModelID.c',
]
xwin_sys_libs += ['-lshlwapi', '-lole32', '-ldwmapi']

srcs_windows += [
     'winrandr.c',
]

srcs_windows += [
    'InitInput.c',
    'InitOutput.c',
    'winallpriv.c',
    'winauth.c',
    'winblock.c',
    'wincmap.c',
    'winconfig.c',
    'wincreatewnd.c',
    'wincursor.c',
    'windialogs.c',
    'winengine.c',
    'winerror.c',
    'winglobals.c',
    'winkeybd.c',
    'winkeyhook.c',
    'winmisc.c',
    'winmonitors.c',
    'winmouse.c',
    'winmsg.c',
    'winmsgwindow.c',
    'winmultiwindowclass.c',
    'winmultiwindowicons.c',
    'winos.c',
    'winprefs.c',
    'winprocarg.c',
    'winscrinit.c',
    'winshadddnl.c',
    'winshadgdi.c',
    'wintaskbar.c',
    'wintrayicon.c',
    'winvalargs.c',
    'winwakeup.c',
    'winwindow.c',
    'winwndproc.c',
    'ddraw.h',
    'winconfig.h',
    'win.h',
    'winglobals.h',
    'winkeybd.h',
    'winkeynames.h',
    'winlayouts.h',
    'winmessages.h',
    'winmonitors.h',
    'winmsg.h',
    'winms.h',
    'winmultiwindowclass.h',
    'winmultiwindowicons.h',
    'winprefs.h',
    'winresource.h',
    'winwindow.h',
    'windisplay.c',
    'windisplay.h',
    '../../mi/miinitext.c',
    '../../mi/miinitext.h',
]

rsrc = windows.compile_resources(
     'XWin.rc',
     include_directories: include_directories('../../include/'),
     depend_files: ['XWin.exe.manifest', 'X.ico'],
)
srcs_windows += rsrc

lgen = generator(
    exe_flex,
    output: '@PLAINNAME@.yy.c',
    arguments: ['-i', '-o', '@OUTPUT@', '@INPUT@']
)

lfiles = lgen.process('winprefslex.l')
srcs_windows += lfiles

pgen = generator(
    exe_bison,
    output: ['@BASENAME@.c', '@BASENAME@.h'],
    arguments: ['@INPUT@', '--defines=@OUTPUT1@', '--output=@OUTPUT0@']
)

pfiles = pgen.process('winprefsyacc.y')
srcs_windows += pfiles

dep_xwin = [
    dep_common,
    dependency('xcb-aux'),
    dependency('xcb-image'),
    dependency('xcb-ewmh'),
    dependency('xcb-icccm'),
    dependency('xcb-composite'),
]

executable(
    server_name,
    srcs_windows,
    include_directories: [inc, top_dir_inc],
    dependencies: dep_xwin,
    link_with: [
        xwin_windowsdri,
        xwin_glx,
        xwin_clipboard,
        libxserver_fb,
        libxserver,
        libxserver_glx,
        libglxvnd,
        libxserver_xkb_stubs,
        libxserver_miext_shadow,
        libxserver_pseudoramix,
        libxserver_xi_stubs,
    ],
    link_args: ['-Wl,--disable-stdcall-fixup', '-Wl,--export-all-symbols'] +  xwin_sys_libs,
    c_args: xwin_c_args,
    win_subsystem: 'windows',
    install: true,
)

install_data(
    'system.XWinrc',
    install_dir: join_paths(get_option('sysconfdir'), 'X11')
)
