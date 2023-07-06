#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

int min(int lparam, int rparam) {
    return lparam < rparam ? lparam : rparam;
}

int max(int lparam, int rparam) {
    return lparam > rparam ? lparam : rparam;
}