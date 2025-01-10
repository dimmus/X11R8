src = [
  'rgb',
  'XpmCreate',
  'XpmMisc',
  'XpmRead',
  'XpmWrite',
]

foreach test : src
  test('xpm - ' + test,
    executable(test, test + '.c',
      include_directories: inc_lib,
      dependencies: [xproto, libxpm],
    )
  )
endforeach