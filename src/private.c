#include <private.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* struct was typedef in header */
struct Object_private
{
    size_t size;
    uint8_t object[]; /* we can't alloc object on stack, so use fast placeholder */
};

void object_private_init(Object_private* objectp, const void* object, size_t size)
{
    if (objectp->size < size)
        return;

    memcpy(objectp->object, object, size);
    objectp->size = size;
}

void object_private_deinit(Object_private* objectp)
{
    memset(objectp, 0, sizeof(*objectp) + objectp->size);
}

Object_private* object_private_create(const void* object, size_t size)
{
    Object_private* objectp = malloc(sizeof(*objectp) + size);
    if (objectp == NULL)
        return NULL;

    objectp->size = size;
    object_private_init(objectp, object, size);
    return objectp;
}

void object_private_destroy(Object_private* objectp)
{
    free(objectp);
}

size_t object_private_get_size(const Object_private* objectp)
{
    return objectp == NULL ? 0 : objectp->size;
}

void* object_private_get_object(const Object_private* objectp)
{
    Object_private* ptr = (Object_private *)(uintptr_t)objectp; /* to remove const */
    return objectp == NULL ? NULL : &ptr->object[0];
}
