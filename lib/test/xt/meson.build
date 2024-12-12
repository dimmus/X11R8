src = [
  'Alloc',
  'Converters',
  'Event',
]

foreach test : src
  test('xt - ' + test,
    executable(test, test + '.c',
      include_directories: inc_lib,
      dependencies: [xproto, libxmu, libxt],
    )
  )
endforeach