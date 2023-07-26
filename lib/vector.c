#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

vector *vector_new() {
    vector *vec = malloc(sizeof(vector));
    vec->content = NULL;
    vec->capacity = 1;
    vec->size = 0;
    return vec;
}

void vector_free(vector *vec) {
    for (size_t i = 0; i < vec->capacity; i++) {
        free(vec->content[i]);
    }
    free(vec->content);
    free(vec);
}

static void vector_resize(vector *vec, size_t newCapacity) {
    void **newContent = realloc(vec->content, newCapacity * sizeof(void *));
    if (newContent) {
        vec->content = newContent;
        vec->capacity = newCapacity;
    } else {
        fprintf(stderr, "realloc in vector_add failed");
    }
}

void vector_add(vector *vec, void *item) {
    if (vec->size >= vec->capacity) {
        vector_resize(vec, vec->capacity * 2);
    }

    vec->content[vec->size] = item;
    vec->size++;
}

void *vector_pop(vector *vec) {
    void *item = vec->content[vec->size];
    vec->size--;
    return item;
}

// Set vec[idx] to item
// void vector_set(vector *vec, void *item, size_t idx);

void *vector_get(vector *vec, size_t idx) {
    if (idx <= vec->size) {
        return vec->content[idx];
    }
    fprintf(stderr, "idx in vector_get to high");
    return NULL;
}

void vector_shrink(vector *vec) { vector_resize(vec, vec->size); }
