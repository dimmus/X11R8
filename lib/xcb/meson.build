inc_xcb += [
  inc_config,
  include_directories('.')
]

f_check += ['getaddrinfo', 'poll']
h_check += []

conf.set('HAVE_SENDMSG', 1) # Define if your platform supports sendmsg
conf.set('HAVE_ABSTRACT_SOCKETS', 1) # Define if your platform supports abstract sockets
conf.set('XCB_QUEUE_BUFFER_SIZE', 16384) # Set the XCB buffer queue size (default is 16384)
conf.set('XCB_SERVERSIDE_SUPPORT', 0) # Build with support for server-side usage of xcb. This is still EXPERIMENTAL! ABI/API may change! (default: no)
# conf.set('IOV_MAX', 16) # Define if not provided by <limits.h>

dep_int_xcb = [libxau, libxdmcp]

BUILD_COMPOSITE   = get_option('composite')
BUILD_DAMAGE      = get_option('damage') 
BUILD_DBE         = get_option('dbe')
BUILD_DPMS        = get_option('dpms')
BUILD_DRI2        = get_option('dri2')
BUILD_DRI3        = get_option('dri3')
BUILD_GLX         = get_option('glx')
BUILD_PRESENT     = get_option('present')
BUILD_RANDR       = get_option('randr')
BUILD_RECORD      = get_option('record')
BUILD_RENDER      = get_option('render')
BUILD_RESOURCE    = get_option('resource')
BUILD_SCREENSAVER = get_option('screensaver')
BUILD_SHAPE       = get_option('shape')
BUILD_SHM         = get_option('shm')
BUILD_SYNC        = get_option('sync')
BUILD_XEVIE       = get_option('xevie')
BUILD_XFREE86_DRI = get_option('xfree86_dri')
BUILD_XFIXES      = get_option('xfixes')
BUILD_XINERAMA    = get_option('xinerama')
BUILD_XINPUT      = get_option('xinput')
BUILD_XKB         = get_option('xkb')
BUILD_XPRINT      = get_option('xprint')
BUILD_SELINUX     = get_option('selinux')
BUILD_XTEST       = get_option('xtest')
BUILD_XV          = get_option('xv')
BUILD_XVMC        = get_option('xvmc')
BUILD_GE          = get_option('ge')

# C_CLIENT_PY_EXTRA_ARGS =
# if XCB_SERVERSIDE_SUPPORT
# C_CLIENT_PY_EXTRA_ARGS += --server-side
# endif

# $(EXTSOURCES): c_client.py $(XCBPROTO_XCBINCLUDEDIR)/$(@:.c=.xml)
# 	$(AM_V_GEN)$(PYTHON) $(srcdir)/c_client.py	-c "$(PACKAGE_STRING)" -l "$(XORG_MAN_PAGE)" \
# 		-s "$(LIB_MAN_SUFFIX)" -p $(XCBPROTO_XCBPYTHONDIR) \
# 		$(C_CLIENT_PY_EXTRA_ARGS) \
# 		$(XCBPROTO_XCBINCLUDEDIR)/$(@:.c=.xml)

subdir('proto')
subdir('src')

xcb = library('xcb', 
  [src, src_proto],
  include_directories: inc_xcb,
  dependencies: dep_int_xcb,
  version: '2.0.1',
  install: true,
)

libxcb = declare_dependency(
  link_with: xcb,
  include_directories: inc_xcb,
)

pkg.generate(
  name: 'XCB',
  description: 'X-protocol C Binding',
  version: '1.17.0',
  requires_private: ['xau', 'xdmcp'],
)

if BUILD_COMPOSITE
pkg.generate(
  name: 'XCB Composite',
  description: 'XCB Composite Extension',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-xfixes'],
)
endif
if BUILD_DAMAGE
pkg.generate(
  name: 'XCB Damage',
  description: 'XCB Damage Extension',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-xfixes'],
)
endif
if BUILD_DBE
pkg.generate(
  name: 'XCB Dbe',
  description: 'XCB Double Buffer Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_DPMS
pkg.generate(
  name: 'XCB DPMS',
  description: 'XCB DPMS Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_DRI2
pkg.generate(
  name: 'XCB DRI2',
  description: 'XCB DRI2 Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_DRI3
pkg.generate(
  name: 'XCB DRI3',
  description: 'XCB DRI3 Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_GLX
pkg.generate(
  name: 'XCB GLX',
  description: 'XCB GLX Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_PRESENT
pkg.generate(
  name: 'XCB Present',
  description: 'XCB Present Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_RANDR
pkg.generate(
  name: 'XCB RandR',
  description: 'XCB RandR Extension',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-render'],
)
endif
if BUILD_RECORD
pkg.generate(
  name: 'XCB Record',
  description: 'XCB Record Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_RENDER
pkg.generate(
  name: 'XCB Render',
  description: 'XCB Render Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_RESOURCE
pkg.generate(
  name: 'XCB Res',
  description: 'XCB X-Resource Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_SCREENSAVER
pkg.generate(
  name: 'XCB Screensaver',
  description: 'XCB Screensaver Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_SHAPE
pkg.generate(
  name: 'XCB Shape',
  description: 'XCB Shape Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_SHM
pkg.generate(
  name: 'XCB Shm',
  description: 'XCB Shm Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_SYNC
pkg.generate(
  name: 'XCB Sync',
  description: 'XCB Sync Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XEVIE
pkg.generate(
  name: 'XCB Xevie',
  description: 'XCB Xevie Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XFREE86_DRI
pkg.generate(
  name: 'XCB XFree86-DRI',
  description: 'XCB XFree86-DRI Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XFIXES
pkg.generate(
  name: 'XCB XFixes',
  description: 'XCB XFixes Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XINERAMA
pkg.generate(
  name: 'XCB Xinerama',
  description: 'XCB Xinerama Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XINPUT
pkg.generate(
  name: 'XCB XInput',
  description: 'XCB XInput Extension (EXPERIMENTAL)',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-xfixes'],
)
endif
if BUILD_XKB
pkg.generate(
  name: 'XCB XKB',
  description: 'XCB Keyboard Extension (EXPERIMENTAL)',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XPRINT
pkg.generate(
  name: 'XCB Xprint',
  description: 'XCB Xprint Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_SELINUX
pkg.generate(
  name: 'XCB SELinux',
  description: 'XCB SELinux Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XTEST
pkg.generate(
  name: 'XCB XTEST',
  description: 'XCB XTEST Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif
if BUILD_XV
pkg.generate(
  name: 'XCB Xv',
  description: 'XCB Xv Extension',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-shm'],
)
endif
if BUILD_XVMC
pkg.generate(
  name: 'XCB XvMC',
  description: 'XCB XvMC Extension',
  version: '1.17.0',
  requires_private: ['xcb', 'xcb-xv'],
)
endif
if BUILD_GE
pkg.generate(
  name: 'XCB GenericEvent',
  description: 'XCB GenericEvent Extension',
  version: '1.17.0',
  requires_private: 'xcb',
)
endif

subdir('utils')