# Enable only one of them!
WITH_PTHREAD = true
WITH_FUTEX   = not WITH_PTHREAD

if WITH_PTHREAD
  h_check += ['sys/memfd.h', 'pthread.h']
else
  h_check += ['sys/umtx.h', 'linux/futex.h']
endif
f_check += ['memfd_create', 'mkostemp']

dep_int_xshmfence = xproto

foreach dir : ['/run/shm', '/dev/shm', '/var/tmp', '/tmp']
  if fs.is_dir(dir)
    conf.set_quoted('SHMDIR', dir)
  endif
endforeach

src = files('xshmfence_alloc.c')

if WITH_PTHREAD
  src += files('xshmfence_pthread.c')
endif

if WITH_FUTEX
  src += files('xshmfence_futex.c')
endif

lib = library('xshmfence', src,
  include_directories: inc_lib,
  dependencies: dep_int_xshmfence,
  version: '1.0.0',
  install: true,
)

libxshmfence = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'The X Shared Memory Fence Library',
  version: ver_xshmfence,
  filebase: 'xshmfence',
)