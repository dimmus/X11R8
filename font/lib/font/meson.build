ver_xfont = '2.0.7'

inc_font_xfont = include_directories(
  'include',
  'include' / 'X11',
  'include' / 'X11' / 'fonts',
  'src' / 'bitmap',
  'src' / 'builtins',
  'src' / 'fc',
  'src' / 'fontfile',
  'src' / 'FreeType',
  'src' / 'stubs',
  'src' / 'util',
)

lib_args = ['-fvisibility=hidden']

f_check += ['poll', 'readlink', 'strlcat']
h_check += ['endian.h', 'poll.h', 'sys/poll.h', 'err.h', 'float.h']
# TODO: AC_REPLACE_FUNCS([reallocarray realpath strlcat strlcpy])

dep_ext_xfont = [dep_m, dep_freetype2, dep_zlib, dep_bzip2]
dep_int_xfont = [xproto, libfontenc]

if dep_zlib.found()
  conf.set('X_GZIP_FONT_COMPRESSION', 1)
endif

if dep_bzip2.found()
  conf.set('X_BZIP2_FONT_COMPRESSION', 1)
endif
conf.set('XFONT_BUILTINS', 1)  # Support built-in fonts
conf.set('XFONT_PCFFORMAT', 1) # Support pcf format bitmap font files
conf.set('XFONT_BDFFORMAT', 1) # Support bdf format bitmap font files
conf.set('XFONT_SNFFORMAT', false) # Support snf format bitmap font files # TODO: error in linker with xfs, so set FALSE for now
conf.set('XFONT_BITMAP', 1)    # Support bitmap font files
conf.set('XFONT_FONTFILE', 1)  # Support fonts in files
conf.set('XFONT_FC', 1)        # Support the X Font Services Protocol

# TODO: implement for Windows
# [AC_LANG_SOURCE([[
#   #if defined(__CYGWIN__) || defined(__MINGW32__)
#   #error No visibility support
#   #endif
#   extern __attribute__((__visibility__("default"))) int x;
# ]])],

src = files(
  'src/stubs/atom.c',
  'src/stubs/libxfontstubs.c',
  'src/util/fontaccel.c',
  'src/util/fontnames.c',
  'src/util/fontutil.c',
  'src/util/fontxlfd.c',
  'src/util/format.c',
  'src/util/miscutil.c',
  'src/util/patcache.c',
  'src/util/private.c',
  'src/util/utilbitmap.c',
)

# if XFONT_FONTFILE
src += files(
  'src/fontfile/bitsource.c',
  'src/fontfile/bufio.c',
  'src/fontfile/decompress.c',
  'src/fontfile/defaults.c',
  'src/fontfile/dirfile.c',
  'src/fontfile/fileio.c',
  'src/fontfile/filewr.c',
  'src/fontfile/fontdir.c',
  'src/fontfile/fontencc.c',
  'src/fontfile/fontfile.c',
  'src/fontfile/fontscale.c',
  'src/fontfile/gunzip.c',
  'src/fontfile/register.c',
  'src/fontfile/renderers.c',
  'src/fontfile/catalogue.c',
)

# if X_BZIP2_FONT_COMPRESSION
src += files(
  'src/fontfile/bunzip2.c',
)

# if XFONT_FREETYPE
src += files(
  'src/FreeType/ftenc.c',
  'src/FreeType/ftfuncs.c',
  'src/FreeType/fttools.c',
  'src/FreeType/xttcap.c',
) 

# if XFONT_BITMAP
src += files(
  'src/bitmap/bitmap.c',
  'src/bitmap/bitmapfunc.c',
  'src/bitmap/bitmaputil.c',
  'src/bitmap/bitscale.c',
  'src/bitmap/fontink.c',
) 

# if XFONT_BDFFORMAT
src += files(
  'src/bitmap/bdfread.c',
  'src/bitmap/bdfutils.c',
)

# if XFONT_PCF_OR_BUILTIN
src += files(
  'src/bitmap/pcfread.c',
)

# if XFONT_PCFFORMAT
src += files(
  'src/bitmap/pcfwrite.c',
)

# if XFONT_SNFFORMAT
src += files(
  'src/bitmap/snfread.c',
)

# if XFONT_BUILTINS
src += files(
  'src/builtins/dir.c',
  'src/builtins/file.c',
  'src/builtins/fonts.c',
  'src/builtins/fpe.c',
  'src/builtins/render.c',
)

# if XFONT_FC
src += files(
  'src/fc/fsconvert.c',
  'src/fc/fserve.c',
  'src/fc/fsio.c',
  'src/fc/fstrans.c',
)

# util
src += files(
  'src/util/strlcat.c',
  'src/util/strlcpy.c',
  'src/util/realpath.c',
  'src/util/reallocarray.c',
)

lib_xfont = library('Xfont', src,
  c_args: lib_args,
  include_directories: [inc_font, inc_font_xfont, inc_x11],
  dependencies: [dep_int_xfont, dep_ext_xfont],
  version: '2.0.0',
  install: true,
)

libxfont = declare_dependency(
  link_with: lib_xfont,
  include_directories: [inc_font, inc_font_xfont, inc_x11],
)

install_headers(
  'include/X11/fonts/libxfont2.h',
  subdir: 'X11/Xfont',
)

pkg.generate(lib,
  name: 'Xfont2',
  description: 'X font Library version 2',
  version: ver_xfont,
  filebase: 'xfont2',
  requires: 'xproto',
  requires_private: ['fontenc', 'freetype', 'zlib']
)
