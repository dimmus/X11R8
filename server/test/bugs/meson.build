dep_xcb = dependency('xcb', required: false)
dep_xcb_image = dependency('xcb-image', required: false)
dep_xcb_util = dependency('xcb-util', required: false)

if get_option('xvfb')
    xvfb_args = [
        xvfb_server.full_path(),
        '-screen',
        'scrn',
        '1280x1024x24'
    ]

    if dep_xcb.found() and dep_xcb_image.found() and dep_xcb_util.found() and get_option('xvfb') and get_option('xephyr') and build_glamor
        bug1354 = executable('bug1354', 'bug1354.c', dependencies: [dep_xcb, dep_xcb_image, dep_xcb_util])
        foreach testsuite: [
            ['-gl', ':201', ':200'],
            ['-gles2', ':199', ':198'],
            ['-gles3', ':203', ':202']
        ]
            test('bug1354' + testsuite[0],
                    simple_xinit,
                    args: [simple_xinit.full_path(),
                        bug1354.full_path(),
                        '-t', testsuite[1],'-r', testsuite[2],
                        '----',
                        xephyr_server.full_path(),
                        '-glamor',
                        '-schedMax', '2000',
                        testsuite[1],
                        '--',
                        xvfb_args,
                        testsuite[2]
                        ],
                    suite: 'xephyr-glamor' + testsuite[0],
                    timeout: 300,
                )
        endforeach
    endif
endif