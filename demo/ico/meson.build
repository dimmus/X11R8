#define LocalThreadsDefines -DMULTITHREAD
#include <Threads.tmpl>

conf.set('MULTIBUFFER', 1)
conf.set('XTHREADS', 1)

executable('ico', 'ico.c',
    dependencies: [libxmu, libxext, libx11, libxt, dep_m],
    include_directories: inc_lib,
    install: false
)