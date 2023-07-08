#define NEWEST_YEAR_SUPPORTED 2023

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "common.h"
#include "days.h"

typedef void (*FunctionPtr)(char *);

int main(int argc, char *argv[]) {
    if (argc == 3) {
        // argv[1] ^= year, argv[2] ^= day
        int year = atoi(argv[1]);
        int day = atoi(argv[2]);

        int year_idx = year - 2015; // current year minus first year(2015)
        int day_idx = day - 1;

        FunctionPtr fun[8][25] = {ADDED_FUNCTIONS};

        if (year_idx <= NEWEST_YEAR_SUPPORTED && day_idx <= 31) {
            if (fun[year_idx][day_idx]) {
                char file_name[26];

                snprintf(file_name, sizeof file_name,
                         "inputs/input_%d_%02d.txt", year, day);

                char *file = load_file(file_name);

                struct timeval t1, t2;
                double elapsedTime;

                printf("\n--- %d -- %02d ---\n\n", year, day);

                gettimeofday(&t1, NULL);
                fun[year_idx][day_idx](file);
                gettimeofday(&t2, NULL);
                free(file);

                elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;    // sec to ms
                elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
                printf("\n------------------\n");
                printf("Time used: %f ms.\n", elapsedTime);
                printf("------------------\n\n");
            } else {
                printf("Function not provided\n");
            }
        } else {
            printf("Function out of bounds\n");
        }

    } else {
        printf("Use case: %s <year(2015-%d)> <day(1-25)>\n", argv[0],
               NEWEST_YEAR_SUPPORTED);
    }
    return 0;
}
