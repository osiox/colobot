#!/usr/bin/env python3

import os
import shutil
import sys

def copy_file(src, target):
    # Check if the target is a directory
    if os.path.isdir(target):
        print("Error: Target already exists and is a directory.")
        sys.exit(1)

    parent_dir = os.path.dirname(target)
    if not os.path.exists(parent_dir):
        os.makedirs(parent_dir)

    shutil.copy2(src, target)

if __name__ == "__main__":
    # Check if the number of arguments is correct
    if len(sys.argv) != 3:
        print("Usage: install_compiled_translations.py <src> <target>")
        sys.exit(1)

    src = sys.argv[1]
    target = sys.argv[2]

    print(f"Installing {src} to {target}")
    copy_file(src, target)

