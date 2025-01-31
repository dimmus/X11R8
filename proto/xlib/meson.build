ver_xproto = '2024.1'

h_check += ['sys/select.h', 'sys/param.h', 'sys/types.h', 'sys/time.h']

proto_pc = [
  ['AppleWM',       '1.4.2'   ],
  ['BigReqs',       '1.1.2'   ],
  ['Composite',     '0.4.2'   ], # Ext
  ['Damage',        '1.2.1'   ],
  ['DMX',           '2.3.1'   ],
  ['DPMS',          '1.2'     ],
  ['DRI2',          '2.8'     ],
  ['DRI3',          '1.4'     ],
  ['Fixes',         '6.1'     ],
  ['Fonts',         '2.1.3'   ],
  ['GL',            '1.4.17'  ],
  ['Input',         '2.3.99.2'],
  ['KB',            '1.0.7'   ],
  ['Present',       '1.4'     ],
  ['Randr',         '1.6.0'   ],
  ['Record',        '1.14.2'  ],
  ['Render',        '0.11.1'  ],
  ['Resource',      '1.2.0'   ],
  ['ScrnSaver',     '1.2.3'   ],
  ['Video',         '2.3.3'   ],
  ['XCMisc',        '1.2.2'   ],
  ['XExt',          '7.3.0'   ],
  ['XF86BigFont',   '1.2.0'   ],
  ['XF86DGA',       '2.1'     ],
  ['XF86DRI',       '2.1.1'   ],
  ['XF86VidMode',   '2.3.1'   ],
  ['Xinerama',      '1.2.1'   ],
  ['Xwayland',      '1.0'     ],
]

if get_option('build-xproto-legacy')
proto_pc += [
  ['EvIE',          '1.1.1'   ], # Ext
  ['Fontcache',     '0.1.3'   ],
  ['Lg3d',          '5.0'     ],
  ['Print',         '1.0.5'   ],
  ['Trap',          '3.4.3'   ], # Requires: xt
  ['WindowsWM',     '1.0.4'   ],
  ['XCalibrate',    '0.1.0'   ],
  ['XF86Misc',      '0.9.3'   ],
  ['XF86Rush',      '1.1.2'   ],
  ['XProxyMng',     '1.0.3'   ],
]
endif

# pc_data.set('prefix', dir_prefix)
# pc_data.set('includedir', '${prefix}' / dir_include)

foreach proto : proto_pc
pkg.generate(
  name: '@0@Proto'.format(proto[0]),
  description: '@0@ extension headers'.format(proto[0]),
  version: proto[1],
)
endforeach

pkg.generate(
  name: 'Xproto',
  description: 'Xproto headers',
  version: '7.0.33',
)

xproto = declare_dependency(
    include_directories: inc_lib
)

keysymfile = dir_source / 'include' / 'X11' / 'XF86keysym.h'

if WITH_TESTS # needs python module 'libevdev'
test('xproto - evdev-keysym',
    find_program('keysym-generator.py'),
    args: ['-v', '--header', keysymfile, 'verify'],
)
endif