if get_option('xvfb')
    damage_primitives = executable('damage-primitives', 'primitives.c', dependencies: libxcb)
    test('Server - damage-primitives', simple_xinit, args: [damage_primitives, '--', xvfb_server])
endif
