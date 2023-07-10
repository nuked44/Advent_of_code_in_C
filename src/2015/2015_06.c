#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _2015_06_p1(char *input) {
    unsigned num_of_lights = 0;
    bool lights[1000][1000] = {false};

    char *buffer = malloc((strlen(input) + 1) * sizeof(char));
    char *buffer_adress = buffer;
    strcpy(buffer, input);
    char *save_ptr = NULL;
    char *line = strtok_r(buffer, "\n", &save_ptr);

    while (line) {
        char action[4] = {0};
        int x1, y1, x2, y2 = 0;

        if (line[1] == 'u') { // tUrn %s(action)->(on|off)
            sscanf(line, "%*s %s %d,%d through %d,%d", action, &x1, &y1, &x2, &y2);

            if (!strcmp(action, "on")) {
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        lights[i][j] = true;
                    }
                }
            }
            if (!strcmp(action, "off")) {
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        lights[i][j] = false;
                    }
                }
            }

        } else if (line[1] == 'o') { // tOggle
            sscanf(line, "%*s %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    lights[i][j] = !lights[i][j];
                }
            }
        }

        line = strtok_r(NULL, "\n", &save_ptr);
    }

    for (size_t i = 0; i <= 999; i++) {
        for (size_t j = 0; j <= 999; j++) {
            if (lights[i][j]) {
                num_of_lights++;
            }
        }
    }

    printf("%d\n", num_of_lights);
    free(buffer_adress);
}

void _2015_06_p2(char *input) {
    unsigned brightness = 0;
    unsigned lights[1000][1000] = {0};

    char *save_ptr = NULL;
    char *line = strtok_r(input, "\n", &save_ptr);

    while (line) {
        char action[4] = {0};
        int x1, y1, x2, y2 = 0;

        if (line[1] == 'u') { // tUrn %s(action)->(on|off)
            sscanf(line, "%*s %s %d,%d through %d,%d", action, &x1, &y1, &x2, &y2);

            if (!strcmp(action, "on")) {
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        lights[i][j]++;
                    }
                }
            }
            if (!strcmp(action, "off")) {
                for (int i = x1; i <= x2; i++) {
                    for (int j = y1; j <= y2; j++) {
                        if (lights[i][j] > 0) {
                            lights[i][j]--;
                        }
                    }
                }
            }

        } else if (line[1] == 'o') { // tOggle
            sscanf(line, "%*s %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    lights[i][j] += 2;
                }
            }
        }

        line = strtok_r(NULL, "\n", &save_ptr);
    }

    for (size_t i = 0; i <= 999; i++) {
        for (size_t j = 0; j <= 999; j++) {
            brightness += lights[i][j];
        }
    }

    printf("%d\n", brightness);
}

void run2015_06(char *input) {
    printf("Part 1: ");
    _2015_06_p1(input);
    printf("Part 2: ");
    _2015_06_p2(input);
}