inc_lib += [
    inc_config,
    include_directories('.'),
    include_directories('X11'),
    include_directories('X11/ICE'),
    include_directories('X11/SM'),
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