if get_option('xvfb')
    sync = executable('sync', 'sync.c', dependencies: dep_xcb)
    test('sync', simple_xinit, args: [sync, '--', xvfb_server])
endif
