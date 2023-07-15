#!/usr/bin/env python3

import os
import re
import sys
from pathlib import Path

class print_colors:
    OK = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

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

def make_input_file(year: int, day: int):
    input_file = open(f"./inputs/input_{year}_{day:02}.txt", "w")
    input_file.write(f"Get input from 'https://adventofcode.com/{year}/day/{day}/input'")
    input_file.close()

def findWholeWord(w):
    return re.compile(r'\b({0})\b'.format(w)).search

def insert_entry(year: int, day: int):
    entries_header = "./src/entries.h"
    with open(entries_header, "r") as f:
        entryfile = f.readlines()

    if not findWholeWord(f"run{year}_{day:02}")(entryfile[4]):
        entryfile[4] = f"{entryfile[4][:-2]}, run{year}_{day:02}{entryfile[4][-2:]}"
        entryfile[-2] = f"#include \"{year}/{year}_{day:02}.h\"\n\n"
        print(f"{print_colors.OK}added function to entry{print_colors.ENDC}")
    else:
        print(f"{print_colors.FAIL}function entry already exists{print_colors.ENDC}")

    with open(entries_header, "w") as f:
        contents = "".join(entryfile)
        f.write(contents)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <year> <day>")
    year = int(sys.argv[1])
    day = int(sys.argv[2])
    
    Path(f"./src/{year}").mkdir(exist_ok=True)
    Path(f"./obj/{year}").mkdir(exist_ok=True)
    if not Path(f"./src/{year}/{year}_{day:02}.h").is_file():
        make_header(year, day)
        print(f"{print_colors.OK}added ./src/{year}/{year}_{day:02}.h{print_colors.ENDC}")
    else:
        print(f"{print_colors.FAIL}file ./src/{year}/{year}_{day:02}.h already exists{print_colors.ENDC}")
    if not Path(f"./src/{year}/{year}_{day:02}.c").is_file():
        make_c_file(year, day)
        print(f"{print_colors.OK}added ./src/{year}/{year}_{day:02}.c{print_colors.ENDC}")
    else:
        print(f"{print_colors.FAIL}file ./src/{year}/{year}_{day:02}.c already exists{print_colors.ENDC}")
    if not Path(f"./inputs/input_{year}_{day:02}.txt").is_file():   
        make_input_file(year, day)
        print(f"{print_colors.OK}added ./inputs/input_{year}_{day:02}.txt{print_colors.ENDC}")
    else:
        print(f"{print_colors.FAIL}file ./inputs/input_{year}_{day:02}.txt already exists{print_colors.ENDC}")
    insert_entry(year, day)
    os.system("rm -f aoc_c obj/main.o")

