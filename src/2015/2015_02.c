#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../common.h"

void _2015_02_p1(char *input) {
    char *buffer = (char *)malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    int total = 0;
    char *save_ptr = NULL;
    char *line_save_ptr = NULL;
    char *line = strtok_r(buffer, "\n", &save_ptr);

    while (line) {
        int length = atoi(strtok_r(line, "x", &line_save_ptr));
        int width = atoi(strtok_r(NULL, "x", &line_save_ptr));
        int height = atoi(strtok_r(NULL, "x", &line_save_ptr));

        int lw = length * width;
        int wh = width * height;
        int hl = height * length;

        int lowest = min(lw, min(wh, hl));

        total += 2 * (lw + wh + hl) + lowest;
        line = strtok_r(NULL, "\n", &save_ptr);
    }
    free(buffer_adress);
    printf("%d\n", total);
}

void _2015_02_p2(char *input) {
    int total = 0;
    char *save_ptr = NULL;
    char *line_save_ptr = NULL;
    char *line = strtok_r(input, "\n", &save_ptr);

    while (line) {
        int length = atoi(strtok_r(line, "x", &line_save_ptr));
        int width = atoi(strtok_r(NULL, "x", &line_save_ptr));
        int height = atoi(strtok_r(NULL, "x", &line_save_ptr));

        int lowest = min(length, min(width, height));
        int second_lowest =
            ((length + width + height) - lowest) - max(length, max(width, height));

        total += (2 * (lowest + second_lowest)) + (length * width * height);
        line = strtok_r(NULL, "\n", &save_ptr);
    }
    printf("%d\n", total);
}

void run2015_02(char *input) {
    printf("Part 1: ");
    _2015_02_p1(input);
    printf("Part 2: ");
    _2015_02_p2(input);
}