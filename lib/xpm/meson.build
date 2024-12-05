ver_xpm = '3.5.17'

inc_xpm = [
  inc_config,
  include_directories('include'),
  include_directories('include/X11'),
  include_directories('src'),
]

lib_args = []

f_check += ['strlcat', 'fork', 'closefrom']

if get_option('open-zfile')
  gzip = find_program('gzip')
  if gzip.found()
    XPM_PATH_GZIP = gzip.full_path()
    conf.set_quoted('XPM_PATH_GZIP', XPM_PATH_GZIP)
  endif

  # TODO: need?
  # compress = find_program('compress', required: false)
  # if compress.found()
  #   XPM_PATH_COMPRESS = compress.full_path()
  # endif

  # uncompress = find_program('uncompress', required: false)
  # if uncompress.found()
  #   XPM_PATH_UNCOMPRESS = uncompress.full_path()
  # endif
  # lib_args += ['-DNO_ZPIPE']
else
  COMPRESSED_PIXMAPS = true
endif

if get_option('build-sxpm')
  f_check += ['close_range', 'break']
endif

if get_option('stat-zfile')
  lib_args += ['-DSTAT_ZFILE']
endif

dep_int_xpm = [libx11, xproto, libxext, libxt]

dep_gettext = dependency('gettext', required: false)
if dep_gettext.found()
  lib_args += ['-DUSE_GETTEXT'] 
endif

src = files(
  'src/Attrib.c',
  'src/CrBufFrI.c',
  'src/CrBufFrP.c',
  'src/CrDatFrI.c',
  'src/CrDatFrP.c',
  'src/CrIFrBuf.c',
  'src/CrIFrDat.c',
  'src/CrIFrP.c',
  'src/CrPFrBuf.c',
  'src/CrPFrDat.c',
  'src/CrPFrI.c',
  'src/Image.c',
  'src/Info.c',
  'src/RdFToBuf.c',
  'src/RdFToDat.c',
  'src/RdFToI.c',
  'src/RdFToP.c',
  'src/WrFFrBuf.c',
  'src/WrFFrDat.c',
  'src/WrFFrI.c',
  'src/WrFFrP.c',
  'src/XpmI.h',
  'src/create.c',
  'src/data.c',
  'src/hashtab.c',
  'src/misc.c',
  'src/parse.c',
  'src/rgb.c',
  'src/scan.c',
)

lib = library('Xpm', src,
  c_args : lib_args,
  include_directories : inc_xpm,
  dependencies : dep_int_xpm,
  version : '4.11.0',
  install : true,
)

executable('cxpm', 'cxpm/cxpm.c',
  dependencies : dep_int_xpm,
  c_args : lib_args,
  include_directories : inc_xpm,
)

if get_option('build-sxpm')
  executable('sxpm',
    'sxpm/sxpm.c',
    dependencies : dep_int_xpm,
    c_args : lib_args,
    include_directories : inc_xpm,
    link_with : lib,
  )
endif

libxpm = declare_dependency(
  link_with : lib,
  include_directories : inc_xpm,
)

meson.override_dependency('xpm', libxpm)

install_headers(
  'include/X11/xpm.h',
  subdir : 'X11',
)

pkg.generate(lib,
  description : 'X Pixmap Library',
  version: ver_xpm,
  filebase : 'xpm',
  requires : 'x11',
)

# subdir('test') # TODO: implement