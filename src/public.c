#include <public.h>
#include <string.h>
#include <stdlib.h>

void object_public_init(Object_public* objectp, const void* object, size_t size)
{
    objectp->object = malloc(size);
    if (objectp->object == NULL)
    {
        objectp->size = 0;
        return;
    }
    memcpy(objectp->object, object, size);
    objectp->size = size;
}

void object_public_deinit(Object_public* objectp)
{
    free(objectp->object);
    memset(objectp, 0, sizeof(*objectp));
}

Object_public* object_public_create(const void* object, size_t size)
{
    Object_public* objectp = malloc(sizeof(*objectp));
    if (objectp == NULL)
        return NULL;

    object_public_init(objectp, object, size);
    return objectp;
}

void object_public_destroy(Object_public* objectp)
{
    free(objectp->object);
    free(objectp);
}