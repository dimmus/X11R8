f_check += ['realpath']

test('font - xfont - lsfontdir',
  executable('lsfontdir',
    [
      'font-test-utils.c',
      'lsfontdir.c'
    ],
    dependencies: libxfont,
    include_directories: [inc_font, inc_lib],
  )
)
