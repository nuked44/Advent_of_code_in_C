#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void look_and_say(const char *input, char **buffer, size_t *buffer_size) {
    int input_size = strlen(input) + 1;
    char *input_c = malloc(input_size);
    strcpy(input_c, input);
    size_t buffer_pos = 0;
    int amount_char_in_row = 1;
    char next = '\0';
    char current = '\0';

    for (size_t i = 0; input_c[i + 1] != '\0'; i++) {
        next = input_c[i + 1];
        current = input_c[i];

        if (next == current) {
            amount_char_in_row++;
        } else {
            // Resize the buffer if needed
            if (buffer_pos + 10 >= *buffer_size) {
                *buffer_size *= 2;
                *buffer = realloc(*buffer, *buffer_size);
            }
            buffer_pos += snprintf(&((*buffer)[buffer_pos]), *buffer_size - buffer_pos, "%d%c", amount_char_in_row, current);
            amount_char_in_row = 1;
        }
    }

    // Resize the buffer if needed
    if (buffer_pos + 10 >= *buffer_size) {
        *buffer_size *= 2;
        *buffer = realloc(*buffer, *buffer_size);
    }
    snprintf(&((*buffer)[buffer_pos]), *buffer_size - buffer_pos, "%d%c", amount_char_in_row, next);
    free(input_c);
}

void _2015_10_p1(const char *input) {
    size_t input_len = strlen(input);
    
    size_t buffer_size = input_len * 2 + 1;
    
    char *result = malloc(buffer_size);
    strcpy(result, input);

    for (size_t _ = 0; _ < 40; _++) {
        look_and_say(result, &result, &buffer_size);
    }

    size_t result_len = strlen(result);
    printf("%zu\n", result_len);
    free(result);
}

void _2015_10_p2(char *input) {
    size_t input_len = strlen(input);
    
    size_t buffer_size = input_len * 2 + 1;
    
    char *result = malloc(buffer_size);
    strcpy(result, input);

    for (size_t _ = 0; _ < 50; _++) {
        look_and_say(result, &result, &buffer_size);
    }

    size_t result_len = strlen(result);
    printf("%zu\n", result_len);
    free(result);
}

void run2015_10(char *input) {
    printf("Part 1: ");
    _2015_10_p1(input);
    printf("Part 2: ");
    _2015_10_p2(input);
}