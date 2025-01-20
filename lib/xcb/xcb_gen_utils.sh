#!/bin/bash

# (Re)generate ERRORS util files
echo -n "[xcb-utils] Gererating ERRORS util files ... "
cd utils/errors
python3 extensions.py extensions.c ../../proto/src/*.xml
echo "Done"
cd ../../

# (Re)generate WM util files
echo -n "[xcb-utils] Gererating WM util files ... "
cd utils/wm
m4 ewmh.c.m4 > ewmh.c
m4 xcb_ewmh.h.m4 > xcb_ewmh.h
echo "Done"
cd ../../