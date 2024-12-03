project('xorg', 'c', 
    license : 'MIT', 
    version : '21.1.99.1', # xserver
    meson_version : '>=0.59.0',
    # 0.56.0
    # 0.58.0: {'format strings'}
    # 0.59.0: {'feed arg in custom_target'}
    # 0.62.0: {'dep 'dl' custom lookup'}
)

add_project_arguments(
  '-DHAVE_CONFIG_H',
  '-D_GNU_SOURCE',
  '-D_XOPEN_SOURCE', # xfont
  '-D__EXTENSIONS__',
  '-D_CONST_X_STRING',
  '-D_DEFAULT_SOURCE',
  '-DHAVE_DIX_CONFIG_H',
  language : 'c'
)

add_project_link_arguments(
  '-fvisibility=hidden',
  '-fno-strict-aliasing',
  language : 'c'
)

cc = meson.get_compiler('c')

dir_prefix  = get_option('prefix')
# dir_sysconf = dir_prefix / get_option('sysconfdir')
dir_bin     = dir_prefix / get_option('bindir')
dir_data    = dir_prefix / get_option('datadir')
dir_include = dir_prefix / get_option('includedir')
dir_lib     = dir_prefix / get_option('libdir')
dir_man     = dir_prefix / get_option('mandir')

dep_m  = cc.find_library('m',  required : false) # libxcvt
dep_dl = cc.find_library('dl', required : false) # xvmc, xserver

WITH_UNIT_TESTS = false

python = import('python').find_installation()
pkg = import('pkgconfig')

conf = configuration_data()
inc_config = include_directories('.')

f_check = []
h_check = []

inc_x11 = []
inc_lib = []
inc_fonts = []

subdir('include')
subdir('proto')
subdir('lib' / 'xtrans')
subdir('fonts') # <- xtrans
subdir('lib' / 'x11')
subdir('lib' / 'xau')
subdir('lib' / 'xdmcp')
subdir('lib' / 'ice')
subdir('lib' / 'sm')
subdir('lib' / 'xt')
subdir('lib' / 'xcvt')
subdir('extensions' / 'xrender')
subdir('lib' / 'xft') # <- xrender
subdir('extensions' / 'xfixes')
subdir('lib' / 'xcursor') # <- xrender, xfixes
subdir('extensions' / 'xext')
subdir('lib' / 'xpm') # <- xext
subdir('lib' / 'xmu') # <- xext
subdir('lib' / 'xaw') # <- xext
# subdir('xaw3d')
subdir('extensions')
subdir('server')

MESON_NEWER_053 = meson.version().version_compare('>=0.53.0')
MESON_NEWER_056 = meson.version().version_compare('>=0.56.0')

if MESON_NEWER_056
    dir_build  = meson.project_build_root()
    dir_source = meson.project_source_root()
else
    dir_build  = meson.build_root()
    dir_source = meson.source_root()
endif

FIRST_RUN = false
if MESON_NEWER_053
  fs = import('fs')
  FIRST_RUN = not fs.is_dir(dir_build / 'src')
endif

# switch that off when run meson reconfigure
if (FIRST_RUN and MESON_NEWER_053) or not MESON_NEWER_053
  f_unique = []
  foreach f : f_check
    if not f_unique.contains(f)
      conf.set('HAVE_@0@'.format(f.to_upper()), cc.has_function(f))
      if f == 'arc4random_buf'
        h_check += ['sys/random.h']
      endif
      f_unique += f
    endif
  endforeach

  # TODO: sort h_check to check only unique headers 
  h_unique = []
  foreach h : h_check
    if not h_unique.contains(h)
      conf.set('HAVE_@0@'.format(h.underscorify().to_upper()), cc.has_header(h))
      h_unique += h
    endif
  endforeach

  # strcasecmp is spelled '_stricmp' on Windows
  if not cc.has_function('strcasecmp')
    if cc.has_function('_stricmp')
      conf.set('strcasecmp', '_stricmp', description: 'Replacement for strcasecmp, if necessary')
    else
      error('strcasecmp (or _stricmp) is mandatory')
    endif
  endif
endif

## from extension/xkbfile
conf.set('HAVE_REALLOCF', cc.has_function('reallocf'))
conf.set('HAVE_STRNDUP', cc.has_function('strndup') and cc.has_header_symbol('string.h', 'strndup'))
conf.set('HAVE_UNLOCKED_STDIO', cc.has_function('getc_unlocked'))

configure_file(
  output: 'config.h',
  configuration: conf
)