dirs = [
    'compat',
    'geometry',
    'keycodes',
    'rules',
    'symbols',
    'types',
]

foreach dir: ['compat', 'geometry', 'keycodes', 'types']
    install_subdir(dir, install_dir: dir_data / 'X11' / 'xkb')
endforeach