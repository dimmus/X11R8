xfs_config = configuration_data()

XORG_FONTSUBDIR(FONTMISCDIR, fontmiscdir, misc)
XORG_FONTSUBDIR(FONTOTFDIR, fontotfdir, OTF)
XORG_FONTSUBDIR(FONTTTFDIR, fontttfdir, TTF)
XORG_FONTSUBDIR(FONTTYPE1DIR, fonttype1dir, Type1)
XORG_FONTSUBDIR(FONT75DPIDIR, font75dpidir, 75dpi)
XORG_FONTSUBDIR(FONT100DPIDIR, font100dpidir, 100dpi)

DEFAULT_FONT_PATH = "${FONTMISCDIR}/,${FONTTTFDIR}/,${FONTOTFDIR}/,${FONTTYPE1DIR}/,${FONT100DPIDIR}/,${FONT75DPIDIR}/"
DEFAULT_FONT_PATH = '${sysconfdir}/X11/fontpath.d'

FSERRORS = '/var/log/xfs.log'

configure_file(
    input:  'config.in',
    output: 'config',
    configuration: xfs_config,
)

install_data('config',
  install_dir: dir_sysconf / 'X11' / 'fs',
)