inc_lib += [
    inc_config,
    include_directories(
        '.',
        'dri',
        'extensions',
        'fonts',
        'ICE',
        'SM',
        'Xaw',
        'Xcursor',
        'Xft',
        'Xmu',
        'Xtrans',
    )
]

subdir('dri')
subdir('extensions')
subdir('fonts')
if get_option('legacy')
subdir('PM')
endif

install_headers(
    'ap_keysym.h',
    'DECkeysym.h',
    'HPkeysym.h',
    'keysymdef.h',
    'keysym.h',
    'Sunkeysym.h',
    'Xalloca.h',
    'Xarch.h',
    'Xatom.h',
    'Xdefs.h',
    'XF86keysym.h',
    'Xfuncs.h',
    'Xfuncproto.h',
    'X.h',
    'Xmd.h',
    'Xosdefs.h',
    'Xos.h',
    'Xos_r.h',
    'Xproto.h',
    'Xprotostr.h',
    'Xthreads.h',
    'Xw32defs.h',
    'XWDFile.h',
    'Xwindows.h',
    'Xwinsock.h',
    subdir: 'X11'
)

# x11
install_headers(
    'XKBlib.h',
    'Xcms.h',
    'Xlib.h',
    'XlibConf.h',
    'Xlibint.h',
    'Xlocale.h',
    'Xresource.h',
    'Xutil.h',
    'cursorfont.h',
    'Xregion.h',
    'ImUtil.h',
    'Xlib-xcb.h',
    subdir: 'X11',
)

# xauth
install_headers(
    'Xauth.h',
    subdir: 'X11',
)

# xdmcp
install_headers(
    'Xdmcp.h',
    subdir: 'X11',
)

# xpm
install_headers(
    'xpm.h',
    subdir: 'X11',
)

# xt
install_headers(
    'Composite.h',
    'CompositeP.h',
    'ConstrainP.h',
    'Constraint.h',
    'Core.h',
    'CoreP.h',
    'Intrinsic.h',
    'IntrinsicP.h',
    'Object.h',
    'ObjectP.h',
    'RectObj.h',
    'RectObjP.h',
    'ResConfigP.h',
    'Shell.h',
    'ShellP.h',
    'StringDefs.h',
    'Vendor.h',
    'VendorP.h',
    'CallbackI.h',
    'ConvertI.h',
    'CreateI.h',
    'EventI.h',
    'HookObjI.h',
    'InitialI.h',
    'IntrinsicI.h',
    'PassivGraI.h',
    'ResourceI.h',
    'SelectionI.h',
    'ShellI.h',
    'ThreadsI.h',
    'TranslateI.h',
    'VarargsI.h',
    'Xtos.h',
    subdir: 'X11',
)

# xshmfence
install_headers(
    'xshmfence.h',
    subdir: 'X11',
)

install_headers(
    'ICE/ICE.h',
    'ICE/ICEconn.h',
    'ICE/ICElib.h',
    'ICE/ICEmsg.h',
    'ICE/ICEproto.h',
    'ICE/ICEutil.h',
    subdir: 'X11/ICE',
)

install_headers(
    'SM/SM.h',
    'SM/SMlib.h',
    'SM/SMproto.h',
    subdir: 'X11/SM',
)

install_headers(
    'Xaw/AllWidgets.h',
    'Xaw/AsciiSink.h',
    'Xaw/AsciiSinkP.h',
    'Xaw/AsciiSrc.h',
    'Xaw/AsciiSrcP.h',
    'Xaw/AsciiText.h',
    'Xaw/AsciiTextP.h',
    'Xaw/Box.h',
    'Xaw/BoxP.h',
    'Xaw/Cardinals.h',
    'Xaw/Command.h',
    'Xaw/CommandP.h',
    'Xaw/Dialog.h',
    'Xaw/DialogP.h',
    'Xaw/Form.h',
    'Xaw/FormP.h',
    'Xaw/Grip.h',
    'Xaw/GripP.h',
    'Xaw/Label.h',
    'Xaw/LabelP.h',
    'Xaw/List.h',
    'Xaw/ListP.h',
    'Xaw/MenuButton.h',
    'Xaw/MenuButtoP.h',
    'Xaw/MultiSrc.h',
    'Xaw/MultiSrcP.h',
    'Xaw/MultiSink.h',
    'Xaw/MultiSinkP.h',
    'Xaw/Paned.h',
    'Xaw/PanedP.h',
    'Xaw/Panner.h',
    'Xaw/PannerP.h',
    'Xaw/Porthole.h',
    'Xaw/PortholeP.h',
    'Xaw/Repeater.h',
    'Xaw/RepeaterP.h',
    'Xaw/Reports.h',
    'Xaw/Scrollbar.h',
    'Xaw/ScrollbarP.h',
    'Xaw/Simple.h',
    'Xaw/SimpleP.h',
    'Xaw/SimpleMenu.h',
    'Xaw/SimpleMenP.h',
    'Xaw/Sme.h',
    'Xaw/SmeP.h',
    'Xaw/SmeBSB.h',
    'Xaw/SmeBSBP.h',
    'Xaw/SmeLine.h',
    'Xaw/SmeLineP.h',
    'Xaw/StripChart.h',
    'Xaw/StripCharP.h',
    'Xaw/Template.c',
    'Xaw/Template.h',
    'Xaw/TemplateP.h',
    'Xaw/Text.h',
    'Xaw/TextP.h',
    'Xaw/TextSink.h',
    'Xaw/TextSinkP.h',
    'Xaw/TextSrc.h',
    'Xaw/TextSrcP.h',
    'Xaw/Tip.h',
    'Xaw/TipP.h',
    'Xaw/Toggle.h',
    'Xaw/ToggleP.h',
    'Xaw/Tree.h',
    'Xaw/TreeP.h',
    'Xaw/VendorEP.h',
    'Xaw/Viewport.h',
    'Xaw/ViewportP.h',
    'Xaw/XawImP.h',
    'Xaw/XawInit.h',
    subdir: 'X11/Xaw',
)

install_headers(
    'Xcursor/Xcursor.h',
    subdir: 'X11/Xcursor',
)

install_headers(
    'Xft/XftCompat.h',
    'Xft/Xft.h',
    subdir: 'X11/Xft',
)

install_headers(
    'Xmu/Xmu.h',
	'Xmu/Atoms.h',
	'Xmu/CharSet.h',
	'Xmu/CloseHook.h',
	'Xmu/Converters.h',
	'Xmu/CurUtil.h',
	'Xmu/CvtCache.h',
	'Xmu/DisplayQue.h',
	'Xmu/Drawing.h',
	'Xmu/Editres.h',
	'Xmu/EditresP.h',
	'Xmu/Error.h',
	'Xmu/ExtAgent.h',
	'Xmu/Initer.h',
	'Xmu/Lookup.h',
	'Xmu/Misc.h',
	'Xmu/StdSel.h',
	'Xmu/StdCmap.h',
	'Xmu/SysUtil.h',
	'Xmu/WidgetNode.h',
	'Xmu/WinUtil.h',
	'Xmu/Xct.h',
	'Xmu/WhitePoint.h',
    subdir: 'X11/Xmu',
)

install_headers(
    'Xtrans/Xtrans.h',
	'Xtrans/Xtrans.c',
	'Xtrans/Xtransint.h',
	'Xtrans/Xtranslcl.c',
	'Xtrans/Xtranssock.c',
	'Xtrans/Xtransutil.c',
	'Xtrans/transport.c',
    subdir: 'X11/Xtrans',
)

# Xpoll.h
fd_set_maybe_headers = [
    'sys/param.h',
    'sys/types.h',
    'sys/time.h',
    'sys/select.h'
]
fd_set_headers = ''
foreach h: fd_set_maybe_headers
    if cc.has_header(h)
        fd_set_headers += '#include <' + h + '>\n'
    endif
endforeach

# generated headers. try not to make more of these, please.
if cc.has_member('fd_set', 'fds_bits', prefix: fd_set_headers)
    fds_bits = 'fds_bits'
elif cc.has_member('fd_set', '__fds_bits', prefix: fd_set_headers)
    fds_bits = '__fds_bits'
else
    error('Your fd_set is too weird.')
endif

xpoll_config = configuration_data()
xpoll_config.set('USE_FDS_BITS', fds_bits)
configure_file(input: 'Xpoll.h.in',
               output: 'Xpoll.h',
               install: true,
               install_dir: dir_include / 'X11',
               configuration: xpoll_config)