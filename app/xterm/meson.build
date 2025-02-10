
inc_xterm = include_directories('.')

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

# conf_xterm = configuration_data()

# conf_xterm.set('HAVE_X11_DECKEYSYM_H', 1)	        # X11/DECkeysym.h
# conf_xterm.set('HAVE_X11_EXTENSIONS_XDBE_H', 1)     # X11/extensions/Xdbe.h
# conf_xterm.set('HAVE_X11_EXTENSIONS_XINERAMA_H', 1) # X11/extensions/Xinerama.h
# conf_xterm.set('HAVE_X11_EXTENSIONS_XKB_H', 1)      # X11/extensions/XKB.h
# conf_xterm.set('HAVE_X11_SUNKEYSYM_H', 1)           # X11/Sunkeysym.h
# conf_xterm.set('HAVE_X11_TRANSLATEI_H', 1)          # X11/TranslateI.h
# conf_xterm.set('HAVE_X11_XF86KEYSYM_H', 1)          # X11/XF86keysym.h
# conf_xterm.set('HAVE_X11_XKBLIB_H', 1)	            # X11/XKBlib.h
# conf_xterm.set('HAVE_X11_XPOLL_H', 1)               # X11/Xpoll.h

# conf_xterm.set('HAVE_XKBKEYCODETOKEYSYM', 1)
# conf_xterm.set('HAVE_XKBQUERYEXTENSION', 1)
# conf_xterm.set('HAVE_LIB_XAW', 1)
# conf_xterm.set('HAVE_LIB_XAW3D', 1)
# conf_xterm.set('USE_DOUBLE_BUFFER', 1)

# conf_xterm.set('USE_UTMP_SETGID', 1) # if we should use setgid to access utmp/utmpx
# conf_xterm.set('HAVE_LIB_XCURSOR', 1) # if we expect to use the Xcursor library
# conf_xterm.set('OWN_TERMINFO_ENV', 1) # enable setenv of $TERMINFO value
# conf_xterm.set('NO_ACTIVE_ICON', 1) # disable X11R6.3 active-icon feature
# conf_xterm.set('OPT_ISO_COLORS', 0) # disable ANSI color
# conf_xterm.set('OPT_AIX_COLORS', 0) # disable 16-color support
# conf_xterm.set('OPT_256_COLORS', 1) # enable 256-color support
# conf_xterm.set('OPT_DIRECT_COLOR', 1) # enable direct-color support
# conf_xterm.set('OPT_88_COLORS', 1) # enable 88-color support
# conf_xterm.set('OPT_BLINK_CURS', 0) # disable support for blinking cursor
# conf_xterm.set('OPT_BROKEN_OSC', 0) # allow broken Linux OSC-strings
# conf_xterm.set('OPT_BROKEN_ST', 0) # disallow broken string-terminators
# conf_xterm.set('OPT_BUILTIN_XPMS', 1) # compile-in icon data
# conf_xterm.set('OPT_C1_PRINT', 0) # disallow -k8 option for printable 128-159
# conf_xterm.set('OPT_PC_COLORS', 0) # disable PC-style mapping of bold colors
# conf_xterm.set('OPT_COLOR_CLASS', 0) # disable separate color class resources
# conf_xterm.set('DFT_COLORMODE', 0) # if you want color-mode enabled by default
# conf_xterm.set('OPT_HIGHLIGHT_COLOR', 0) # if you want support for color highlighting
# conf_xterm.set('OPT_DEC_CHRSET', 0) # disable support for double-size chars
# conf_xterm.set('OPT_BOX_CHARS', 0) # disable fallback-support for box chars
# conf_xterm.set('OPT_EXEC_SELECTION', 0) # disable "exec-selection" action
# conf_xterm.set('OPT_EXEC_XTERM', 1) # enable "spawn-new-terminal" action
# conf_xterm.set('OPT_DOUBLE_BUFFER', 1) # enable double-buffering in default resources
# conf_xterm.set('OPT_HP_FUNC_KEYS', 0) # enable support for HP-style function keys
# conf_xterm.set('OPT_SCO_FUNC_KEYS', 0) # enable support for SCO-style function keys
# conf_xterm.set('OPT_SUN_FUNC_KEYS', 0) # disable support for Sun-style function keys
# conf_xterm.set('OPT_I18N_SUPPORT', 0) # disable internationalization
# conf_xterm.set('OPT_INITIAL_ERASE', 0) # disable setup for stty erase
# conf_xterm.set('OPT_INPUT_METHOD', 0) # disable input-method
# conf_xterm.set('OPT_LOAD_VTFONTS', 1) # enable load-vt-fonts() action
# conf_xterm.set('ALLOWLOGGING', 1) # if you want support for logging
# conf_xterm.set('ALLOWLOGFILEEXEC',1) # if you want to allow logging via a pipe
# conf_xterm.set('OPT_MAXIMIZE', 0) # disable actions for iconify/deiconify/maximize/restore
# conf_xterm.set('OPT_NUM_LOCK', 0) # disable NumLock keypad support
# conf_xterm.set('OPT_PASTE64', 1) # disable get/set base64 selection data
# conf_xterm.set('OPT_PTY_HANDSHAKE', 1) # disable pty-handshake support
# conf_xterm.set('OPT_READLINE', 1) # enable support for mouse in readline applications
# conf_xterm.set('OPT_SELECT_REGEX', 1) # enable regular-expression selections
# conf_xterm.set('SCROLLBAR_RIGHT', 1) # enable right-scrollbar support
# conf_xterm.set('OPT_SAME_NAME', 0) # disable check for redundant name-change
# conf_xterm.set('OPT_SELECTION_OPS', 0) # disable selection-action operations
# conf_xterm.set('OPT_SESSION_MGT', 0) # disable support for session management
# conf_xterm.set('OPT_STATUS_LINE', 1) # enable support for status-line
# conf_xterm.set('OPT_TCAP_FKEYS', 0) # disable termcap function-keys support
# conf_xterm.set('OPT_TCAP_QUERY', 0) # disable compiled-in termcap-query support
# conf_xterm.set('OPT_TEK4014', 0) # disable tek4014 emulation
# conf_xterm.set('OPT_TOOLBAR', 1) # compile-in toolbar for pulldown menus
# conf_xterm.set('OPT_VT52_MODE', 0) # disable VT52 emulation
# conf_xterm.set('OPT_WIDE_ATTRS', 0) # disable rarely-used SGR features
# conf_xterm.set('OPT_WIDER_ICHAR', 0) # enable 16-bit character support
# conf_xterm.set('OPT_MINI_LUIT', 1) # enable mini-luit (built-in Latin9 support)
# conf_xterm.set('OPT_LUIT_PROG', 1) # enable luit filter (Unicode translation)
# conf_xterm.set('OPT_WIDE_CHARS', 1) # enable wide-character support
# conf_xterm.set('OPT_DABBREV', 1) # enable dynamic-abbreviation support
# conf_xterm.set('OPT_DEC_LOCATOR', 1) # enable DECterm Locator support
# conf_xterm.set('OPT_SCREEN_DUMPS', 0) # disable XHTML and SVG screen dump support
# conf_xterm.set('OPT_REGIS_GRAPHICS', 1) # enable ReGIS graphics support
# conf_xterm.set('OPT_SIXEL_GRAPHICS', 1) # enable sixel graphics support
# conf_xterm.set('OPT_GRAPHICS',1) # if any graphics mode is enabled
# conf_xterm.set('OPT_PRINT_GRAPHICS', 1) # enable screen dump to sixel support
# conf_xterm.set('OPT_DEC_RECTOPS', 0) # disable VT420 rectangle support
# conf_xterm.set('OPT_ZICONBEEP', 0) # disable -ziconbeep option
# conf_xterm.set('OPT_TRACE', 1) # enable debugging traces
# conf_xterm.set('OPT_XMC_GLITCH', 1) # enable xmc magic-cookie emulation
# conf_xterm.set('DISABLE_SETUID', 1) # if you want to disable setuid

# conf_xterm.set_quoted('DFT_DECID', 'vt420')
# conf_xterm.set_quoted('DFT_TERMTYPE', 'xterm')
# conf_xterm.set_quoted('OWN_TERMINFO_DIR', '/usr/lib/terminfo') # Define to override default TERMINFO value
# conf_xterm.set_quoted('PROCFS_ROOT', '/proc') # This is defined via the --enable-exec-xterm option

# configure_file(
#   output: 'config_xterm.h',
#   configuration: conf_xterm
# )

# TERMLIB="termlib ncursesw ncurses curses"
dep_ext_xterm = [dep_freetype2, dep_fontconfig, dependency('ncurses')]

dep_int_xterm = [
    xproto,
    libxaw,
    libx11,
    libxext,
    libxt,
    libxmu,
    libxpm,
    libice,
    libxft,
    libxinerama,
    libxkb,
]

src = files(
    'button.c',
    'cachedGCs.c',
    'charproc.c',
    'charsets.c',
    'charclass.c',
    'cursor.c',
    'data.c',
    'doublechr.c',
    'fontutils.c',
    'graphics.c',
    'graphics_sixel.c',
    'html.c',
    'input.c',
    'linedata.c',
    'main.c',
    'menu.c',
    'misc.c',
    'print.c',
    'precompose.c',
    'ptydata.c',
    'screen.c',
    'scrollback.c',
    'scrollbar.c',
    'svg.c',
    'tabs.c',
    'util.c',
    'version.c',
    'VTPrsTbl.c',
    'wcwidth.c',
    'xstrings.c',
    'xtermcap.c',
)

executable('xterm', src,
    include_directories: [inc_xterm, inc_lib],
    dependencies: [dep_ext_xterm, dep_int_xterm],
    install: true,
)