ver_epoxy = '1.5.11'

inc_epoxy = [include_directories('.')]

dep_ext_epoxy = [dep_dl, dep_egl.partial_dependency(compile_args: true, includes: true)]

epoxy_has_glx = get_option('glx')
epoxy_has_egl = get_option('egl')

conf_epoxy = configuration_data()
conf_epoxy.set10('ENABLE_GLX', epoxy_has_glx)
conf_epoxy.set10('ENABLE_EGL', epoxy_has_egl)

if not dep_gles2.found()
  dep_gles2 = cc.find_library('libGLESv2', required: false)
  dep_ext_epoxy += dep_gles2
endif

gen_dispatch_py = find_program('src/gen_dispatch.py')

gl_registry  = files('registry/gl.xml')
egl_registry = files('registry/egl.xml')
glx_registry = files('registry/glx.xml')

epoxy_headers = []

subdir('include')
subdir('src')