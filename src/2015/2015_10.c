#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void look_and_say(char *input, char *buffer) {
    int input_len = strlen(input);
    char *temp_buffer = calloc(input_len + 1, 1);
    int ammout_char_in_row = 1;
    char next = '\0';
    char current = '\0';
    for (size_t i = 0; input[i + 1] != '\0'; i++) {
        next = input[i + 1];
        current = input[i];
        if (next == current) {
            ammout_char_in_row++;
        } else {
            int len = sprintf(temp_buffer, "%d%c", ammout_char_in_row, current);
            temp_buffer[len + 1] = '\0';
            strcat(buffer, temp_buffer);
            ammout_char_in_row = 1;
        }
    }
    sprintf(temp_buffer, "%d%c", ammout_char_in_row, next);
    strcat(buffer, temp_buffer);
    free(temp_buffer);
}

void _2015_10_p1(char *input) {
    char *input_buffer = malloc(strlen(input) + 1);
    strcpy(input_buffer, input);
    char *buffer = calloc(strlen(input) + 1, 2);
    for (size_t _ = 0; _ < 40; _++) {
        look_and_say(input_buffer, buffer);
        input_buffer = realloc(input_buffer, strlen(buffer) + 1);
        strcpy(input_buffer, buffer);
        buffer = realloc(buffer, (strlen(buffer) + 1) * 2);
        buffer[0] = '\0';
    }
    printf("%zu\n", strlen(input_buffer));
    free(input_buffer);
    free(buffer);
}

void _2015_10_p2(char *input) {
    int input_len = strlen(input);
    char *input_buffer = malloc(input_len + 1);
    strcpy(input_buffer, input);
    char *buffer = calloc(input_len + 1, 2);
    for (size_t _ = 0; _ < 50; _++) {
        look_and_say(input_buffer, buffer);
        input_buffer = realloc(input_buffer, strlen(buffer) + 1);
        strcpy(input_buffer, buffer);
        buffer = realloc(buffer, (strlen(buffer) + 1) * 2);
        buffer[0] = '\0';
    }
    printf("%zu\n", strlen(input_buffer));
    free(input_buffer);
    free(buffer);
}

void run2015_10(char *input) {
    printf("Part 1: ");
    _2015_10_p1(input);
    printf("Part 2: ");
    _2015_10_p2(input);
}