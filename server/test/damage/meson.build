dep_xcb = dependency('xcb', required: false)
dep_xcb_damage = dependency('xcb-damage', required: false)

if get_option('xvfb')
    if dep_xcb.found() and dep_xcb_damage.found()
        damage_primitives = executable('damage-primitives', 'primitives.c', dependencies: [dep_xcb, dep_xcb_damage])
        test('damage-primitives', simple_xinit, args: [damage_primitives, '--', xvfb_server])
    endif
endif
