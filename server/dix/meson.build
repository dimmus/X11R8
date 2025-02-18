srcs_dix = [
    'atom.c',
    'colormap.c',
    'color.c',
    'cursor.c',
    'devices.c',
    'dispatch.c',
    'display.c',
    'dixfonts.c',
    'main.c',
    'dixutils.c',
    'enterleave.c',
    'events.c',
    'eventconvert.c',
    'extension.c',
    'gc.c',
    'gestures.c',
    'getevents.c',
    'globals.c',
    'glyphcurs.c',
    'grabs.c',
    # 'initatoms.c',
    'inpututils.c',
    'pixmap.c',
    'privates.c',
    'property.c',
    'ptrveloc.c',
    'region.c',
    'registry.c',
    'resource.c',
    'selection.c',
    'swaprep.c',
    'swapreq.c',
    'tables.c',
    'touch.c',
    'window.c',
]

atom_generator = generator(
    find_program('generate-atoms'),
    output: '@BASENAME@.c',
    arguments : ['@INPUT@', '@OUTPUT@'])

builtinatoms_src = atom_generator.process('BuiltInAtoms')

dtrace_src = []
if WITH_DTRACE
    dtrace_object = generator(exe_dtrace,
        output: '@BASENAME@.o',
        arguments: ['-G', '-s', '@INPUT@', '-o', '@OUTPUT@']
    )

    dtrace_src += dtrace_object.process(dtrace_tmpl)
endif

dep_dtrace = declare_dependency(sources: [dtrace_src, dtrace_hdr])

libxserver_dix = static_library('libxserver_dix',
    [srcs_dix, builtinatoms_src],
    include_directories: inc_server,
    dependencies: [ dep_dtrace, dep_common, ]
)

libxserver_main = static_library('libxserver_main',
    'stubmain.c',
    include_directories: inc_server,
    dependencies: dep_common,
)

install_data('protocol.txt', install_dir: serverconfigdir)
