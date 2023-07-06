#include <stdio.h>
#include <stdlib.h>

void _2015_01_p1(char *input) {
    int floor = 0;
    for (int i = 0; input[i] != 0; i++) {
        switch (input[i])
        {
        case '(':
            floor++;
            break;

        case ')':
            floor--;
            break;
        
        default:
            break;
        }
    }
    printf("%d\n", floor);
}

void _2015_01_p2(char *input) {
    int floor = 0;
    for (int i = 0; input[i] != 0; i++) {
        switch (input[i])
        {
        case '(':
            floor++;
            break;

        case ')':
            floor--;
            break;
        
        default:
            break;
        }
        if (floor == -1)
        {
            printf("%d\n", i + 1);
            return;
        }
    }
}

void run2015_01(char *input) {
    printf("Part 1: ");
    _2015_01_p1(input);
    printf("Part 2: ");
    _2015_01_p2(input);
}