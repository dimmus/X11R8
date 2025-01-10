headers = files(
    'font.h',
    'fontproto.h',
    'fontstruct.h',
    'FS.h',
    'fsmasks.h',
    'FSproto.h',
)

# lib/xfont
headers += files('libxfont2.h')

# lib/fontenc
headers += files('fontenc.h')

# lib/fs
headers += files('FSlib.h')

install_headers(headers,
    subdir: 'X11/fonts',
)