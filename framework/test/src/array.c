#include <array.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

struct Array
{
    int* t;
    size_t len;
};

struct Array_iterator
{
    int        *array;          /* pointer to array */
    ssize_t     index;          /* index of array */
    size_t      array_length;   /* array length */
};

Array* array_create(size_t len)
{
    Array *a = malloc(sizeof(Array));
    if (a == NULL)
        return NULL;

    array_init(a, len);

    return a;
}

void array_init(Array* a, size_t len)
{
    a->t = malloc(len * sizeof(a->t[0]));
    a->len = len;
}

void array_deinit(Array *a)
{
    free(a->t);
    memset(a, 0, sizeof(*a));
}

void array_destroy(Array *a)
{
    free(a->t);
    free(a);
}

size_t array_sizeof(size_t len)
{
    return sizeof(Array) + len * sizeof(int);
}

void array_set(Array* a, size_t index, int value)
{
    if (index >= a->len)
        return;

    a->t[index] = value;
}

int array_get(const Array* a, size_t index)
{
    if (index >= a->len)
        return 0;

    return a->t[index];
}

/* Iterator framework */

Array_iterator *array_iterator_create(const Array *a, oop_iterator_init_mode_t mode)
{
    Array_iterator* it = malloc(sizeof(*it));
    if (it == NULL)
        return NULL;

    it->array = a->t;
    it->array_length = a->len;

    switch (mode)
    {
        case OOP_ITERATOR_INIT_MODE_NORMAL:
        {
            it->index = 0;
            break;
        }
        case OOP_ITERATOR_INIT_MODE_REVERSE:
        {
            it->index = (ssize_t)it->array_length - 1;
            break;
        }
        default:
        {
            break;
        }
    }

    return it;
}

void array_iterator_destroy(Array_iterator *iterator)
{
    free(iterator);
}

int array_iterator_next(Array_iterator *iterator)
{
    ++iterator->index;

    return 0;
}

int array_iterator_prev(Array_iterator *iterator)
{
    --iterator->index;

    return 0;
}

bool array_iterator_end(const Array_iterator *iterator)
{
    return (iterator->index < 0 || (size_t)iterator->index >= iterator->array_length);
}

int array_iterator_get_data(const Array_iterator* iterator, void *val)
{
    *(int *)val = iterator->array[iterator->index];

    return 0;
}

int array_iterator_get_node(const Array_iterator* iterator, void* node)
{
    *(void **)node = (void*)&iterator->array[iterator->index];

    return 0;
}