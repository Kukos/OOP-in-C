#include <interface.h>
#include <stdlib.h>
#include <string.h>

void interface_object_init(Interface_object* iobject,
                           void* object,
                           interface_object_get_size_f get_size,
                           interface_object_get_object_f get_object,
                           interface_object_deinit_f deinit,
                           interface_object_destroy_f destroy)
{
    iobject->object = object;
    iobject->get_object = get_object;
    iobject->get_size = get_size;
    iobject->deinit = deinit;
    iobject->destroy = destroy;
}

Interface_object* interface_object_create(void* object,
                                          interface_object_get_size_f get_size,
                                          interface_object_get_object_f get_object,
                                          interface_object_deinit_f deinit,
                                          interface_object_destroy_f destroy)
{
    Interface_object* iobject = malloc(sizeof(*iobject));
    if (iobject == NULL)
        return NULL;

    interface_object_init(iobject, object, get_size, get_object, deinit, destroy);

    return iobject;
}

void interface_object_destroy(Interface_object* iobject)
{
    /* destroy only if callback has been passed, if not object is on stack */
    if (iobject->destroy != NULL)
        iobject->destroy(iobject->object);
    else
        iobject->deinit(iobject->object);

    free(iobject);
}

void interface_object_deinit(Interface_object* iobject)
{
    iobject->deinit(iobject->object);
    memset(iobject, 0, sizeof(*iobject));
}