project('X Window System', 'c', 
    license: 'MIT', 
    version: '11.8.1',
    default_options : [
      'buildtype=debugoptimized', # plain,debug,debugoptimized,release,minsize,custom
      'c_std=gnu99', # we use typeof in server
      'optimization=2',  # 0,g,1,2,3,s
      # 'b_sanitize=none   # none,address,thread,undefined,memory,leak,address,undefined',
      # 'b_coverage=true',
      # 'b_lto=false',
      # 'b_lto_threads=32',
      # 'b_staticpic=true', 
      # 'b_pie=false',
      # 'b_lundef=true',
      'prefix=/usr',
      'sysconfdir=/etc',
      'localstatedir=/var'
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
      # '-Werror=write-strings', # initialization discards ‘const’ qualifier from pointer target type
      '-Werror=address',
      '-Werror=int-to-pointer-cast',
      '-Werror=pointer-to-int-cast',
    ]
  endif
else
  test_wflags = [
    '-Wno-error=array-bounds',      # 32-bit fails otherwise
    '-Wno-use-after-free',          # gcc
    '-Wno-stringop-truncation',     # gcc
    '-Wno-maybe-uninitialized',     # gcc
    '-Wno-unused-result',           # gcc, clang
    '-Wno-format-truncation',       # gcc, clang
    '-Wno-stringop-overflow',       # gcc
    '-Wno-strict-aliasing',         # gcc, clang
    '-Wno-array-bounds',            # gcc, clang
    '-Wno-stringop-overread',       # gcc
    '-Wno-unused-but-set-variable', # gcc, clang
    '-Wno-typedef-redefinition',    # clang
    '-Wno-incompatible-pointer-types-discards-qualifiers', # clang
    '-Wno-unknown-warning-option',  # clang
  ]
endif

add_project_arguments(
  cc.get_supported_arguments(test_wflags), 
  language: 'c'
)

add_project_arguments(
  '-DHAVE_CONFIG_H',
  '-DHAVE_DIX_CONFIG_H',
  '-D_GNU_SOURCE',
  '-D_DEFAULT_SOURCE', # use instead of deprecated _BSD_SOURCE and _SVID_SOURCE
  '-march=x86-64',
  '-mtune=generic',
  '-pipe',
  '-fstack-protector-strong',
  language: 'c'
)

add_project_link_arguments(
  '-Wl,-O1,--sort-common,--as-needed,-z,relro',
  language: 'c'
)

dir_build        = meson.project_build_root()
dir_source       = meson.project_source_root()

dir_prefix       = get_option('prefix')
dir_bin          = dir_prefix / get_option('bindir')
dir_data         = dir_prefix / get_option('datadir')
dir_include      = dir_prefix / get_option('includedir')
dir_lib          = dir_prefix / get_option('libdir')
dir_man          = dir_prefix / get_option('mandir')
dir_sysconf      = dir_prefix / get_option('sysconfdir')
dir_libexec      = dir_prefix / get_option('libexecdir')
dir_xorg_module  = dir_lib / 'xorg' / 'modules' # drivers
dir_xorg_conf    = dir_data / 'X11' / 'xorg.conf.d' # drivers
dir_xorg         = dir_include / 'xorg' # server

WITH_DEBUG       = get_option('build-debug')
WITH_FONT_SERVER = get_option('build-font-server')
WITH_TESTS       = get_option('build-test')
WITH_DOC         = get_option('build-doc')
WITH_DOC_MAN     = get_option('build-doc-man')
WITH_INT_PIXMAN  = get_option('build-static-pixman')
WITH_INT_EPOXY   = get_option('build-static-epoxy')
WITH_DEMO        = get_option('build-demo')
WITH_APP         = get_option('build-app')
WITH_DTRACE      = get_option('dtrace')

dep_m            = cc.find_library('m',         required: true)  # libxcvt
dep_dl           = cc.find_library('dl',        required: false) # xvmc, xserver, static/epoxy
dep_rt           = cc.find_library('rt',        required: true)  # driver/video/intel

dep_zlib         = dependency('zlib',           required: true)  # xfont, fontenc
dep_bzip2        = dependency('bzip2',          required: true)  # xfont
dep_freetype2    = dependency('freetype2',      required: true)  # xfont, xft
dep_fontconfig   = dependency('fontconfig',     required: true, version: '>= 2.5.92') # xft
dep_uuid         = dependency('uuid',           required: false) # sm
dep_gettext      = dependency('gettext',        required: false) # xpm
# xserver
dep_null         = dependency('',               required: false)
dep_pixman       = dependency('pixman-1',       required: not WITH_INT_PIXMAN)
dep_libbsd       = dependency('libbsd-overlay', required: false)
dep_dbus         = dependency('dbus-1',         required: get_option('systemd_logind') == 'true', version: '>= 1.0')
dep_fontutil     = dependency('fontutil',       required: false)
dep_drm          = dependency('libdrm',         required: true, version: '>= 2.4.116') # server/hw/xfree86, driver/video/intel
dep_gl           = dependency('gl',             required: true, version: '>= 1.2') # server/glx, static/epoxy, driver/amdgpu
dep_gbm          = dependency('gbm',            required: true ) # server/glamor
dep_epoxy        = dependency('epoxy',          required: not WITH_INT_EPOXY) # server/glamor
dep_pciaccess    = dependency('pciaccess',      required: get_option('pciaccess'), version: '>= 0.12.901') # server/hw/xfree86
dep_systemd      = dependency('libsystemd',     required: false, version: '>= 209') # server
dep_libunwind    = dependency('libunwind',      required: get_option('libunwind')) # server
dep_dri          = dependency('dri',            required: true ) # server, driver/video/intel
dep_libsha1      = dependency('libsha1',        required: false) # server/os
dep_nettle       = dependency('nettle',         required: false) # server/os
dep_gcrypt       = dependency('libgcrypt',      required: false) # server/os
dep_openssl      = dependency('openssl',        required: false) # server/os

# app
dep_jpeg         = dependency('libjpeg',        required: get_option('xli')) # app/xli

# static
dep_threads      = dependency('threads',        required: get_option('build-video-intel')) # pixman, driver/video/intel
dep_openmp       = dependency('openmp',         required: get_option('openmp')) # pixman
dep_egl          = dependency('egl',            required: WITH_INT_EPOXY) # epoxy
dep_gles2        = dependency('glesv2',         required: WITH_INT_EPOXY) # epoxy

# drivers
dep_udev         = dependency('libudev',        required: false) # input/evdev
dep_evdev        = dependency('libevdev',       required: false) # input/evdev
dep_input        = dependency('libinput',       required: true, version: '>= 1.11.0') # input/libinput
dep_cairo        = dependency('cairo',          required: WITH_TESTS) # video/intel (test)
dep_png          = dependency('libpng',         required: true ) # video/intel (test, tools)
dep_drm_intel    = dependency('libdrm_intel',   required: true ) # video/intel
dep_drm_nouveau  = dependency('libdrm_nouveau', required: true ) # video/nouveau
dep_drm_radeon   = dependency('libdrm_radeon',  required: true ) # video/ati
dep_xa           = dependency('xatracker',      required: true ) # video/vmware
dep_valgrind     = dependency('valgrind',       required: get_option('valgrind')) # video/intel

exe_bison        = find_program('bison',        required: false)
exe_flex         = find_program('flex',         required: false)
exe_gzip         = find_program('gzip',         required: false)
exe_awk          = find_program('awk',          required: false)
exe_dtrace       = find_program('dtrace',       required: WITH_DTRACE)
# exe_python       = find_program('python3',      required: false) # unused

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
inc_pixman       = []
inc_epoxy        = []

summary_dir      = {}
summary_lib      = {}
summary_srv      = {}
summary_org      = {}

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
subdir('data')

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
    if (h == 'unistd.h' or h == 'fcntl.h') and cc.has_header(h)
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
  endif
endif

## extension/xkbfile
conf.set('HAVE_REALLOCF', cc.has_function('reallocf'))
conf.set('HAVE_STRNDUP', cc.has_function('strndup') and cc.has_header_symbol('string.h', 'strndup'))
conf.set('HAVE_UNLOCKED_STDIO', cc.has_function('getc_unlocked'))

conf.set('XTHREADS',                '1')
conf.set('XUSE_MTSAFE_API',         '1')
conf.set('X_FORCE_USE_MTSAFE_API',  '1')

if WITH_DOC
if WITH_DOC_MAN
exe_sed  = find_program('sed',      required: false)
# xmlto    = find_program('xmlto',    required: false)
# xsltproc = find_program('xsltproc', required: false) # require_devel_docs
# fop      = find_program('fop',      required: false) # require_docs_pdf
subdir('doc' / 'man')
endif
endif

if WITH_DEBUG
  conf.set('DEBUG', true)
  
  conf.set('XTHREADS_WARN', true)
  conf.set('XTHREADS_DEBUG', true)
  conf.set('XTHREADS_FILE_LINE', true)
  
  # twm
  conf.set('DEBUG_EVENTS', true)
  conf.set('DEBUG_ICONMGR', true)
  conf.set('DEBUG_MENUS', true)

  conf.set('XTRANSDEBUG', '5') # level 1-5
  conf.set('XTRANSDEBUGTIMESTAMP', false)

  # mowitz
  conf.set('DEBUG_GEOM', true)
  conf.set('DEBUG_TF', true)
  
  conf.set('FONTDEBUG', true)
  conf.set('XNL_DEBUG', true)
  conf.set('DEBUG_WO_TIMERS', true)
  
  # server
  conf.set('COMPOSITE_DEBUG', true)
  conf.set('SMART_DEBUG', true)
  conf.set('DEBUG_EVENTS', true)
  conf.set('PTRACCEL_DEBUGGING', true)
  conf.set('DEBUG_GLYPH_CACHE', true)
  conf.set('DEBUG_TRACE_FALL', false) # error in driver/video/vmeare (saa)
  conf.set('FB_DEBUG', true)
  conf.set('DEBUGOVERSCAN', true)
  conf.set('SPRITE_DEBUG_ENABLE', true)
  conf.set('DAMAGE_VALIDATE_ENABLE', true)
  conf.set('ROOTLESSDEBUG', true)
  conf.set('FAMILY_SI_DEBUG', true)
  conf.set('DEBUG_COMMUNICATION', true)
endif

configure_file(output: 'config.h',  configuration: conf)

summary_dir += {'PREFIX': dir_prefix}
summary_dir += {'BIN': dir_bin}
summary_dir += {'DATA': dir_data}
summary_dir += {'INCLUDE': dir_include}
summary_dir += {'LIB': dir_lib}
summary_dir += {'MAN': dir_man}
summary_dir += {'SYSCONF': dir_sysconf}
summary_dir += {'LIBEXEC': dir_libexec}
summary_dir += {'XORG-MODULES': dir_xorg_module}
summary_dir += {'XORG-CONF': dir_xorg_conf}
summary_dir += {'XORG': dir_xorg}

summary(summary_dir,  bool_yn: true, section: 'Directories: ')
summary(summary_lib,  bool_yn: true, section: 'X11 Library ')
summary(summary_srv,  bool_yn: true, section: 'X11 Server')
summary(summary_org,  bool_yn: true, section: 'X11 Server: Xorg')