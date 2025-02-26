srcs_mi = files(
  'miarc.c',
  'micmap.c',
  'micopy.c',
  'midash.c',
  'midispcur.c',
  'mieq.c',
  'miexpose.c',
  'mifillarc.c',
  'migc.c',
  'miglblt.c',
  'mipointer.c',
  'mipoly.c',
  'mipolypnt.c',
  'mipolyrect.c',
  'mipolyseg.c',
  'mipolytext.c',
  'mipushpxl.c',
  'miscrinit.c',
  'misprite.c',
  'mivaltree.c',
  'miwideline.c',
  'miwindow.c',
  'mizerarc.c',
  'mizerclip.c',
  'mizerline.c',
)

hdrs_mi = files(
  'micmap.h',
  'micoord.h',
  'migc.h',
  'mi.h',
  'miline.h',
  'mipointer.h',
  'mipointrst.h',
  'mistruct.h',
  'mizerarc.h',
)

libxserver_mi = static_library('libxserver_mi',
  srcs_mi,
  include_directories: inc_server,
  dependencies: [dep_common, dep_m],
  c_args: XSERVER_CFLAGS,
)

install_data(hdrs_mi, install_dir: dir_xorg)
