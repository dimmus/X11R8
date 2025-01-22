project('X Window System', 'c', 
    license: 'MIT', 
    version: '11.8.1',
    default_options : [
      'buildtype=debug', # plain,debug,debugoptimized,release,minsize,custom
      # 'optimization=g',  # 0,g,1,2,3,s
      # 'b_sanitize=none   # none,address,thread,undefined,memory,leak,address,undefined',
      # 'b_coverage=true',
      # 'b_lto=false',
      # 'b_lto_threads=32',
      # 'b_staticpic=true', 
      # 'b_pie=false',
      # 'b_lundef=true',
      'c_std=gnu99' # we use typeof in server
    ],
    meson_version: '>=0.59.0',
    # 0.56.0
    # 0.58.0: {'format strings'}
    # 0.59.0: {'feed arg in custom_target'}
    # 0.62.0: {'dep 'dl' custom lookup'}
)

cc = meson.get_compiler('c')

if get_option('buildtype').startswith('debug')
  if cc.get_id() == 'gcc' or cc.get_id() == 'clang'
    test_wflags = [
      '-Wincompatible-pointer-types',
      '-Wpointer-arith',
      '-Wuninitialized',
      '-Werror=implicit',
      '-Werror=nonnull',
      '-Werror=init-self',
      '-Werror=main',
      '-Werror=missing-braces',
      '-Werror=sequence-point',
      '-Werror=return-type',
      '-Werror=trigraphs',
      '-Werror=array-bounds',
      # '-Werror=write-strings', # initialization discards ‘const’ qualifier from pointer target type
      '-Werror=address',
      '-Werror=int-to-pointer-cast',
      '-Werror=pointer-to-int-cast',
    ]
  endif
else
  test_wflags = [
    '-Wno-use-after-free',
    '-Wno-stringop-truncation',
    '-Wno-maybe-uninitialized',
    '-Wno-unused-result',
    '-Wno-format-truncation',
    '-Wno-alloc-size-larger-than=',
    '-Wno-stringop-overflow',
    '-Wno-strict-aliasing',
    '-Wno-array-bounds',
    '-Wno-stringop-overread',
  ]
endif

add_project_arguments(
  cc.get_supported_arguments(test_wflags), 
  language: 'c'
)

add_project_arguments(
  '-DHAVE_CONFIG_H',
  '-D_GNU_SOURCE',
  '-D_BSD_SOURCE',
  '-D_XOPEN_SOURCE', # xfont
  '-D__EXTENSIONS__',
  '-D_CONST_X_STRING',
  '-D_DEFAULT_SOURCE',
  '-DHAVE_DIX_CONFIG_H',
  '-D__USE_MISC', # test/xfont (used if HAVE_REALPATH true)
  '-D__USE_XOPEN_EXTENDED', # test/xfont (used if HAVE_REALPATH true)
  language: 'c'
)

add_project_link_arguments(
  '-fvisibility=hidden',
  '-fno-strict-aliasing',
  language: 'c'
)

WITH_SUMMARY = get_option('show_summary')
if WITH_SUMMARY
summary_dir  = {}
summary_lib  = {}
summary_info = {}
summary_mem  = {}
summary_srv  = {}
summary_org  = {}
summary_xwl  = {}
endif

dir_prefix       = get_option('prefix')
dir_bin          = dir_prefix / get_option('bindir')
dir_data         = dir_prefix / get_option('datadir')
dir_include      = dir_prefix / get_option('includedir')
dir_lib          = dir_prefix / get_option('libdir')
dir_man          = dir_prefix / get_option('mandir')
dir_sysconf      = dir_prefix / get_option('sysconfdir')
dir_libexec      = dir_prefix / get_option('libexecdir')
dir_headers      = dir_lib / get_option('module_dir') # drivers
dir_xorg_module  = dir_include / 'xorg' # drivers
dir_xorg_conf    = dir_data / 'X11' / 'xorg.conf.d' # drivers

dir_build        = meson.project_build_root()
dir_source       = meson.project_source_root()

WITH_UNIT_TESTS  = false
WITH_FONT_SERVER = get_option('build-font-server')
WITH_TESTS       = get_option('build-tests')
WITH_DOC         = get_option('build-docs')
WITH_DOC_MAN     = get_option('build-docs-man')
WITH_INT_PIXMAN  = get_option('use-builtin-pixman')
WITH_INT_EPOXY   = get_option('use-builtin-epoxy')
WITH_DEMOS       = get_option('build-demos')
WITH_DTRACE      = get_option('dtrace')
WITH_XTHREADS    = true
WITH_XTHREADS_DBG = false

dep_m            = cc.find_library('m',         required: get_option('driver_video_intel')) # libxcvt
dep_dl           = cc.find_library('dl',        required: false) # xvmc, xserver,static/epoxy

dep_zlib         = dependency('zlib',           required: false) # xfont, fontenc
dep_bzip2        = dependency('bzip2',          required: false) # xfont
dep_freetype2    = dependency('freetype2',      required: false) # xfont, xft
dep_fontconfig   = dependency('fontconfig',     required: false, version: '>= 2.5.92') # xft
dep_uuid         = dependency('uuid',           required: false) # sm
dep_gettext      = dependency('gettext',        required: false) # xpm
# xserver
dep_null         = dependency('',               required: false)
dep_pixman       = dependency('pixman-1',       required: not WITH_INT_PIXMAN)
dep_libbsd       = dependency('libbsd-overlay', required: false)
dep_xkbcomp      = dependency('xkbcomp',        required: false)
dep_dbus         = dependency('dbus-1',         required: get_option('systemd_logind') == 'true', version: '>= 1.0')
dep_fontutil     = dependency('fontutil',       required: false)
dep_drm          = dependency('libdrm',         required: true, version: '>= 2.4.116') # server/hw/xfree86, driver/video/intel
dep_gl           = dependency('gl',             required: true, version: '>= 1.2') # server/glx, static/epoxy
dep_gbm          = dependency('gbm',            required: true) # server/glamor
dep_epoxy        = dependency('epoxy',          required: not WITH_INT_EPOXY) # server/glamor
dep_pciaccess    = dependency('pciaccess',      required: get_option('pciaccess'), version: '>= 0.12.901') # server/hw/xfree86
dep_systemd      = dependency('libsystemd',     required: false, version: '>= 209') # server
dep_libunwind    = dependency('libunwind',      required: get_option('libunwind')) # server
dep_dri          = dependency('dri',            required: true) # server, driver/video/intel

# static
dep_threads      = dependency('threads',        required: get_option('driver_video_intel')) # pixman, driver/video/intel
dep_openmp       = dependency('openmp',         required: get_option('openmp')) # pixman
dep_egl          = dependency('egl',            required: WITH_INT_EPOXY) # epoxy
dep_gles2        = dependency('glesv2',         required: WITH_INT_EPOXY) # epoxy
dep_gles1        = dependency('glesv1_cm',      required: false) # epoxy

# drivers
dep_udev         = dependency('libudev',        required: false) # input/evdev
dep_evdev        = dependency('libevdev',       required: false) # input/evdev
dep_input        = dependency('libinput',       required: true, version: '>= 1.11.0') # input/libinput

exe_bison        = find_program('bison',        required: false)
exe_flex         = find_program('flex',         required: false)
exe_gzip         = find_program('gzip',         required: false)
exe_awk          = find_program('awk',          required: false)
exe_dtrace       = find_program('dtrace',       required: WITH_DTRACE)
exe_python       = find_program('python3',      required: false)
exe_mig          = find_program('mig',          required: false) # xquarz, mach interface

python           = import('python').find_installation()
pkg              = import('pkgconfig')
fs               = import('fs')

conf             = configuration_data()

inc_config       = include_directories('.')

f_check          = []
h_check          = []

inc_font         = []
inc_lib          = []
inc_xcb          = []
inc_server       = []
inc_static       = []

# libraries
ver_ice          = '1.1.1'
ver_sm           = '1.2.4'
ver_x11          = '1.8.10'
ver_xau          = '1.0.11'
ver_xaw          = '1.0.16'
ver_xcursor      = '1.2.3'
ver_xcvt         = '0.1.2'
ver_xdmcp        = '1.1.5'
ver_xft          = '2.3.8'
ver_xmu          = '1.2.1'
ver_xpm          = '3.5.17'
ver_xt           = '1.3.0'
ver_xtrans       = '1.5.1'
ver_xcb          = '1.17.0'
ver_xshmfence    = '1.3.2'
# extensions
ver_dmx          = '1.1.5'
ver_xcomposite   = '0.4.6'
ver_xdamage      = '1.1.6'
ver_xext         = '1.3.6'
ver_xf86dga      = '1.1.6'
ver_xf86vm       = '1.1.5'
ver_xfixes       = '6.0.1'
ver_xi           = '1.8.2'
ver_xinerama     = '1.1.5'
ver_xkbfile      = '1.1.3'
ver_xrandr       = '1.5.4'
ver_xrender      = '0.9.11'
ver_xres         = '1.2.2'
ver_xss          = '1.2.4'
ver_xtst         = '1.2.5'
ver_xv           = '1.0.12'
ver_xvmc         = '1.0.14'
# xserver
ver_xserver      = '21.1.99.1'
# drivers
ver_evdev = '2.11.0'

subdir('include')
subdir('static')
subdir('proto')
subdir('lib' / 'src' / 'xshmfence')
subdir('lib' / 'src' / 'xtrans') # <- lib/src/xshmfence
subdir('font') # <- lib/src/xtrans
subdir('lib')
subdir('font' / 'client')
subdir('server')
subdir('driver')
subdir('app')
subdir('demo')

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
      if h == 'unistd.h' and cc.has_header(h)
        conf.set('HAVE_@0@'.format(h.underscorify().to_upper()), 1) # avoid warning with redefinition in freetype2
      else
        conf.set('HAVE_@0@'.format(h.underscorify().to_upper()), cc.has_header(h))
      endif
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

conf.set('XTHREADS',                WITH_XTHREADS ? '1' : false)
conf.set('XUSE_MTSAFE_API',         WITH_XTHREADS ? '1' : false)
conf.set('X_FORCE_USE_MTSAFE_API',  WITH_XTHREADS ? '1' : false)
conf.set('XTHREADS_WARN',           WITH_XTHREADS_DBG ? '1' : false)
conf.set('XTHREADS_FILE_LINE',      WITH_XTHREADS_DBG ? '1' : false)
conf.set('XTHREADS_DEBUG',          WITH_XTHREADS_DBG ? '1' : false)

if WITH_DOC
if WITH_DOC_MAN
exe_sed  = find_program('sed',      required: false)
xmlto    = find_program('xmlto',    required: false)
xsltproc = find_program('xsltproc', required: false) # require_devel_docs
fop      = find_program('fop',      required: false) # require_docs_pdf
subdir('doc' / 'man')
endif
endif

configure_file(
  output: 'config.h',
  configuration: conf
)

if WITH_SUMMARY
summary(summary_lib,  bool_yn: true, section: 'X11 Library ')
summary(summary_srv,  bool_yn: true, section: 'X11 Server')
summary(summary_org,  bool_yn: true, section: 'X11 Server: Xorg')
summary(summary_xwl,  bool_yn: true, section: 'X11 Server: XWayland')
summary(summary_dir,  bool_yn: true, section: 'Directories')
summary(summary_mem,  bool_yn: true, section: 'Memory configuration')
summary(summary_info, bool_yn: true, section: 'Information')
endif