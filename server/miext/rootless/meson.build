srcs_miext_rootless = files(
   'rootlessCommon.c',
   'rootlessGC.c',
   'rootlessScreen.c',
   'rootlessValTree.c',
   'rootlessWindow.c',
)

libxserver_miext_rootless = static_library('libxserver_miext_rootless',
   srcs_miext_rootless,
   include_directories: inc_server,
   dependencies: dep_common,
   c_args: XSERVER_CFLAGS,
   link_args: XSERVER_LDFLAGS,
)
