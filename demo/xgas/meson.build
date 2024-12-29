src = files(
    'main.c',
    'dynamics.c',
    'chamber.c',
    'timestep.c',
    'molecule.c',
    'util.c',
    'help.c',
    'Gas.c',
    'doc.c',
    'quick.c',
    'man.c',
)
executable('xgas', src,
    dependencies: [libxmu, libxext, libx11, libxt, libxaw, dep_m],
    include_directories: inc_x11,
    install: false
)