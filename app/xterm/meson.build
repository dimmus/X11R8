f_check += [
    'wcwidth',
    'wcswidth',
    'waitpid',
    'use_extended_names',
    'unsetenv',
    'tigetstr',
    'tcgetattr',
    'strftime',
    'setpgid',
    'sched_yield',
    'putenv',
    'mkdtemp',
    'initgroups',
    'endusershell',
    'gethostname',
    'getlogin',
    'getusershell',
]

h_check += [
    'ncurses/curses.h',
    'ncurses/term.h',
    'stdlib.h',
    'sys/ttydefaults.h',
    'termcap.h',
    'termios.h',
    'term.h',
    'unistd.h',
    'wchar.h',
]

conf.set('HAVE_X11_DECKEYSYM_H', 1)	          # X11/DECkeysym.h
conf.set('HAVE_X11_EXTENSIONS_XDBE_H', 1)     # X11/extensions/Xdbe.h
conf.set('HAVE_X11_EXTENSIONS_XINERAMA_H', 1) # X11/extensions/Xinerama.h
conf.set('HAVE_X11_EXTENSIONS_XKB_H', 1)      # X11/extensions/XKB.h
conf.set('HAVE_X11_SUNKEYSYM_H', 1)           # X11/Sunkeysym.h
conf.set('HAVE_X11_TRANSLATEI_H', 1)          # X11/TranslateI.h
conf.set('HAVE_X11_XF86KEYSYM_H', 1)          # X11/XF86keysym.h
conf.set('HAVE_X11_XKBLIB_H', 1)	          # X11/XKBlib.h
conf.set('HAVE_X11_XPOLL_H', 1)               # X11/Xpoll.h

conf.set('HAVE_XKBKEYCODETOKEYSYM', 1)
conf.set('HAVE_XKBQUERYEXTENSION', 1)

conf.set_quoted('DFT_TERMTYPE', 'xterm')

dep_int_xterm = [xproto, libxaw, libx11]

conf.set('OPT_TOOLBAR', 1)
conf.set('HAVE_LIB_XAW', 1)

src = files(
    'button.c',
    'cachedGCs.c',
    'charproc.c',
    'charsets.c',
    'cursor.c',
    'data.c',
    'doublechr.c',
    'fontutils.c',
    'input.c',
    'linedata.c',
    'main.c',
    'menu.c',
    'misc.c',
    'print.c',
    'ptydata.c',
    'scrollback.c',
    'screen.c',
    'scrollbar.c',
    'tabs.c',
    'util.c',
    'version.c',
    'xstrings.c',
    'xtermcap.c',
    'VTPrsTbl.c',
)

executable('xterm', src,
    include_directories: inc_config,
    dependencies: dep_int_xterm,
    install: true,
)