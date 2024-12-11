dep_xcb = dependency('xcb', required: false)
dep_xcb_xinput = dependency('xcb-xinput', required: false)

if get_option('xvfb')
    if dep_xcb.found() and dep_xcb_xinput.found()
        requestlength = executable('request-length', 'request-length.c',
                                   dependencies: [dep_xcb, dep_xcb_xinput])
        test('request-length', simple_xinit, args: [requestlength, '--', xvfb_server])
    endif
endif
