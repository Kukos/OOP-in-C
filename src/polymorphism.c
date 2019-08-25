#include <polymorphism.h>

Interface_object* interface_object_create_object_public(void *object, size_t size)
{
    Object_public* objectp = object_public_create(object, size);
    return interface_object_create(objectp,
                                   object_public_get_size_interface_wrapper,
                                   object_public_get_object_interface_wrapper,
                                   object_public_deinit_interface_warpper,
                                   object_public_destroy_interface_wrapper);
}

Interface_object* interface_object_create_object_private(void *object, size_t size)
{
    Object_private* objectp = object_private_create(object, size);
    return interface_object_create(objectp,
                                   object_private_get_size_interface_wrapper,
                                   object_private_get_object_interface_wrapper,
                                   object_private_deinit_interface_warpper,
                                   object_private_destroy_interface_wrapper);
}