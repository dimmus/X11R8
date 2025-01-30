lib_args = []

f_check += ['strlcat', 'fork', 'closefrom']

if get_option('zfile-open')
  if exe_gzip.found()
    XPM_PATH_GZIP = exe_gzip.full_path()
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

if get_option('sxpm')
  f_check += ['close_range', 'break']
endif

if get_option('zfile-stat')
  lib_args += '-DSTAT_ZFILE'
endif

dep_int_xpm = [libx11, xproto, libxext, libxt]

if dep_gettext.found()
  lib_args += '-DUSE_GETTEXT'
endif

src = files(
  'Attrib.c',
  'CrBufFrI.c',
  'CrBufFrP.c',
  'CrDatFrI.c',
  'CrDatFrP.c',
  'CrIFrBuf.c',
  'CrIFrDat.c',
  'CrIFrP.c',
  'CrPFrBuf.c',
  'CrPFrDat.c',
  'CrPFrI.c',
  'Image.c',
  'Info.c',
  'RdFToBuf.c',
  'RdFToDat.c',
  'RdFToI.c',
  'RdFToP.c',
  'WrFFrBuf.c',
  'WrFFrDat.c',
  'WrFFrI.c',
  'WrFFrP.c',
  'XpmI.h',
  'create.c',
  'data.c',
  'hashtab.c',
  'misc.c',
  'parse.c',
  'rgb.c',
  'scan.c',
)

lib = library('Xpm', src,
  c_args: lib_args,
  include_directories: inc_lib,
  dependencies: dep_int_xpm,
  version: '4.11.0',
  install: true,
)

libxpm = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X Pixmap Library',
  version: ver_xpm,
  filebase: 'xpm',
  requires: 'x11',
)

executable('cxpm', 
  'cxpm/cxpm.c',
  dependencies: dep_int_xpm,
  c_args: lib_args,
  include_directories: inc_lib,
)

if get_option('sxpm')
  executable('sxpm',
    'sxpm/sxpm.c',
    dependencies: dep_int_xpm,
    c_args: lib_args,
    include_directories: inc_lib,
    link_with: lib,
  )
endif