src = [
  'xshmfence_test',
]

foreach test : src
  test('xshm - ' + test,
    executable(test, test + '.c',
      include_directories: inc_lib,
      dependencies: [xproto, libxshmfence],
    )
  )
endforeach