#ifndef GARRAY_H
#define GARRAY_H

#include <stddef.h>

typedef void (*garray_deinit_f)(void* a);
typedef void (*garray_destroy_f)(void* a);
typedef size_t (*garray_sizeof_f)(size_t len);
typedef void (*garray_set_f)(void*a, size_t index, int value);
typedef int (*garray_get_f)(const void* a, size_t index);

typedef struct GArray
{
    void* array;

    garray_destroy_f destroy;
    garray_deinit_f deinit;
    garray_sizeof_f size_of;
    garray_set_f set;
    garray_get_f get;

} GArray;

#endif