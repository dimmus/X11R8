# SPDX-License-Identifier: MIT
# Copyright © 2023 Intel Corporation

prog_sed = find_program('sed')

foreach man: [
  'Xau', 'XauDisposeAuth', 'XauFileName', 'XauGetAuthByAddr', 'XauGetBestAuthByAddr',
  'XauLockAuth', 'XauReadAuth', 'XauUnlockAuth', 'XauWriteAuth'
  ]
  custom_target('@0@'.format(man),
    input: '@0@.man'.format(man),
    output: '@0@.3'.format(man),
    command: [
      prog_sed,
      '-e', 's/__xorgversion__/"libXau @0@" "X Version 11"/'.format(ver_xau),
      '-e', 's/__libmansuffix__/3/',
      '@INPUT@',
    ],
    capture: true,
    install: true,
    install_dir: dir_man / 'man3',
  )
endforeach
