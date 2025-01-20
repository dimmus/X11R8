if get_option('xvfb')
    requestlength = executable('request-length', 'request-length.c', dependencies: dep_xcb)
    test('request-length', simple_xinit, args: [requestlength, '--', xvfb_server])
endif
