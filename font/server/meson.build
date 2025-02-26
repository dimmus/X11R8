ver_xfs = '1.2.2'

inc_xfs = include_directories('include')

h_check += 'stdint.h'
f_check += 'daemon'

lib_args  = [
  '-DFONT_t', '-DTRANS_SERVER', '-DTRANS_REOPEN', '-DTCPCONN',
  '-DXFS_INETD', '-DUSE_SYSLOG', '-DXFSPIDDIR="/var/run"',
]

dep_int_xfs = [xproto, libxfont]

src = files(
  'difs/atom.c',
  'difs/charinfo.c',
  'difs/difsutils.c',
  'difs/dispatch.c',
  'difs/events.c',
  'difs/extensions.c',
  'difs/fontinfo.c',
  'difs/fonts.c',
  'difs/globals.c',
  'difs/initfonts.c',
  'difs/main.c',
  'difs/resource.c',
  'difs/swaprep.c',
  'difs/swapreq.c',
  'difs/tables.c',
  'os/access.c',
  'os/config.c',
  'os/configstr.h',
  'os/connection.c',
  'os/daemon.c',
  'os/error.c',
  'os/io.c',
  'os/osdep.h',
  'os/osglue.c',
  'os/osinit.c',
  'os/utils.c',
  'os/waitfor.c',
  'os/xfstrans.c',
)

executable('xfs', src,
  dependencies: dep_int_xfs,
  c_args: lib_args,
  include_directories: [inc_font, inc_xfs, inc_lib],
)

subdir('config')