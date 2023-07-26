#ifndef VECTOR
#define VECTOR

#include <stdlib.h>

typedef struct vector {
    void **content;
    unsigned capacity;
    unsigned size;
} vector;

// Make new vector
vector *vector_new();
// Free vector vec
void vector_free(vector *vec);

// Push element at end of vector
void vector_add(vector *vec, void *item);
// Pop element at end of vector, size--
void *vector_pop(vector *vec);

// Set vec[idx] to item
// void vector_set(vector vec, void *item, size_t idx);

// Get vec[idx]
void *vector_get(vector *vec, size_t idx);

// Shrink the vector to size
void vector_shrink(vector *vec);

#endif