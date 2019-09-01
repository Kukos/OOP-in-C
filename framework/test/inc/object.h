#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>

/* Forward declaration makes this object full private */
typedef struct Object_private Object_private;

Object_private* object_private_create(const void* object, size_t size);
void object_private_destroy(Object_private* objectp);
void object_private_init(Object_private* objectp, const void* object, size_t size);
void object_private_deinit(Object_private* objectp);

/* Object is private we can't implement getters as static inline */
size_t object_private_get_size(const Object_private* objectp);
void* object_private_get_object(const Object_private* objectp);

size_t object_private_sizeof(size_t object_size);

#endif