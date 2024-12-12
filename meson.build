project('X Window System', 'c', 
    license: 'MIT', 
    version: '11.8.1',
    meson_version: '>=0.59.0',
    # 0.56.0
    # 0.58.0: {'format strings'}
    # 0.59.0: {'feed arg in custom_target'}
    # 0.62.0: {'dep 'dl' custom lookup'}
)

cc = meson.get_compiler('c')

# if cc.get_id() == 'gcc' or cc.get_id() == 'clang'
#     test_wflags = [
#         '-Wall',
#         '-Wpointer-arith',
#         '-Wmissing-declarations',
#         '-Wformat=2',
#         '-Wstrict-prototypes',
#         '-Wmissing-prototypes',
#         '-Wnested-externs',
#         '-Wbad-function-cast',
#         '-Wold-style-definition',
#         '-Wunused',
#         '-Wuninitialized',
#         '-Wshadow',
#         '-Wmissing-noreturn',
#         '-Wmissing-format-attribute',
#         '-Wredundant-decls',
#         '-Werror=implicit',
#         '-Werror=nonnull',
#         '-Werror=init-self',
#         '-Werror=main',
#         '-Werror=missing-braces',
#         '-Werror=sequence-point',
#         '-Werror=return-type',
#         '-Werror=trigraphs',
#         '-Werror=array-bounds',
#         '-Werror=write-strings',
#         '-Werror=address',
#         '-Werror=int-to-pointer-cast',
#         '-Werror=pointer-to-int-cast',
#     ]
# else
    test_wflags = []
# endif

common_wflags = cc.get_supported_arguments(test_wflags)

add_project_arguments(common_wflags, language: 'c')

add_project_arguments(
  '-DHAVE_CONFIG_H',
  '-D_GNU_SOURCE',
  '-D_XOPEN_SOURCE', # xfont
  '-D__EXTENSIONS__',
  '-D_CONST_X_STRING',
  '-D_DEFAULT_SOURCE',
  '-DHAVE_DIX_CONFIG_H',
  language: 'c'
)

add_project_link_arguments(
  '-fvisibility=hidden',
  '-fno-strict-aliasing',
  language: 'c'
)

dir_prefix  = get_option('prefix')
dir_bin     = dir_prefix / get_option('bindir')
dir_data    = dir_prefix / get_option('datadir')
dir_include = dir_prefix / get_option('includedir')
dir_lib     = dir_prefix / get_option('libdir')
dir_man     = dir_prefix / get_option('mandir')

dir_build  = meson.project_build_root()
dir_source = meson.project_source_root()

dep_m           = cc.find_library('m',  required: false) # libxcvt
dep_dl          = cc.find_library('dl', required: false) # xvmc, xserver
dep_zlib        = dependency('zlib') # xfont
dep_bzip2       = dependency('bzip2') # xfont
dep_freetype2   = dependency('freetype2') # xfont
dep_zlib        = dependency('zlib') # fontenc
dep_xcb         = dependency('xcb', version: '>= 1.11.1') # x11
dep_uuid        = dependency('uuid', required: false) # sm
dep_freetype2   = dependency('freetype2', version: '>= 2.1.6') # xft
dep_fontconfig  = dependency('fontconfig', version: '>= 2.5.92') # xft

WITH_UNIT_TESTS = false

python = import('python').find_installation()
pkg    = import('pkgconfig')

conf = configuration_data()
inc_config = include_directories('.')

f_check  = []
h_check  = []
inc_ext  = []
inc_x11  = []
inc_lib  = []
inc_font = []

# lib
ver_ice      = '1.1.1'
ver_sm       = '1.2.4'
ver_x11      = '1.8.10'
ver_xau      = '1.0.11'
ver_xaw      = '1.0.16'
ver_xcursor  = '1.2.3'
ver_xcvt     = '0.1.2'
ver_xdmcp    = '1.1.5'
ver_xft      = '2.3.8'
ver_xmu      = '1.2.1'
ver_xpm      = '3.5.17'
ver_xt       = '1.3.0'
ver_xtrans   = '1.5.1'

# ext
ver_dmx      = '1.1.5'
ver_xcomposite = '0.4.6'
ver_xdamage  = '1.1.6'
ver_xext     = '1.3.6'
ver_xf86dga  = '1.1.6'
ver_xf86vm   = '1.1.5'
ver_xfixes   = '6.0.1'
ver_xi       = '1.8.2'
ver_xinerama = '1.1.5'
ver_xkbfile  = '1.1.3'
ver_xrandr   = '1.5.4'
ver_xrender  = '0.9.11'
ver_xres     = '1.2.2'
ver_xss      = '1.2.4'
ver_xtst     = '1.2.5'
ver_xv       = '1.0.12'
ver_xvmc     = '1.0.14'

ver_xserver  = '21.1.99.1'

subdir('include')
subdir('proto')
subdir('lib' / 'include')
subdir('lib' / 'src' / 'xtrans')
subdir('font') # <- xtrans
subdir('lib' / 'src' / 'x11')
subdir('lib' / 'src' / 'xau')
subdir('lib' / 'src' / 'xdmcp')
subdir('lib' / 'src' / 'ice')
subdir('lib' / 'src' / 'sm')
subdir('lib' / 'src' / 'xt')
subdir('lib' / 'src' / 'xcvt')
subdir('extension' / 'lib' / 'xrender')
subdir('extension' / 'lib' / 'xfixes')
subdir('extension' / 'lib' / 'xext')
subdir('lib' / 'src' / 'xft')     # <- xrender
subdir('lib' / 'src' / 'xcursor') # <- xrender, xfixes
subdir('lib' / 'src' / 'xpm')     # <- xext
subdir('lib' / 'src' / 'xmu')     # <- xext
subdir('lib' / 'src' / 'xaw')     # <- xext
# subdir('lib' / 'src' / 'xaw3d')   # TODO: implement 
subdir('lib' / 'test')
subdir('lib' / 'example')
subdir('extension')
subdir('server')

fs = import('fs')
FIRST_RUN = not fs.is_dir(dir_build / 'src')

# speed up when run meson reconfigure
if FIRST_RUN
  f_unique = []
  foreach f: f_check
    if not f_unique.contains(f)
      conf.set('HAVE_@0@'.format(f.to_upper()), cc.has_function(f))
      if f == 'arc4random_buf'
        h_check += ['sys/random.h']
      endif
      f_unique += f
    endif
  endforeach

  h_unique = []
  foreach h: h_check
    if not h_unique.contains(h)
      conf.set('HAVE_@0@'.format(h.underscorify().to_upper()), cc.has_header(h))
      h_unique += h
    endif
  endforeach

  if not cc.has_function('strcasecmp')
    if cc.has_function('_stricmp')
      conf.set('strcasecmp', '_stricmp', description: 'Replacement for strcasecmp, if necessary')
    else
      error('strcasecmp (or _stricmp) is mandatory')
    endif
  endif
endif

## extension/xkbfile
conf.set('HAVE_REALLOCF', cc.has_function('reallocf'))
conf.set('HAVE_STRNDUP', cc.has_function('strndup') and cc.has_header_symbol('string.h', 'strndup'))
conf.set('HAVE_UNLOCKED_STDIO', cc.has_function('getc_unlocked'))

configure_file(
  output: 'config.h',
  configuration: conf
)