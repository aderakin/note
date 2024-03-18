#!/usr/bin/env python3

import subprocess
import sys 
import re 
import os

[src] = [arg for arg in sys.argv[1:] if arg.endswith('.cpp')]
argv = [arg for arg in sys.argv[1:] if arg != src]
src_tmp = src.rsplit('.', 1)[0] + '.tmp.cpp'
includes, lines = [], []

with open(src, 'r', encoding='utf-16') as infile:
    for line in infile:
        if re.match(r"#include\s*<[^>]*>", line):
            includes.append(line)
        else:
            lines.append(line)

with open(src_tmp, 'w') as tmpfile:
    tmpfile.writelines(lines)

output = subprocess.check_output(['g++', '-E', '-C', src_tmp] + argv).decode('utf-8')
# Remove preprocessor artifacts.
lines = [line + '\n' for line in output.splitlines() 
         if not line.startswith('# ')]

# At this point you could write your own post-processing routine.
# This perticular one removes duplicate "using namespace ...;" 
# and duplicate empty lines.
nlines = []
found_namespaces = set()
for line in lines:
    if not line.strip() and nlines and not nlines[-1].strip():
        continue
    if line.strip() == ';':
        continue
    match = re.match(r"using\s+namespace\s+([^;]+);", line)
    if match:
        match = match[1] 
        if match in found_namespaces:
            continue 
        found_namespaces.add(match)
    nlines.append(line)
lines = nlines
output = "".join(includes + lines)

os.remove(src_tmp)
print(output)