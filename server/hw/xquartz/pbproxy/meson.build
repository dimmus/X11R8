build_standalone_pbproxy = get_option('xpbproxy')

pbproxy_defs = [
    '-DXQUARTZ_DATA_DIR="@0@"'.format(xquartz_data_dir),
    bundle_id_def
]
if build_standalone_pbproxy
    pbproxy_defs += ['-DSTANDALONE_XPBPROXY']
endif

dep_libapplewm = dependency('applewm', version: '>=1.4')

libxpbproxy = static_library('xpbproxy',
    ['../NSUserDefaults+XQuartzDefaults.m',
     'main.m',
     'x-input.m',
     'x-selection.m'],
    include_directories: ['..'],
    dependencies: [xproto, dep_libapplewm, libxfixes, libx11],
    objc_args: pbproxy_defs,
)

cocoa = dependency('Cocoa', method: 'extraframework')

# standalone xpbproxy
if build_standalone_pbproxy
    executable('xpbproxy',
        'app-main.m',
        link_with: libxpbproxy,
        dependencies: [cocoa, libx11],
        objc_args: pbproxy_defs,
        install: true,
    )
endif
