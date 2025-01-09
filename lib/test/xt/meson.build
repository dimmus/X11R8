src = [
  'Alloc',
  'Converters',
  'Event',
]

foreach test : src
  test('xt - ' + test,
    executable(test, test + '.c',
      include_directories: inc_x11,
      dependencies: [xproto, libxmu, libxt],
    )
  )
endforeach