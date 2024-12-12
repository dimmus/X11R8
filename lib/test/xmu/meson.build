src = [
  'CursorName',
  'EditResStream',
  'Lower',
  'ReadBitmapData',
  'reallocarray',
  'StrToBS',
  'StrToGrav',
  'StrToJust',
  'StrToLong',
  'StrToOrnt',
  'StrToShap',
]

foreach test : src
  test('xmu - ' + test,
    executable(test, test + '.c',
      include_directories: [inc_lib, inc_x11],
      dependencies: [libxmu, libxt],
    )
  )
endforeach