inc_epoxy += include_directories('.')

# Configuration file
configure_file(output: 'config_epoxy.h', configuration: conf_epoxy)

# List of generated sources:
#   - name of the generated file
#   - registry source file
#   - additional sources
# generated_sources  = [ [ 'gl_generated_dispatch.c',  gl_registry,  ['dispatch_common.c', 'dispatch_common.h'] ] ]
# generated_sources += [ [ 'egl_generated_dispatch.c', egl_registry, 'dispatch_egl.c' ] ]
# generated_sources += [ [ 'glx_generated_dispatch.c', glx_registry, 'dispatch_glx.c' ] ]

# gen_sources = []
# sources = []

# foreach g: generated_sources
#   gen_source = g[0]
#   registry = g[1]
#   source = g[2]

#   generated = custom_target(gen_source,
#                             input: registry,
#                             output: [ gen_source ],
#                             command: [
#                               gen_dispatch_py,
#                               '--source',
#                               '--no-header',
#                               '--outputdir=@OUTDIR@',
#                               '@INPUT@',
#                             ])

#   gen_sources += [ generated ]
#   sources += [ source ]
# endforeach

# epoxy_sources = sources + gen_sources

# XXX: hardcoded here generated above files
epoxy_sources = files(
  'dispatch_common.c',
  'dispatch_egl.c',
  'dispatch_glx.c',
  'gl_generated_dispatch.c',
  'egl_generated_dispatch.c',
  'glx_generated_dispatch.c',
)

common_ldflags = []
if host_machine.system() == 'linux' and cc.get_id() == 'gcc'
  common_ldflags += cc.get_supported_link_arguments([ '-Wl,-Bsymbolic-functions', '-Wl,-z,relro' ])
endif

epoxy = static_library('epoxy',
  sources: epoxy_sources + epoxy_headers,
  install: true,
  dependencies: dep_ext_epoxy,
  include_directories: [inc_epoxy, inc_lib],
  link_args: common_ldflags,
)

libepoxy = declare_dependency(
  link_with: epoxy,
  include_directories: [inc_epoxy, inc_lib],
  dependencies: dep_ext_epoxy,
  sources: epoxy_headers,
  variables: {
    'epoxy_has_glx': epoxy_has_glx ? '1' : '0',
    'epoxy_has_egl': epoxy_has_egl ? '1' : '0',
  },
)

# We don't want to add these dependencies to the library, as they are
# not needed when building Epoxy; we do want to add them to the generated
# pkg-config file, for consumers of Epoxy
gl_reqs = []
if dep_gl.found() and dep_gl.type_name() == 'pkgconfig'
  gl_reqs += dep_gl.name()
endif
if dep_egl.found() and dep_egl.type_name() == 'pkgconfig'
  gl_reqs += 'egl'
endif

pkg.generate(
  libraries: libepoxy,
  name: 'epoxy',
  description: 'GL dispatch library',
  version: ver_epoxy,
  variables: [
    'epoxy_has_glx=@0@'.format(epoxy_has_glx),
    'epoxy_has_egl=@0@'.format(epoxy_has_egl),
  ],
  filebase: 'epoxy',
  requires_private: ' '.join(gl_reqs),
)
