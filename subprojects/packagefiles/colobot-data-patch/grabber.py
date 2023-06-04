#!/usr/bin/env python3
# Description: This script takes a globbing expression as input and prints the files it finds.

import glob
import os
import sys

if len(sys.argv) != 2:
    print("Usage: grabber.py <globbing-expression>")
    sys.exit(1)

glob_expression = sys.argv[1]

if 'MESON_SOURCE_ROOT' in os.environ:
    source_root = os.getenv('MESON_SOURCE_ROOT')
    subdir = os.getenv('MESON_SUBDIR')
    os.chdir(os.path.join(source_root, subdir))

files = glob.glob(glob_expression)

for file in files:
    print(file)

