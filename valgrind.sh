# script for checking for memory leaks

# usage: ./valgrind.sh <year> <day>

# measured times are not accurate while using this script

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./aoc_c $1 $2