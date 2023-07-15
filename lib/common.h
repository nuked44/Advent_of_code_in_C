#ifndef COMMON
#define COMMON

// returns a ptr to a buffer with the contents of the file
char *load_file(char const *path);
// returns the smaller of 2 values
int min(int lparam, int rparam);
// returns the bigger of 2 values
int max(int lparam, int rparam);
// swaps 2 integers
void swap_int(int *lparam, int *rparam);
// takes &str and swaps their pointers 
void swap_str(char **lparam, char **rparam);
// returns the factorial (n!) of n
long factorial(long n);
// heaps algorithm for permutation
// puts all permutations of orig_array in dest_array
void heap_permutations(char **array, int size_of_array, int n, char ***dest_array);

#endif