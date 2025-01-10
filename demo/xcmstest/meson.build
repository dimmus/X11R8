src = files(
    'TekCMS_LT.c',
    'LibTest.c',
    'TestInit.c',
    'TekCMS_TCI.c',
    'TekCMSutil.c',
    'TekCMSglob.c',
    'TekCMS_TCI.c',
)

executable('xcmstest', src,
    dependencies: [libxmu, libxext, libx11, libxt, dep_m, libxcms],
    include_directories: inc_lib,
    install: false
)