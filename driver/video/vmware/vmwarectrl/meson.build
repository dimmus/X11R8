exe_vmwctrl = executable('vmwarectrl',
    ['vmwarectrl.c', 'libvmwarectrl.c'],
    include_directories: inc_vmware,
	dependencies: [dep_int_vmware, dep_ext_vmware],
	install: true,
    implib: true,
)