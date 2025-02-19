ver_xaw3dm = '0.3.1'

inc_xaw3dm = [inc_lib, include_directories('.')]

dep_int_xaw3dm = [libx11, xproto, libxext, libxt, libxmu, libxpm, libi18n, libxaw3dn]

src = files(
  'MwApplicationShell.c',
  'MwCanvas.c',
  'MwCheck.c',
  'MwCheckME.c',
  'MwCombo.c',
  'MwDialog.c',
  'MwFilesel.c',
  'MwFrame.c',
  'MwGcs.c',
  'MwHandle.c',
  'MwImage.c',
  'MwListTree.c',
  'MwNotebook.c',
  'MwRudegrid.c',
  'MwRuler.c',
  'MwSpinner.c',
  'MwSlider.c',
  'MwVSlider.c',
  'MwTabs.c',
  'MwTabstop.c',
  'MwTabbing.c',
  'MwTextField.c',
  'MwTooltip.c',
  'MwBase.c',
  'MwBaseComp.c',
  'MwBaseConst.c',
  'MwBaseME.c',
  'MwButton.c',
  'MwLineME.c',
  'MwLabelME.c',
  'MwMBButton.c',
  'MwMenu.c',
  'MwMenuBar.c',
  'MwMenuButton.c',
  'MwNws.c',
  'MwPopText.c',
  'MwRow.c',
  'MwSButton.c',
  'MwSubME.c',
  'MwTraverse.c',
  'MwAnimator.c',
  'MwRichtext.c',
  'MwTable.c',
  'MwDND.c',
  'MwUtils.c',
  'MwXutils.c',
  'MwFormat.c',
  'MwXFormat.c',
  'MwXCC.c',
)

lib = library('Mowitz', src,
  c_args: ['-Wno-discarded-qualifiers', '-Wno-unused-function'],
  include_directories: inc_xaw3dm,
  dependencies: dep_int_xaw3dm,
  version: '0.0.1',
  install: true,
)

libxaw3dm = declare_dependency(
  link_with: lib,
  include_directories: inc_xaw3dm,
)

pkg.generate(lib,
  description: 'Mowitz (More widgets) library',
  version: ver_xaw3dm,
  filebase: 'xrender',
  requires: ['xproto', 'xmu', 'xt'],
  requires_private: ['x11', 'xext']
)

# mowitz-config: mowitz-config.sh Makefile
# 	./mowitz-config.sh "-I$(includedir) @CFLAGS_CFG@" \
# 		"-L$(libdir) -lMowitz @LDFLAGS_CFG@" \
# 		"@VERSION@" > mowitz-config
# 	chmod 0755 mowitz-config