#!/usr/bin/env python3

import os
import shutil
import sys

if len(sys.argv) != 3:
    print("Usage: install_generated_files.py <help_build_subdir> <install_dir>")
    sys.exit(1)

help_build_dir = sys.argv[1]
install_dir = sys.argv[2]

def copy_subdirectories(src_dir, dest_dir):
    items = os.listdir(src_dir)

    for item in items:
        src_item = os.path.join(src_dir, item)

        if os.path.isdir(src_item):
            dest_item = os.path.join(dest_dir, item)
            shutil.copytree(src_item, dest_item, dirs_exist_ok=True)

copy_subdirectories(help_build_dir, install_dir)
