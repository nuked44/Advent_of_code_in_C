#ifndef HASHTABLE
#define HASHTABLE

// Defines the HashTable item.
typedef struct Ht_item {
    char *key;
    char *value;
} Ht_item;

// Defines the HashTable.
typedef struct HashTable {
    // Contains an array of pointers to items.
    Ht_item **items;
    int size;
    int count;
} HashTable;

// create a hashtable, returns a pointer to the table
HashTable *hashtable_create(int size);
// free a hashtable
void hashtable_free(HashTable *table);
// insert key value pair into hashtable
void hashtable_insert(HashTable *table, char *key, char *value);
// search for key in hashtable, returns the value associated to key
char *hashtable_search(HashTable *table, char *key);
// delete item from hashtable
void hashtable_delete_item(HashTable *table, char *key);

#endif