f_check += ['uuid_create']

dep_ext_sm = [dep_uuid]
dep_int_sm = [xproto, libice]

src = files(
  'sm_client.c',
  'sm_error.c',
  'sm_genid.c',
  'sm_manager.c',
  'sm_misc.c',
  'sm_process.c',
)

lib = library('SM', src,
  include_directories: inc_lib,
  dependencies: [dep_int_sm, dep_ext_sm],
  version: '6.0.1',
  install: true,
)

libsm = declare_dependency(
  link_with: lib,
  include_directories: inc_lib,
)

pkg.generate(lib,
  description: 'X Session Management Library',
  version: ver_sm,
  filebase: 'sm',
  requires_private: ['xproto', 'ice', 'uuid'],
)
