#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int tableArraySize = 340;

typedef struct {
    char *key;
    union {
        char *op[3];
        int val;
    };
} DataItem;

DataItem *unprocessed;
DataItem *processed;

void initPbuffer() {
    unprocessed = calloc(tableArraySize, sizeof(DataItem));
    processed = calloc(tableArraySize, sizeof(DataItem));
}

static uint16_t search(DataItem *table, char *key) {
    for (size_t i = 0; i <= tableArraySize; i++) {
        if (table[i].key != NULL) {
            if (!strcmp(table[i].key, key))
                return i;
        }
    }
    printf("Table with key: %s not found\n", key);
    exit(1);
}

static int isInProcessed(DataItem *table, char *key) {
    for (size_t i = 0; i < tableArraySize; i++) {
        if (table[i].key != NULL) {
            if (!strcmp(table[i].key, key)) {
                return i;
            }
        }
    }
    return 0;
}

static void insert(DataItem *table, char *key, char *data[3], uint16_t counter) {
    table[counter].key = key;
    table[counter].op[0] = data[0];
    table[counter].op[1] = data[1];
    table[counter].op[2] = data[2];
}

char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}
static int walkThrough(DataItem *unprocessed, DataItem *processed, char *key) {
    // layer++;
    if (isdigit(*key)) {
        return atoi(key);
    }

    uint16_t index = search(unprocessed, key);
    // printf("l: %u, k: %s, op1: %s, op2: %s, op3: %s\n", layer, key, unprocessed[index].op[0],
    // unprocessed[index].op[1], unprocessed[index].op[2]);
    int result;
    if (!isInProcessed(processed, key)) {
        if ((unprocessed[index].op[1] == NULL) && (unprocessed[index].op[2] == NULL)) {
            result = walkThrough(unprocessed, processed, unprocessed[index].op[0]);
        } else if ((unprocessed[index].op[2] == NULL)) {
            if (!strcmp(unprocessed[index].op[0], "NOT"))
                result = ~(walkThrough(unprocessed, processed, unprocessed[index].op[1]));
        } else {
            if (!strcmp(unprocessed[index].op[1], "AND")) {
                result = walkThrough(unprocessed, processed, unprocessed[index].op[0]) &
                         walkThrough(unprocessed, processed, unprocessed[index].op[2]);
            } else if (!strcmp(unprocessed[index].op[1], "OR")) {
                result = walkThrough(unprocessed, processed, unprocessed[index].op[0]) |
                         walkThrough(unprocessed, processed, unprocessed[index].op[2]);
            } else if (!strcmp(unprocessed[index].op[1], "RSHIFT")) {
                result = walkThrough(unprocessed, processed, unprocessed[index].op[0]) >>
                         walkThrough(unprocessed, processed, unprocessed[index].op[2]);
            } else if (!strcmp(unprocessed[index].op[1], "LSHIFT")) {
                result = walkThrough(unprocessed, processed, unprocessed[index].op[0])
                         << walkThrough(unprocessed, processed, unprocessed[index].op[2]);
            }
        }
        processed[index].val = result;
        processed[index].key = unprocessed[index].key;
    }
    return processed[index].val;
}

void _2015_07_p1(char *input) {
    char *buffer = malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    char *line_save_ptr;
    char *lvl1_save_ptr;
    char *lvl2_save_ptr;
    char *line = strtok_r(buffer, "\n", &line_save_ptr);
    initPbuffer();
    uint16_t table_counter = 0;
    while (line) {
        char *lhs = strtok_r(line, "->", &lvl1_save_ptr);
        char *key = strtok_r(NULL, "->", &lvl1_save_ptr);
        char *data[3];
        data[0] = strtok_r(lhs, " ", &lvl2_save_ptr);
        data[1] = strtok_r(NULL, " ", &lvl2_save_ptr);
        if (data[1]) {
            data[2] = strtok_r(NULL, " ", &lvl2_save_ptr);
        } else {
            data[2] = NULL;
        }

        key = trimwhitespace(key);
        insert(unprocessed, key, data, table_counter);
        table_counter++;

        line = strtok_r(NULL, "\n", &line_save_ptr);
    }

    int result = walkThrough(unprocessed, processed, "a");
    printf("%d\n", result);

    free(buffer_adress);
    free(unprocessed);
    free(processed);
}

void _2015_07_p2(char *input) {
    char *buffer = malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    char *line_save_ptr;
    char *lvl1_save_ptr;
    char *lvl2_save_ptr;
    char *line = strtok_r(buffer, "\n", &line_save_ptr);
    initPbuffer();
    uint16_t table_counter = 0;
    while (line) {
        char *lhs = strtok_r(line, "->", &lvl1_save_ptr);
        char *key = strtok_r(NULL, "->", &lvl1_save_ptr);
        char *data[3];
        data[0] = strtok_r(lhs, " ", &lvl2_save_ptr);
        data[1] = strtok_r(NULL, " ", &lvl2_save_ptr);
        if (data[1]) {
            data[2] = strtok_r(NULL, " ", &lvl2_save_ptr);
        } else {
            data[2] = NULL;
        }

        key = trimwhitespace(key);
        insert(unprocessed, key, data, table_counter);
        table_counter++;

        line = strtok_r(NULL, "\n", &line_save_ptr);
    }

    uint16_t idx_b = search(unprocessed, "b");
    processed[idx_b].key = "b";
    processed[idx_b].val = 16076;
    int result = walkThrough(unprocessed, processed, "a");
    printf("%d\n", result);

    free(buffer_adress);
    free(unprocessed);
    free(processed);
}

void run2015_07(char *input) {
    printf("Part 1: ");
    _2015_07_p1(input);
    printf("Part 2: ");
    _2015_07_p2(input);
}