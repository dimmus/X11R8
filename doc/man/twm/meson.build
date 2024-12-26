custom_target(
    'twm.1',
    build_by_default: true,
    capture: true,
    input: files('twm.man'),
    output: 'twm.1',
    install: true,
    install_dir: get_option('mandir'),
    command: [
        exe_sed,
        '@INPUT@',
        '-e', 's#__appmansuffix__#1#g',
        '-e', 's#__miscmansuffix__#7#g',
        '-e', 's#__datadir__#@0@#g'.format(
            get_option('prefix') / get_option('datadir')
        ),
        '-e', 's#__projectroot__#@0@#g'.format(
            meson.project_source_root()
        ),
        '-e', 's#__xorgversion__#"twm @0@" "X Version 11"#g'.format(
            meson.project_version()
        ),
    ],
)
