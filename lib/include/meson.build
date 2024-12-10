inc_lib += [
    inc_config,
    include_directories('.'),
    include_directories('X11'),
    include_directories('X11' / 'ICE'),
    include_directories('X11' / 'SM'),
    include_directories('X11' / 'extensions'),
]

install_headers(
    files(
        'X11/ICE/ICE.h',
        'X11/ICE/ICEconn.h',
        'X11/ICE/ICElib.h',
        'X11/ICE/ICEmsg.h',
        'X11/ICE/ICEproto.h',
        'X11/ICE/ICEutil.h',
    ),
    subdir : 'X11/ICE',
)


install_headers(
    files(
        'X11/SM/SM.h',
        'X11/SM/SMlib.h',
        'X11/SM/SMproto.h',
    ),
    subdir : 'X11/SM',
)

install_headers(
    files(
        'X11/XKBlib.h',
        'X11/Xcms.h',
        'X11/Xlib.h',
        'X11/Xlibint.h',
        'X11/Xlocale.h',
        'X11/Xresource.h',
        'X11/Xutil.h',
        'X11/cursorfont.h',
        'X11/Xregion.h',
        'X11/ImUtil.h',
        'X11/Xlib-xcb.h',
    ),
    subdir : 'X11',
)


install_headers(
    'X11/Xauth.h',
    subdir : 'X11',
)