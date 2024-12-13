
foreach man: [
  'DMX', 'DMXAddInput', 'DMXAddScreen', 'DMXChangeDesktopAttributes', 'DMXChangeScreensAttributes', 
  'DMXForceWindowCreation', 'DMXGetDesktopAttributes', 'DMXGetInputAttributes', 'DMXGetInputCount', 
  'DMXGetScreenAttributes', 'DMXGetScreenCount', 'DMXGetWindowAttributes', 'DMXQueryExtension', 
  'DMXQueryVersion', 'DMXRemoveInput', 'DMXRemoveScreen', 'DMXSync', 
  ]
  custom_target('@0@'.format(man),
    input: '@0@.man'.format(man),
    output: '@0@.3'.format(man),
    command: [
      prog_sed,
      '-e', 's/__xorgversion__/"libdmx @0@" "X Version 11"/'.format(ver_dmx),
      '-e', 's/__libmansuffix__/3/',
      '-e', 's/__vendorversion__/1/',
      '@INPUT@',
    ],
    capture: true,
    install: true,
    install_dir: dir_man / 'man3',
  )
endforeach
