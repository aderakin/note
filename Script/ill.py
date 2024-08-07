#!/usr/bin/env python3
import sys
import os
import os.path

USED = set()
INCLUDE_PATHS = None


def include_target(file, path):
    for include_path in [os.path.dirname(file), *INCLUDE_PATHS]:
        candidate = os.path.join(include_path, path)
        if os.path.isfile(candidate):
            return candidate
    return None


def dfs(file):
    if file in USED:
        return
    USED.add(file)
    with open(file, "r", encoding='utf=16') as f:
        for line in f:
            if line.startswith("#include "):
                path = include_target(file, line[8:].strip("\n\r \"<>"))
                if path is not None:
                    dfs(path)
                else:
                    print(line, end='')
            else:
                print(line, end='')


def main():
    global INCLUDE_PATHS
    INCLUDE_PATHS = sys.argv[:-1]
    dfs(sys.argv[-1])


if __name__ == '__main__':
    main()