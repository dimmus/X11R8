inc_xcvt = include_directories('include')

subdir('include')
subdir('lib')
subdir('cvt')

pkg.generate(name: 'libxcvt',
        libraries: libxcvt,
        version: ver_xcvt,
        description: 'A Library to generate VESA CVT standard timing modelines.')

libxcvt = declare_dependency(
        link_with: libxcvt,
        include_directories: inc_xcvt
)
