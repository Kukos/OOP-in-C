#ifndef OOP_OBJECT_ALLOCA_H
#define OOP_OBJECT_ALLOCA_H

#include <string.h>

#define _OOP_OBJECT_ALLOCA_CONCAT(x, y) x##y
#define OOP_OBJECT_ALLOCA_CONCAT(x, y) _OOP_OBJECT_ALLOCA_CONCAT(x, y)

#define OOP_OBJECT_ALLOCA(ptr, bytes) \
    char OOP_OBJECT_ALLOCA_CONCAT(object_alloca_memory_, __LINE__)[bytes]; ptr = (void*)&OOP_OBJECT_ALLOCA_CONCAT(object_alloca_memory_, __LINE__)[0]; (void)memset(ptr, 0, (size_t)bytes)

#endif