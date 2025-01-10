srcs_xorg_loader = [
    'loader.c',
    'loadmod.c',
]

xorg_loader = static_library('xorg_loader',
    srcs_xorg_loader,
    include_directories: inc_server,
    dependencies: [dep_common, dep_dl],
    c_args: xorg_c_args,
)

xorg_symbol_test = executable('xorg_symbol_test',
    'symbol-test.c',
    dependencies: dep_dl,
)
