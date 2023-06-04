#!/usr/bin/env python3

import os
import sys

def remove_date(input_file, output_file):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    with open(output_file, 'w') as file:
        for line in lines:
            if line.startswith('"POT-Creation-Date:'):
                line = line.split(':')[0] + ': DATE\\n"'
            file.write(line)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: update_pot.py input_file output_file")
        sys.exit(1)

    if 'MESON_SOURCE_ROOT' in os.environ:
        source_root = os.getenv('MESON_SOURCE_ROOT')
        subdir = os.getenv('MESON_SUBDIR')
        os.chdir(os.path.join(source_root, subdir))

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    remove_date(input_file, output_file)
