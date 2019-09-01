#ifndef PUBLIC_H
#define PUBLIC_H

#include <stddef.h>

typedef struct Object_public
{
    size_t size;
    void*  object; /* we want to alloc it on stack, so void* instead of placeholder */
} Object_public;

Object_public* object_public_create(const void* object, size_t size);
void object_public_destroy(Object_public* objectp);
void object_public_init(Object_public* objectp, const void* object, size_t size);
void object_public_deinit(Object_public* objectp);

/* Object is public, so header known fields. Implement getters in fast way */
static inline size_t object_public_get_size(const Object_public* objectp);
static inline void* object_public_get_object(const Object_public* objectp);

static inline size_t object_public_get_size(const Object_public* objectp)
{
    return objectp == NULL ? 0 : objectp->size;
}

static inline void* object_public_get_object(const Object_public* objectp)
{
    return objectp == NULL ? NULL : objectp->object;
}

#endif