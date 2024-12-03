ver_xcvt = '0.1.2'

inc_xcvt = include_directories('include')

subdir('include')
subdir('lib')
subdir('cvt')

pkg.generate(name : 'libxcvt',
        libraries : libxcvt,
        version : ver_xcvt,
        description : 'A Library to generate VESA CVT standard timing modelines.')

libxcvt_dep = declare_dependency(
        link_with: libxcvt,
        include_directories: inc_xcvt
)
