srcs_windows_dri = [
    'windowsdri.c',
    'windowsdri.h',
]

xwin_windowsdri = static_library(
    'WindowsDRI',
    srcs_windows_dri,
    include_directories: [ inc_server, include_directories('../') ],
    dependencies: dep_pixman,
)
