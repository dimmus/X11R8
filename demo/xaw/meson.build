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

foreach name : src
  executable(name, name + '.c',
    include_directories: inc_lib,
    dependencies: [xproto, libxaw, libxt, libxmu],
  )
endforeach