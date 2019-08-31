#ifndef OBJECT_ALLOCA_H
#define OBJECT_ALLOCA_H

#include <string.h>

#define OBJECT_ALLOCA_CONCAT(x, y) _OBJECT_ALLOCA_CONCAT(x, y)
#define _OBJECT_ALLOCA_CONCAT(x, y) x##y

#define OBJECT_ALLOCA(ptr, bytes) \
    char OBJECT_ALLOCA_CONCAT(object_alloca_memory_, __LINE__)[bytes]; ptr = (void*)&OBJECT_ALLOCA_CONCAT(object_alloca_memory_, __LINE__)[0]; memset(ptr, 0, bytes)

#endif