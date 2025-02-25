ver_xfont = '2.0.7'

inc_font_xfont = include_directories(
  '.',
  'bitmap',
  'builtins',
  'fc',
  'fontfile',
  'FreeType',
  'stubs',
  'util',
)

f_check += ['poll', 'readlink', 'strlcat']
h_check += ['endian.h', 'poll.h', 'sys/poll.h', 'err.h', 'float.h']
# TODO: AC_REPLACE_FUNCS([reallocarray realpath strlcat strlcpy])

dep_ext_xfont = [dep_m, dep_freetype2, dep_zlib, dep_bzip2]
dep_int_xfont = [xproto, libfontenc]

conf.set('X_GZIP_FONT_COMPRESSION',  dep_zlib.found())
conf.set('X_BZIP2_FONT_COMPRESSION', dep_bzip2.found())

conf.set('XFONT_PCFFORMAT', true)  # Support pcf format bitmap font files
conf.set('XFONT_BDFFORMAT', true)  # Support bdf format bitmap font files
conf.set('XFONT_SNFFORMAT', false) # Support snf format bitmap font files # TODO: error in linker with xfs
conf.set('XFONT_BITMAP',    true)  # Support bitmap font files
conf.set('XFONT_FC',        true)  # Support the X Font Services Protocol

src = files(
  'stubs/atom.c',
  'stubs/libxfontstubs.c',
  'util/fontaccel.c',
  'util/fontnames.c',
  'util/fontutil.c',
  'util/fontxlfd.c',
  'util/format.c',
  'util/miscutil.c',
  'util/patcache.c',
  'util/private.c',
  'util/utilbitmap.c',
)

src += files(
  'fontfile/bitsource.c',
  'fontfile/bufio.c',
  'fontfile/decompress.c',
  'fontfile/defaults.c',
  'fontfile/dirfile.c',
  'fontfile/fileio.c',
  'fontfile/filewr.c',
  'fontfile/fontdir.c',
  'fontfile/fontencc.c',
  'fontfile/fontfile.c',
  'fontfile/fontscale.c',
  'fontfile/gunzip.c',
  'fontfile/register.c',
  'fontfile/renderers.c',
  'fontfile/catalogue.c',
)

src += files(
  'builtins/dir.c',
  'builtins/file.c',
  'builtins/fonts.c',
  'builtins/fpe.c',
  'builtins/render.c',
)

# if X_BZIP2_FONT_COMPRESSION
src += files(
  'fontfile/bunzip2.c',
)

# if XFONT_FREETYPE
src += files(
  'FreeType/ftenc.c',
  'FreeType/ftfuncs.c',
  'FreeType/fttools.c',
  'FreeType/xttcap.c',
)

# if XFONT_TRUETYPE # XXX: need libx11
# src += files(
#   'TrueType/FontCache.c',
# ) 

# if XFONT_BITMAP
src += files(
  'bitmap/bitmap.c',
  'bitmap/bitmapfunc.c',
  'bitmap/bitmaputil.c',
  'bitmap/bitscale.c',
  'bitmap/fontink.c',
) 

# if XFONT_BDFFORMAT
src += files(
  'bitmap/bdfread.c',
  'bitmap/bdfutils.c',
)

# if XFONT_PCF_OR_BUILTIN
src += files(
  'bitmap/pcfread.c',
)

# if XFONT_PCFFORMAT
src += files(
  'bitmap/pcfwrite.c',
)

# if XFONT_SNFFORMAT
src += files(
  'bitmap/snfread.c',
)

# if XFONT_FC
src += files(
  'fc/fsconvert.c',
  'fc/fserve.c',
  'fc/fsio.c',
  'fc/fstrans.c',
)

# util
src += files(
  'util/strlcat.c',
  'util/strlcpy.c',
  'util/realpath.c',
  'util/reallocarray.c',
)

lib = shared_library('Xfont2', src,
  c_args: '-fvisibility=hidden',
  include_directories: [inc_lib, inc_font_xfont],
  dependencies: [dep_int_xfont, dep_ext_xfont],
  version: '2.0.0',
  install: true,
)

libxfont = declare_dependency(
  link_with: lib,
  include_directories: [inc_lib, inc_font_xfont],
)

pkg.generate(lib,
  name: 'Xfont2',
  description: 'X font Library version 2',
  version: ver_xfont,
  filebase: 'xfont2',
  requires: 'xproto',
  requires_private: ['fontenc', 'freetype', 'zlib']
)
