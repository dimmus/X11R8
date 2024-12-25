# SPDX-License-Identifier: MIT
# Copyright © 2022 Intel Corporation

xorg = import('unstable-xorg')

foreach m : ['Xv', 'XvCreateImage', 'XvFreeAdaptorInfo', 'XvFreeEncodingInfo',
             'XvGetPortAttribute', 'XvGetStill', 'XvGetVideo', 'XvGrabPort',
             'XvListImageFormats', 'XvPortNotify', 'XvPutImage', 'XvPutStill',
             'XvPutVideo', 'XvQueryAdaptors', 'XvQueryBestSize',
             'XvQueryEncodings', 'XvQueryExtension', 'XvQueryPortAttributes',
             'XvSelectPortNotify', 'XvSelectVideoNotify', 'XvSetPortAttribute',
             'XvShmCreateImage', 'XvShmPutImage', 'XvStopVideo', 'XvUngrabPort',
             'XvVideoNotify']
  xorg.format_man('@0@.man'.format(m), 'lib')
endforeach