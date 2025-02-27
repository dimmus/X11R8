srcs_glx = files(
    'indirect_dispatch.c',
    'indirect_dispatch_swap.c',
    'indirect_reqsize.c',
    'indirect_size_get.c',
    'indirect_table.c',
    'clientinfo.c',
    'createcontext.c',
    'extension_string.c',
    'indirect_util.c',
    'indirect_program.c',
    'indirect_texture_compression.c',
    'glxcmds.c',
    'glxcmdsswap.c',
    'glxext.c',
    'glxdriswrast.c',
    'glxdricommon.c',
    'glxscreens.c',
    'render2.c',
    'render2swap.c',
    'renderpix.c',
    'renderpixswap.c',
    'rensize.c',
    'single2.c',
    'single2swap.c',
    'singlepix.c',
    'singlepixswap.c',
    'singlesize.c',
    'swap_interval.c',
    'xfont.c',
)

libxserver_glx = []
if build_glx
    libxserver_glx = static_library('libxserver_glx',
        srcs_glx,
        include_directories: inc_server,
        dependencies: [
            dep_common,
            dep_dl,
            dep_dri,
            dep_gl,
        ],
        c_args: [
            XSERVER_CFLAGS,
            glx_align64,
            '-Wno-unused-function',
        ],
        link_args: XSERVER_LDFLAGS,
    )
endif

srcs_glxdri2 = []
if build_dri2 or build_dri3
    srcs_glxdri2 = files('glxdri2.c')
endif

srcs_vnd = files(
    'vndcmds.c',
    'vndext.c',
    'vndservermapping.c',
    'vndservervendor.c',
)

libglxvnd = []
if build_glx
    libglxvnd = static_library('libglxvnd',
        srcs_vnd,
        include_directories: inc_server,
        dependencies: [dep_common, dep_dl, dep_gl],
        c_args: XSERVER_CFLAGS,
        link_args: XSERVER_LDFLAGS,
    )
    install_data('vndserver.h', install_dir: dir_xorg)
endif
