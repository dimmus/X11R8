dep_xcb = dependency('xcb', required: false)
dep_xcb_sync = dependency('xcb-sync', required: false)

if get_option('xvfb')
    if dep_xcb.found() and dep_xcb_sync.found()
        sync = executable('sync', 'sync.c', dependencies: [dep_xcb, dep_xcb_sync])
        test('sync', simple_xinit, args: [sync, '--', xvfb_server])
    endif
endif
