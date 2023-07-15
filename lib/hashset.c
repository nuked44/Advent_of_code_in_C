#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashset.h"

static unsigned long hash_function(char *str, int size) {
    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
        i += str[j];

    return i % size;
}

// Creates a new HashTable item, returns pointer to it
static char *create_item(char *key) {
    char *item = malloc(strlen(key) + 1);
    if (item == NULL) {
        // Handle allocation error
        return NULL;
    }

    strcpy(item, key);
    return item;
}

// Creates a new HashSet, returns a pointer to it
HashSet *hashset_create(int size) {
    HashSet *set = calloc(1, sizeof(HashSet));
    if (set == NULL) {
        // Handle allocation error
        return NULL;
    }
    set->size = size;
    set->count = 0;
    set->items = calloc(set->size, sizeof(char *));
    if (set->items == NULL) {
        // Handle allocation error
        free(set);
        return NULL;
    }
    return set;
}

// Frees an item.
static void free_hashset_item(char **items, int index) {
    free(items[index]);
}

// Frees the set.
void hashset_free(HashSet *set) {
    for (int i = 0; i < set->size; i++) {
        free_hashset_item(set->items, i);
    }
    free(set->items);
    free(set);
}

int hashset_get_idx_if_in_set(HashSet *set, char *key) {
    // Searches for the key in the HashTable.
    // Returns NULL if it doesn't exist.
    int index = hash_function(key, set->size);
    char *item = set->items[index];

    // Provide only non-NULL values.
    if (item != NULL) {
        if (!strcmp(item, key)) {
            return index;
        } else {
            for (size_t i = 0; i < set->size; i++) {
                if (!strcmp(set->items[index], key)) {
                    return index;
                } else {
                    index += (index + 1) % set->size;
                }
            }
        }
    }
    return -1;
}

void hashset_insert(HashSet *set, char *key) {

    if (set->count == set->size) {
        // HashTable is full.
        printf("Insert Error: Hashset is full\n");
        return;
    }

    // Creates the item.
    char *item = create_item(key);

    // Computes the index.
    int index = hash_function(key, set->size);

    if (set->items[index] == NULL) {
        // Key does not exist.

        // Insert directly.
        set->items[index] = item;
        set->count++;
    } else {
        if (hashset_get_idx_if_in_set(set, key) == -1) {
            while (set->items[index] != NULL) {
                index++;
                index %= set->size;
            }
            set->items[index] = item;
            set->count++;

            return;
        } else {
            free(item);
        }
    }
}

// delete item from hashset
void hashset_delete_item(HashSet *set, char *key) {
    int index = hash_function(key, set->size);

    if (!set->items[index]) {
        // Does not exist.
        return;
    } else {
        if (!strcmp(set->items[index], key)) {
            // Remove the item.
            // Set hashset index to NULL.
            set->items[index] = NULL;
            free_hashset_item(set->items, index);
            set->count--;
        } else {
            for (size_t i = 0; i < set->size; i++) {
                if (!strcmp(set->items[index], key)) {
                    free_hashset_item(set->items, index);
                    set->count--;
                } else {
                    index += (index + 1) % set->size;
                }
            }
        }
    }
}

char **hashset_return_as_array(HashSet *set) {

    char **array = calloc(set->size, sizeof(char *));
    int index = 0;
    for (size_t i = 0; i < set->size; i++) {
        if (set->items[i] != NULL) {
            char *array_item = malloc(strlen(set->items[i]) + 1);
            strcpy(array_item, set->items[i]);
            array[index] = array_item;
            index++;
        }
    }
    return array;
}