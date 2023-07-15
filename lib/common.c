#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "common.h"

char *load_file(char const *path) {
    char *buffer = 0;
    long length;
    FILE *f = fopen(path, "r");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc((length + 1) * sizeof(char));
        if (buffer) {
            fread(buffer, sizeof(char), length, f);
        }
        fclose(f);
    }
    buffer[length] = '\0';
    return buffer;
}

int min(int lparam, int rparam) { return lparam < rparam ? lparam : rparam; }

int max(int lparam, int rparam) { return lparam > rparam ? lparam : rparam; }

void swap_int(int *lparam, int *rparam) {
    int temp = *lparam;
    *lparam = *rparam;
    *rparam = temp;
}

void swap_str(char **lparam, char **rparam) {
    char *temp = *lparam;
    *lparam = *rparam;
    *rparam = temp;
}

long factorial(long n) {
    long fact = 1;
    for (long i = 1; i <= n; i++) {
        if (__builtin_smull_overflow(fact, i, &fact))
            return -1;
    }
    return fact;
}

static long _permutation_idx = 0;
static void move_permutations_to_dest_array(char **array, int size_of_array, char ***dest_array) {
    dest_array[_permutation_idx] = calloc(size_of_array, sizeof(char *));
    for (size_t i = 0; (i < size_of_array); i++) {
        dest_array[_permutation_idx][i] = malloc(strlen(array[i]) + 1);
        strcpy(dest_array[_permutation_idx][i], array[i]);
    }
    _permutation_idx++;
}

void heap_permutations(char **array, int size_of_array, int n, char ***dest_array) {
    if (n == 1) {
        move_permutations_to_dest_array(array, size_of_array, dest_array);
        return;
    }

    for (int i = 0; i < n; i++) {
        heap_permutations(array, size_of_array, n -1, dest_array);

        // if size is odd, swap 0th i.e (first) and
        // (size-1)th i.e (last) element
        if (n % 2 == 1)
            swap_str(&array[0], &array[n - 1]);

        // If size is even, swap ith and
        // (size-1)th i.e (last) element
        else
            swap_str(&array[i], &array[n - 1]);
    }
}