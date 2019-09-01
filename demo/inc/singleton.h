#ifndef SINGLETON_H
#define SINGLETON_H

typedef enum singleton_operation_t
{
    SINGLETON_OPERATION_GET,
    SINGLETON_OPERATION_SET,
} singleton_operation_t;


#define SINGLETON_VAR_HEADER(type, name) \
    type name##_singleton(type var, singleton_operation_t op); \
    static inline type name##_get(void) \
    { \
        return name##_singleton((type){0}, SINGLETON_OPERATION_GET); \
    } \
    \
    static inline void name##_set(type var) \
    { \
        (void)name##_singleton(var, SINGLETON_OPERATION_SET); \
    }


#define SINGLETON_VAR_SOURCE(type, name) \
    type name##_singleton(type var, singleton_operation_t op) \
    { \
        static type name; \
        switch (op) \
        { \
            case SINGLETON_OPERATION_GET: \
            { \
                return name; \
            } \
            case SINGLETON_OPERATION_SET: \
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

SINGLETON_VAR_HEADER(int, class_int)
SINGLETON_VAR_HEADER(double, class_double)

#endif