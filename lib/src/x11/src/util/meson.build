makekeys_exe = executable('makekeys', 'makekeys.c',
  include_directories : inc_config,
  install: false
)

# if meson.is_cross_build()
#   _makekeys_exe = find_program('makekeys', native : true)
# else
#   _makekeys_exe = makekeys_exe
# endif

# makekeys = [_makekeys_exe]

# Usage:
# ./src/util/makekeys \
#     /usr/include/X11/keysymdef.h \
#     /usr/include/X11/XF86keysym.h \
#     /usr/include/X11/Sunkeysym.h \
#     /usr/include/X11/DECkeysym.h \
#     /usr/include/X11/HPkeysym.h > ks_tables_h