#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _2015_05_p1(char *input) {
    unsigned niceStrings = 0;

    char *buffer = malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    char *save_ptr = NULL;
    char *line = strtok_r(buffer, "\n", &save_ptr);

    while (line) {
        char prev = '\0';
        int vovels = 0;
        bool twice = false;
        bool badString = false;
        for (int i = 0; line[i] != '\0'; i++) {
            char combo[3] = {'\0'};
            snprintf(combo, sizeof(combo), "%c%c", prev, line[i]);

            if (!strcmp(combo, "ab") || !strcmp(combo, "cd") ||
                !strcmp(combo, "pq") || !strcmp(combo, "xy")) {
                badString = true;
                break;
            }

            if (prev == line[i]) {
                twice = true;
            }

            switch (line[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vovels++;
                break;

            default:
                break;
            }

            prev = line[i];
        }
        if (twice && (vovels >= 3) && !badString) {
            niceStrings++;
        }
        line = strtok_r(NULL, "\n", &save_ptr);
    }
    free(buffer_adress);
    printf("%d\n", niceStrings);
}

void _2015_05_p2(char *input) {
    unsigned niceStrings = 0;

    char *save_ptr = NULL;
    char *line = strtok_r(input, "\n", &save_ptr);

    while (line) {
        char prev = '\0';
        char preprev = '\0';
        bool match = false;
        bool repeat = false;

        for (int i = 0; line[i] != '\0'; i++) {
            if (i >= 3) {
                for (int j = 0; j <= i - 3; j++) {
                    if ((line[j] == line[i - 1]) && (line[j + 1] == line[i])) {
                        match = true;
                        break;
                    }
                }
            }
            if (preprev == line[i]) {
                repeat = true;
            }
            preprev = prev;
            prev = line[i];
        }

        if (match && repeat) {
            niceStrings++;
        }

        line = strtok_r(NULL, "\n", &save_ptr);
    }

    printf("%d\n", niceStrings);
}

void run2015_05(char *input) {
    printf("Part 1: ");
    _2015_05_p1(input);
    printf("Part 2: ");
    _2015_05_p2(input);
}