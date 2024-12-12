src = [
    'list',
    'menu',
    'pane',
    'repeater',
    'scrollbar',
    'simple',
    'strip',
    'toggle',
    'viewport',
    'xawhisto',
]

foreach test : src
  test(test,
    executable(test, test + '.c',
      include_directories: inc_lib,
      dependencies: [xproto, libxaw, libxt, libxmu],
    )
  )
endforeach