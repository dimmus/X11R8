# Copyright © 2018 Intel Corporation

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# version: '2024.1'

pcs = [
    'applewmproto',
    'bigreqsproto',
    'compositeproto',
    'damageproto',
    'dmxproto',
    'dpmsproto',
    'dri2proto',
    'dri3proto',
    'fixesproto',
    'fontsproto',
    'glproto',
    'inputproto',
    'kbproto',
    'presentproto',
    'randrproto',
    'recordproto',
    'renderproto',
    'resourceproto',
    'scrnsaverproto',
    'videoproto',
    'xcmiscproto',
    'xextproto',
    'xf86bigfontproto',
    'xf86dgaproto',
    'xf86driproto',
    'xf86vidmodeproto',
    'xineramaproto',
    'xproto',
    'xwaylandproto',
]

pc_data = configuration_data()
pc_data.set('prefix', dir_prefix)
# meson does not allow installing the includedir outside of the prefix
pc_data.set('includedir', '${prefix}' / dir_include)

foreach pc: pcs
    configure_file(
        input: pc + '.pc.in',
        output: pc + '.pc',
        install_dir: dir_data / 'pkgconfig',
        configuration: pc_data,
    )
endforeach

if get_option('build-xproto-legacy')
    legacy_pcs = [
        'evieproto',
        'fontcacheproto',
        'lg3dproto',
        'printproto',
        'trapproto',
        'windowswmproto',
        'xcalibrateproto',
        'xf86miscproto',
        'xf86rushproto',
        'xproxymngproto',
    ]
    foreach pc: legacy_pcs
        configure_file(
            input: pc + '.pc.in',
            output: pc + '.pc',
            install_dir: dir_data / 'pkgconfig',
            configuration: pc_data,
        )
    endforeach
endif

xproto = declare_dependency(
    include_directories: inc_lib
)

keysymfile = dir_source / 'include' / 'X11' / 'XF86keysym.h'

if WITH_TESTS
# XXX: needs python module 'libevdev'
test('xproto - evdev-keysym',
    find_program('scripts' / 'keysym-generator.py'),
    args: ['-v', '--header', keysymfile, 'verify'],

)
endif