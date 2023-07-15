#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

static unsigned long hash_function(char *str, int size) {
    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
        i += str[j];

    return i % size;
}

// Creates a new HashTable item, returns pointer to it
static Ht_item *create_item(char *key, char *value) {
    Ht_item *item = malloc(sizeof(Ht_item));
    if (item == NULL) {
        // Handle allocation error
        return NULL;
    }
    item->key = malloc((strlen(key) + 1) * sizeof(char));
    if (item->key == NULL) {
        // Handle allocation error
        free(item);
        return NULL;
    }
    item->value = malloc((strlen(value) + 1) * sizeof(char));
    if (item->value == NULL) {
        // Handle allocation error
        free(item->key);
        free(item);
        return NULL;
    }
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
}

// Creates a new HashTable, returns a pointer to it
HashTable *hashtable_create(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        // Handle allocation error
        return NULL;
    }
    table->size = size;
    table->count = 0;
    table->items = calloc(table->size, sizeof(Ht_item *));
    if (table->items == NULL) {
        // Handle allocation error
        free(table);
        return NULL;
    }
    return table;
}

// Frees an item.
static void free_hashtable_item(Ht_item **items, int index) {
    if (items[index] != NULL) {
        free(items[index]->key);
        free(items[index]->value);
        free(items[index]);
    }
}

// Frees the table.
void hashtable_free(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
            free_hashtable_item(table->items, i);
    }
    free(table->items);
    free(table);
}

void hashtable_insert(HashTable *table, char *key, char *value) {

    if (table->count == table->size) {
        // HashTable is full.
        printf("Insert Error: Hash Table is full\n");
        return;
    }

    // Creates the item.
    Ht_item *item = create_item(key, value);

    // Computes the index.
    int index = hash_function(key, table->size);

    if (table->items[index] == NULL) {
        // Key does not exist.

        // Insert directly.
        table->items[index] = item;
        table->count++;
    } else {
        // Scenario 1: Update the value.
        if (!strcmp(table->items[index]->key, key)) {
            strcpy(table->items[index]->value, value);
            return;
        } else {
            // Scenario 2: Handle the collision.
            while (table->items[index] != NULL) {
                index++; 
                index %= table->size;
            }
            table->items[index] = item;
            table->count++;

            return;
        }
    }
}

char *hashtable_search(HashTable *table, char *key) {
    // Searches for the key in the HashTable.
    // Returns NULL if it doesn't exist.
    int index = hash_function(key, table->size);
    Ht_item *item = table->items[index];

    // Provide only non-NULL values.
    if (item != NULL) {
        if (!strcmp(item->key, key)) {
            return item->value;
        } else {
            for (size_t i = 0; i < table->size; i++) {
                if (!strcmp(table->items[index]->key, key)) {
                    return table->items[index]->value;
                } else {
                    index++;
                    index %= table->size;
                }
            }
        }
    }
    return NULL;
}

// delete item from hashtable
void hashtable_delete_item(HashTable *table, char *key) {
    int index = hash_function(key, table->size);

    if (!table->items[index]) {
        // Does not exist.
        return;
    } else {
        if (!strcmp(table->items[index]->key, key)) {
            // Remove the item.
            // Set table index to NULL.
            table->items[index] = NULL;
            free_hashtable_item(table->items, index);
            table->count--;
        } else {
            for (size_t i = 0; i < table->size; i++) {
                if (!strcmp(table->items[index]->key, key)) {
                    free_hashtable_item(table->items, index);
                    table->count--;
                } else {
                    index += (index + 1) % table->size;
                }
            }
        }
    }
}
