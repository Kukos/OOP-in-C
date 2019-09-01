#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <oop_iterators.h>

typedef struct Array Array;
typedef struct Array_iterator Array_iterator;

Array* array_create(size_t len);
void array_init(Array* a, size_t len);
void array_deinit(Array* a);
void array_destroy(Array* a);
size_t array_sizeof(size_t len);
void array_set(Array* a, size_t index, int value);
int array_get(const Array* a, size_t index);

OOP_ITERATOR_HEADER(Array, array)

#endif