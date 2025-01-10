custom_target(
    'twm.1',
    build_by_default: true,
    capture: true,
    input: files('twm.man'),
    output: 'twm.1',
    install: true,
    install_dir: dir_man,
    command: [
        exe_sed,
        '@INPUT@',
        '-e', 's#__appmansuffix__#1#g',
        '-e', 's#__miscmansuffix__#7#g',
        '-e', 's#__datadir__#@0@#g'.format(dir_data),
        '-e', 's#__projectroot__#@0@#g'.format(dir_source),
        '-e', 's#__xorgversion__#"twm @0@" "X Version 11"#g'.format(meson.project_version()),
    ],
)
