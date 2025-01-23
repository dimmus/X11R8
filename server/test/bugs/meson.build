if get_option('xvfb')
    xvfb_args = [
        xvfb_server.full_path(),
        '-screen',
        'scrn',
        '1280x1024x24'
    ]

    if get_option('xvfb') and get_option('xephyr')
        bug1354 = executable('bug1354', 'bug1354.c', dependencies: [libxcb, libxcb_image, libxcb_util])
        foreach testsuite: [
            ['-gl', ':201', ':200'],
            ['-gles2', ':199', ':198'],
            ['-gles3', ':203', ':202']
        ]
            test('Server - bug1354' + testsuite[0],
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