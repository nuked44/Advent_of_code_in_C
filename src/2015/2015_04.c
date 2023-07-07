#include <stdio.h>

#include "../../lib/md5.h"

void _2015_04_p1(char *input) {
    char string_buffer[100] = {};
    for (size_t i = 0; i < SIZE_MAX; i++) {
        uint8_t result[16];
        snprintf(string_buffer, 100, "%s%zu", input, i);
        md5String(string_buffer, result);

        if ((result[0] + result[1]) == 0 && result[2] <= 0xf) {
            printf("%zu\n", i);
            break;
        }
    }
}

void _2015_04_p2(char *input) {
    char string_buffer[100] = {};
    for (size_t i = 0; i < SIZE_MAX; i++) {
        uint8_t result[16];
        snprintf(string_buffer, 100, "%s%zu", input, i);
        md5String(string_buffer, result);

        if ((result[0] + result[1] + result[2]) == 0) {
            printf("%zu\n", i);
            break;
        }
    }
}

void run2015_04(char *input) {
    printf("Part 1: ");
    _2015_04_p1(input);
    printf("Part 2: ");
    _2015_04_p2(input);
}