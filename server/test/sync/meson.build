if get_option('xvfb')
    sync = executable('sync', 'sync.c', dependencies: libxcb)
    test('sync', simple_xinit, args: [sync, '--', xvfb_server])
endif
