ver_xclock = '1.1.1'

f_check += ['strlcpy', 'getpid', 'nl_langinfo']

conf.set('XRENDER',     1) # Use Xft2 and Xrender for rendering
conf.set('XFREE86_FT2', 1)
conf.set('HAVE_SINCOS', 1)
conf.set('XKB',         1) # Use XKB to sound bells

dep_ext_xclock = [dep_m, dep_freetype2]
dep_int_xclock = [libxaw, libxmu, libx11, xproto, libxft, libxrender, libxt, libxkbfile]

src = files(
    'Clock.c',
    'xclock.c',
)

executable('xclock', src,
    dependencies: [dep_int_xclock, dep_ext_xclock],
    install: true,
)