#ifndef HASHSET
#define HASHSET

// Defines the HashSet
typedef struct HashSet {
    // Contains an array of pointers to items.
    char **items;
    int size;
    int count;
} HashSet;

// create a hashset, returns a pointer to the set
HashSet *hashset_create(int size);
// free a hashset
void hashset_free(HashSet *set);
// insert key value pair into hashset
void hashset_insert(HashSet *set, char *key);
// search for index key in hashset, returns -1 if failed
int hashset_get_idx_if_in_set(HashSet *set, char *key);
// delete item from hashtable
void hashset_delete_item(HashSet *set, char *key);
// returns a pointer to every char*
char **hashset_return_as_array(HashSet *set);

#endif