src = [
  'list.c',
  'menu.c',
  'pane.c',
  'repeater.c',
  'scrollbar.c',
  'simple.c',
  'strip.c',
  'toggle.c',
  'viewport.c',
  'xawhisto.c',
]

foreach name : src
  executable(name, name,
    include_directories: inc_lib,
    dependencies: [xproto, libxaw, libxt, libxmu],
  )
endforeach