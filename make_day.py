#!/usr/bin/env python3

import sys
from pathlib import Path

def make_header(year: int, day: int):
    header = open(f"./src/{year}/{year}_{day:02}.h", "w")
    header.write(f"#ifndef day{year}{day:02}\n#define day{year}{day:02}\n\nvoid run{year}_{day:02}(char *);\n\n#endif")
    header.close()

def make_c_file(year: int, day: int):
    header = open(f"./src/{year}/{year}_{day:02}.c", "w")
    header.write(f"""#include <stdio.h>

void _{year}_{day:02}_p1(char *input){{
    printf("\\n");
}}

void _{year}_{day:02}_p2(char *input){{
    printf("\\n");
}}

void run{year}_{day:02}(char *input) {{
    printf("Part 1: ");
    _{year}_{day:02}_p1(input);
    printf("Part 2: ");
    _{year}_{day:02}_p2(input);
}}""")
    header.close()

if __name__ == "__main__":
    year = int(sys.argv[1])
    day = int(sys.argv[2])
    if Path(f"./src/{year}/{year}_{day:02}.c").is_file():
        print(f"file: {year}_{day}.c already exists")
        exit()
    Path(f"./src/{year}").mkdir(exist_ok=True)
    Path(f"./obj/{year}").mkdir(exist_ok=True)
    make_header(year, day)
    make_c_file(year, day)


