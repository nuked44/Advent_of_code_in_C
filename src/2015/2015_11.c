#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maps 1-26 to a-z
static const char itoc(int i) {
    if (i < 1 || i > 26) {
        return '\0';
    }
    return (char)(i + 96);
}

// maps a-z to 1-26
static const int ctoi(char i) {
    if (i < 'a' || i > 'z') {
        return 0;
    }
    return (int)i - 96;
}

char *make_next_pwd(char *input) {
    const int size_of_pwd = strlen(input);
    int *pwd = malloc(size_of_pwd * sizeof(int));
    char *respwd = malloc(size_of_pwd + 1);

    bool three_straight = false;
    bool bad_letter = false;
    int pair = 0;
    int pair_letter = 0;

    for (size_t i = 0; i < size_of_pwd; i++) {
        pwd[i] = ctoi(input[i]);
    }

    while (true) {
        three_straight = false;
        bad_letter = false;
        pair = 0;
        pair_letter = 0;

        pwd[size_of_pwd - 1] += 1;
        for (size_t i = size_of_pwd - 1; i > 0; i--) {
            if (pwd[i] > 26) {
                pwd[i] %= 26;
                pwd[i - 1] += 1;
            }
        }

        for (size_t i = 0; i < size_of_pwd; i++) {
            if (i < size_of_pwd - 2) {
                if ((pwd[i] == pwd[i + 1] - 1) && (pwd[i + 1] == pwd[i + 2] - 1)) {
                    three_straight = true;
                }
            }
            if ((pwd[i] == ctoi('i')) || (pwd[i] == ctoi('o')) || (pwd[i] == ctoi('l'))) {
                bad_letter = true;
                break;
            }
            if (i < size_of_pwd - 1) {
                if ((pwd[i] == pwd[i + 1]) && pwd[i] != pair_letter) {
                    pair += 1;
                    pair_letter = pwd[i];
                }
            }
        }
        bool finished = true;
        for (size_t i = 0; i < size_of_pwd; i++) {
            if (pwd[i] != 26) {
                finished = false;
                break;
            }
        }
        if (finished || (three_straight && !bad_letter && (pair >= 2))) {
            break;
        }
    }

    for (size_t i = 0; i < size_of_pwd; i++) {
        respwd[i] = itoc(pwd[i]);
    }
    respwd[8] = '\0';
    free(pwd);
    return respwd;
}

char *_2015_11_p1(char *input) {
    char *respwd = make_next_pwd(input);

    printf("%s\n", respwd);
    return respwd;
}

void _2015_11_p2(char *input) {
    char *respwd = make_next_pwd(input);

    printf("%s\n", respwd);
    free(respwd);
}

void run2015_11(char *input) {
    printf("Part 1: ");
    char *out = _2015_11_p1(input);
    printf("Part 2: ");
    _2015_11_p2(out);
    free(out);
}