#ifndef OOP_SINGLETON_H
#define OOP_SINGLETON_H

typedef enum oop_singleton_operation_t
{
    OOP_SINGLETON_OPERATION_GET,
    OOP_SINGLETON_OPERATION_SET,
} oop_singleton_operation_t;


#define OOP_SINGLETON_VAR_HEADER(type, name) \
    type name##_singleton(type var, oop_singleton_operation_t op); \
    static inline type name##_get(void) \
    { \
        return name##_singleton((type){0}, OOP_SINGLETON_OPERATION_GET); \
    } \
    \
    static inline void name##_set(type var) \
    { \
        (void)name##_singleton(var, OOP_SINGLETON_OPERATION_SET); \
    }


#define OOP_SINGLETON_VAR_SOURCE(type, name) \
    type name##_singleton(type var, oop_singleton_operation_t op) \
    { \
        static type name; \
        switch (op) \
        { \
            case OOP_SINGLETON_OPERATION_GET: \
            { \
                return name; \
            } \
            case OOP_SINGLETON_OPERATION_SET: \
            { \
                name = var; \
                return (type){0}; \
            } \
            default: \
            { \
                return (type){0}; \
            } \
        } \
    }

#endif