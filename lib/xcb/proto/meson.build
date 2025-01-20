inc_xcb += include_directories('.')

src_proto = files(
    'xproto.c',
    'bigreq.c',
    'xc_misc.c',
)

if BUILD_COMPOSITE
    src_proto += files('composite.c')
endif

if BUILD_DAMAGE
    src_proto += files('damage.c')
endif

if BUILD_DBE
    src_proto += files('dbe.c')
endif

if BUILD_DPMS
    src_proto += files('dpms.c')
endif

if BUILD_DRI2
    src_proto += files('dri2.c')
endif

if BUILD_DRI3
    src_proto += files('dri3.c')
endif

if BUILD_PRESENT
    src_proto += files('present.c')
endif

if BUILD_GLX
    src_proto += files('glx.c')
endif

if BUILD_RANDR
    src_proto += files('randr.c')
endif

if BUILD_RECORD
    src_proto += files('record.c')
endif

if BUILD_RENDER
    src_proto += files('render.c')
endif

if BUILD_RESOURCE
    src_proto += files('res.c')
endif

if BUILD_SCREENSAVER
    src_proto += files('screensaver.c')
endif

if BUILD_SHAPE
    src_proto += files('shape.c')
endif

if BUILD_SHM
    src_proto += files('shm.c')
endif

if BUILD_SYNC
    src_proto += files('sync.c')
endif

if BUILD_XEVIE
    src_proto += files('xevie.c')
endif

if BUILD_XFREE86_DRI
    src_proto += files('xf86dri.c')
endif

if BUILD_XFIXES
    src_proto += files('xfixes.c')
endif

if BUILD_XINERAMA
    src_proto += files('xinerama.c')
endif

if BUILD_XINPUT
    src_proto += files('xinput.c')
endif

if BUILD_XKB
    src_proto += files('xkb.c')
endif

if BUILD_XPRINT
    src_proto += files('xprint.c')
endif

if BUILD_SELINUX
    src_proto += files('xselinux.c')
endif

if BUILD_XTEST
    src_proto += files('xtest.c')
endif

if BUILD_XV
    src_proto += files('xv.c')
endif

if BUILD_XVMC
    src_proto += files('xvmc.c')
endif

if BUILD_GE
    src_proto += files('ge.c')
endif