subdir('include')

lib = library('xcvt', 'libxcvt.c',
    include_directories: inc_lib,
    version: ver_xcvt,
    install: true
)

libxcvt = declare_dependency(
    link_with: lib,
    include_directories: inc_lib
)

executable('cvt', 'cvt.c',
    include_directories: inc_lib,
    link_with: lib,
    dependencies: dep_m,
    install: true
)

pkg.generate(
    name: 'libxcvt',
    libraries: libxcvt,
    version: ver_xcvt,
    description: 'A Library to generate VESA CVT standard timing modelines'
)
