#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _2015_08_p1(char *input) {
    char *buffer = malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    char *save_ptr = NULL;
    char *line = strtok_r(buffer, "\n", &save_ptr);
    unsigned mem_chars = 0;
    unsigned total_chars = 0;
    while (line) {
        int string_size_mem = 0;
        int string_size = 0;
        char prev = '\0';

        for (int i = 0; line[i] != '\0'; i++) {
            char current = line[i];
            string_size_mem++;
            string_size++;
            if ((prev == '\\') && (current == 'x')) {
                string_size_mem -= 3;
            } else if ((prev == '\\') && (current == '"')) {
                string_size_mem--;
            } else if ((prev == '\\') && (current == '\\')) {
                string_size_mem--;
                current = '\0';
            }
            
            prev = current;
        }
        mem_chars += string_size_mem - 2; // minus outer quotation
        total_chars += string_size;
        line = strtok_r(NULL, "\n", &save_ptr);
    }
    free(buffer_adress);
    printf("%d\n", total_chars - mem_chars);
}

void _2015_08_p2(char *input) {
    char *save_ptr = NULL;
    char *line = strtok_r(input, "\n", &save_ptr);
    unsigned mem_chars = 0;
    unsigned total_chars = 0;
    while (line) {
        int string_size_mem = 0;
        int string_size = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            string_size++;
            string_size_mem++;
            switch (line[i])
            {
            case '\\':
                string_size_mem++;
                break;
            case '"':
                string_size_mem++;
                break;
            
            default:
                break;
            }
        }
        mem_chars += string_size_mem + 2;
        total_chars += string_size;
        line = strtok_r(NULL, "\n", &save_ptr);
    }
    printf("%d\n", mem_chars - total_chars);
}

void run2015_08(char *input) {
    printf("Part 1: ");
    _2015_08_p1(input);
    printf("Part 2: ");
    _2015_08_p2(input);
}