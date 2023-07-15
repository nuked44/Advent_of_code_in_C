#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/common.h"
#include "../../lib/hashset.h"
#include "../../lib/hashtable.h"

void run2015_09(char *input) {
    HashTable *hashtable = hashtable_create(56);
    HashSet *hashset = hashset_create(56);

    char *buffer = malloc((strlen(input) + 1) * sizeof(char *));
    char *buffer_adress = buffer;
    strcpy(buffer, input);

    char *line_save_ptr = NULL;
    char *line = strtok_r(buffer, "\n", &line_save_ptr);

    while (line) {
        char *loc1 = calloc(sizeof(char *), strlen(line) + 1);
        char *loc2 = calloc(sizeof(char *), strlen(line) + 1);
        char *distance = calloc(sizeof(char *), strlen(line) + 1);
        sscanf(line, "%s to %s = %s", loc1, loc2, distance);
        char *atob = calloc(sizeof(char *), strlen(line) + 1);
        strcat(atob, loc1);
        strcat(atob, loc2);
        hashtable_insert(hashtable, atob, distance);
        char *btoa = calloc(sizeof(char *), strlen(line) + 1);
        strcat(btoa, loc2);
        strcat(btoa, loc1);
        hashtable_insert(hashtable, btoa, distance);

        hashset_insert(hashset, loc1);
        hashset_insert(hashset, loc2);

        free(loc1);
        free(loc2);
        free(distance);
        free(atob);
        free(btoa);
        line = strtok_r(NULL, "\n", &line_save_ptr);
    }

    char **array = hashset_return_as_array(hashset);
    unsigned char_ammount_in_hashset = 0;
    for (size_t i = 0; i < hashset->count; i++) {
        char_ammount_in_hashset += (strlen(array[i]) + 1);
    }
    long ammount_of_permutations = factorial(hashset->count);
    char ***permutations = calloc(ammount_of_permutations, char_ammount_in_hashset);
    heap_permutations(array, hashset->count, hashset->count, permutations);
    int min_travel = __INT_MAX__;
    int max_travel = 0;
    for (int permutation = 0; permutation < factorial(hashset->count); permutation++) {
        int travel_step = 0;
        int location_dist = __INT_MAX__;
        // -1 because count starts at 1, -1 because idx +1 is used
        for (int str_in_permutation = 0; str_in_permutation <= hashset->count - 2; str_in_permutation++) {
            int str_size_of_location = strlen(permutations[permutation][str_in_permutation]) +
                                       strlen(permutations[permutation][str_in_permutation + 1]) + 1;
            char *location = calloc(1, str_size_of_location);
            strcpy(location, permutations[permutation][str_in_permutation]);
            strcat(location, permutations[permutation][str_in_permutation + 1]);
            location_dist = atoi(hashtable_search(hashtable, location));

            travel_step += location_dist;
            free(location);
        }
        min_travel = min(min_travel, travel_step);
        max_travel = max(max_travel, travel_step);
    }
    for (size_t i = 0; i < hashset->size; i++) {
        free(array[i]);
    }
    free(array);

    for (size_t i = 0; i < ammount_of_permutations; i++) {
        for (size_t j = 0; j < hashset->count; j++) {
            free(permutations[i][j]);
        }
        free(permutations[i]);
    }
    free(permutations);

    hashtable_free(hashtable);
    hashset_free(hashset);
    free(buffer_adress);
    printf("Part 1: %d\n", min_travel);
    printf("Part 2: %d\n", max_travel);
}