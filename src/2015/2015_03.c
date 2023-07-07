#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} position;

bool is_uniqe(position *uniqe, position pos, size_t uniqe_added) {
    for (size_t i = 0; i < uniqe_added + 1; i++) {
        if ((uniqe[i].x == pos.x) && (uniqe[i].y == pos.y))
            return false;
    }
    return true;
}

void _2015_03_p1(char *input) {
    position pos = {.x = 0, .y = 0};
    position *uniqe =
        calloc((strlen(input) + 1), sizeof(position));
    size_t uniqe_added = 0;
    for (size_t i = 0; input[i] != 0; i++) {
        switch (input[i]) {
        case '>':
            pos.x++;
            break;
        case '<':
            pos.x--;
            break;
        case '^':
            pos.y++;
            break;
        case 'v':
            pos.y--;
            break;
        }
        if (is_uniqe(uniqe, pos, uniqe_added)) {
            uniqe[uniqe_added] = pos;
            uniqe_added++;
        }
    }
    printf("%zu\n", uniqe_added + 1);
    free(uniqe);
}

void _2015_03_p2(char *input) {
    position santa_pos = {.x = 0, .y = 0};
    position robo_santa_pos = {.x = 0, .y = 0};
    position *uniqe =
        calloc((strlen(input) + 1), sizeof(position));
    size_t uniqe_added = 0;
    for (size_t i = 0; input[i] != 0; i++) {
        switch (input[i]) {
        case '>':
            if (i % 2) {
                robo_santa_pos.x++;
                break;
            } else {
                santa_pos.x++;
                break;
            }
        case '<':
            if (i % 2) {
                robo_santa_pos.x--;
                break;
            } else {
                santa_pos.x--;
                break;
            }
        case '^':
            if (i % 2) {
                robo_santa_pos.y++;
                break;
            } else {
                santa_pos.y++;
                break;
            }
        case 'v':
            if (i % 2) {
                robo_santa_pos.y--;
                break;
            } else {
                santa_pos.y--;
                break;
            }
        }
        if (is_uniqe(uniqe, santa_pos, uniqe_added)) {
            uniqe[uniqe_added] = santa_pos;
            uniqe_added++;
        }
        if (is_uniqe(uniqe, robo_santa_pos, uniqe_added)) {
            uniqe[uniqe_added] = robo_santa_pos;
            uniqe_added++;
        }
    }
    printf("%zu\n", uniqe_added + 1);
    free(uniqe);
}

void run2015_03(char *input) {
    printf("Part 1: ");
    _2015_03_p1(input);
    printf("Part 2: ");
    _2015_03_p2(input);
}