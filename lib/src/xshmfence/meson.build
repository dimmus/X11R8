# h_check += ['sys/umtx.h', 'linux/futex.h', 'sys/memfd.h', 'pthread.h']
h_check += ['pthread.h']
f_check += ['memfd_create', 'mkostemp']

dep_int_xshmfence = [xproto]

lib_args = []

shmdirs = ['/run/shm', '/dev/shm', '/var/tmp', '/tmp']

foreach dir : shmdirs
  if fs.is_dir(dir)
    conf.set_quoted('SHMDIR', dir)
  endif
endforeach

src = files('xshmfence_alloc.c')

# Enable only one of them!
WITH_PTHREAD = true  # h_check += ['pthread.h']
WITH_FUTEX   = false # h_check += ['sys/umtx.h', 'linux/futex.h']

if WITH_PTHREAD
  src += files('xshmfence_pthread.c')
endif

if WITH_FUTEX
  src += files('futex/xshmfence_futex.c')
endif

lib = library('xshmfence', src,
  c_args: lib_args,
  include_directories: inc_x11,
  dependencies: dep_int_xshmfence,
  version: '1.0.0',
  install: true,
)

libxshmfence = declare_dependency(
  link_with: lib,
  include_directories: inc_x11,
)

pkg.generate(lib,
  description: 'The X Shared Memory Fence Library',
  version: ver_xshmfence,
  filebase: 'xshmfence',
)