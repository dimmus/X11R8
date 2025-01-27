ver_intel = '2.99.917'
version = ver_intel.split('.')

conf.set('PACKAGE_VERSION_MAJOR', version[0])
conf.set('PACKAGE_VERSION_MINOR', version[1])
conf.set('PACKAGE_VERSION_PATCHLEVEL', version[2])
conf.set_quoted('LIBEXEC_PATH', dir_libexec)

# cairo-xlib-xrender
dep_int_intel = [
  xproto,
  libx11,
  libx11_xcb,
  libxcomposite,
  libxdamage,
  libxrender,
  libxrandr,
  libxext,
  libxfixes,
  libxcb,
  xserver,
]

dep_ext_intel = [
  dep_threads,
  dep_pciaccess,
  dep_pixman,
  dep_cairo,
  dep_png,
  dep_drm_intel,
]

dep_intel_drv = [dep_int_intel, dep_ext_intel]

f_check += ['getline', 'strndup', 'strcasecmp']

if not cc.has_function('clock_gettime', args : '-lrt')
  error('clock_gettime() missing')
endif

with_tools = get_option('tools')

conf.set('USE_GIT_DESCRIBE', 1)
conf.set('BUILDER_DESCRIPTION', 1)

atomic_primitives = 'none'

atomic_primitives_code = '''
int atomic_add(int i) {
    return __sync_fetch_and_add (&i, 1);
}
int atomic_cmpxchg(int i, int j, int k) {
    return __sync_val_compare_and_swap (&i, j, k);
}
int main(void) {
    return 0;
}'''
if cc.links(atomic_primitives_code, name : 'atomic primitives')
  atomic_primitives = 'intel'
  conf.set('HAVE_ATOMIC_PRIMITIVES', 1)
endif

if atomic_primitives == 'none' and cc.has_header('atomic_ops.h')
  atomic_primitives = 'libatomic-ops'
  conf.set('HAVE_LIB_ATOMIC_OPS', 1)
endif

if atomic_primitives == 'none'
  error('xf86-video-intel depends upon atomic operations, which were not found for your compiler/cpu. Try compiling with -march=native, or install the libatomics-op-dev package.')
endif

if dep_udev.found()
  conf.set('HAVE_UDEV', 1)
endif

cpuid_code = '''
#include <cpuid.h>
#include <stddef.h>
int main(void) {
    int eax, ebx, ecx, edx;
    if (__get_cpuid_max(0, NULL) < 4)
       return 0;
    __cpuid_count(4, 0, eax, ebx, ecx, edx);
    return 0;
}'''
if cc.links(cpuid_code, name : '__cpuid()')
  conf.set('HAVE_CPUID_H', 1)
endif

if cc.has_header('sys/ipc.h')
  conf.set('HAVE_MIT_SHM', 1)
  conf.set('HAVE_X11_EXTENSIONS_SHMPROTO_H', 1)
  conf.set('HAVE_X11_EXTENSIONS_SHMSTR_H', 1)
endif

conf.set('HAVE_X11_EXTENSIONS_XINERAMA_H', 1)
conf.set('HAVE_X11_EXTENSIONS_DPMSCONST_H', 1)
conf.set('HAS_PIXMAN_TRIANGLES', 1)
conf.set('HAS_PIXMAN_GLYPHS', 1)

if get_option('kms')
  conf.set('KMS', 1)
endif

with_ums = get_option('ums')
if with_ums
  if not cc.has_header('vgaHW.h')
    error('UMS dependencies not met')
  endif
  conf.set('UMS', 1)
endif

conf.set('ENABLE_XVMC', 1)

with_valgrind = get_option('valgrind')
if with_valgrind
  message('Checking Valgrind support')
  valgrind = dependency('valgrind', required : true)
  conf.set('HAVE_VALGRIND', 1)
endif

inc = [
  include_directories('.', 'src', 'xvmc', 'src/render_program'),
  inc_server
]

# man_config = configuration_data()
# man_conf.set('appmansuffix', '1')
# man_conf.set('filemansuffix', '5')
# man_conf.set('drivermansuffix', '4')
# man_conf.set('miscmansuffix', '7')
# man_conf.set('xservername',
# 	       cc.get_define('__XSERVERNAME__',
# 			     prefix : '#include <xorg-server.h>')
# man_conf.set('xconfigfile',
# 	       cc.get_define('__XCONFIGFILE____',
# 			     prefix : '#include <xorg-server.h>')
# man_conf.set('vendorversion', '"@0@ @1@" "@2@"'.format(meson.project_name(),
# 							 meson.project_version(),
# 							 'X Version 11'))

subdir('src')
subdir('tools')
subdir('xvmc')

# subdir('man')

# configure_file(output: 'conf.h', install: false, configuration: config)
