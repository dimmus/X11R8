inc_xcb += include_directories('.')

src = [
  'xproto',
  'bigreq',
  'composite',
  'damage',
  'dbe',
  'dpms',
  'dri2',
  'dri3',
  'ge',
  'glx',
  'present',
  'randr',
  'record',
  'render',
  'res',
  'screensaver',
  'shape',
  'shm',
  'sync',
  'xc_misc',
  'xevie',
  'xf86dri',
  'xf86vidmode',
  'xfixes',
  'xinerama',
  'xinput',
  'xkb',
  'xprint',
  'xselinux',
  'xtest',
  'xv',
  'xvmc',
]

# C_CLIENT_PY_EXTRA_ARGS =
# if XCB_SERVERSIDE_SUPPORT
# C_CLIENT_PY_EXTRA_ARGS += --server-side
# endif

# $(EXTSOURCES): c_client.py $(XCBPROTO_XCBINCLUDEDIR)/$(@:.c=.xml)
# 	$(AM_V_GEN)$(PYTHON) $(srcdir)/c_client.py	-c "$(PACKAGE_STRING)" -l "$(XORG_MAN_PAGE)" \
# 		-s "$(LIB_MAN_SUFFIX)" -p $(XCBPROTO_XCBPYTHONDIR) \
# 		$(C_CLIENT_PY_EXTRA_ARGS) \
# 		$(XCBPROTO_XCBINCLUDEDIR)/$(@:.c=.xml)

python_env = {
  'PYTHONPATH': dir_source / 'proto' / 'xcb' / 'xcbgen'
}

src_proto = []
foreach proto : src
  file = custom_target(
    'generate_' + proto,
    input: 'src' / proto + '.xml',
    output: proto + '.c',
    command: [
      python, dir_source / 'proto' / 'xcb' / 'xcbgen.py',
      '-c', 'xcb-proto',
      '-l', proto,
      '-s', 'proto',
      '-p', dir_build / 'proto',
      '--server-side',
      '@INPUT@',
    ],
    env: python_env,
    build_by_default: true
  )
  src_proto += file
endforeach

# lib = library('xcb-proto', src_proto,
#   include_directories: inc_xcb,
#   version: '0.0.0',
#   install: true,
# )

# xcbproto = declare_dependency(
#   link_with: lib,
#   include_directories: inc_xcb,
# )

pkg.generate(
  name: 'XCB Proto',
  description: 'X protocol descriptions for XCB',
  version: '1.17',
)

# if HAVE_XMLLINT
# check-local:
# 	$(XMLLINT) --noout --schema $(srcdir)/xcb.xsd $(srcdir)/*.xml
# endif