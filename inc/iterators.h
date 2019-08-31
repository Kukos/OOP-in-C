#ifndef ITERATORS_H
#define ITERATORS_H

#include <stdbool.h>

#define ITERATORS_CONCAT(x, y) _ITERATORS_CONCAT(x, y)
#define _ITERATORS_CONCAT(x, y) x##y

#define IT_STRUCT_NAME(PREFIX) ITERATORS_CONCAT(PREFIX, _iterator)

typedef enum iterator_mode_t
{
    ITERATOR_MODE_BEGIN,
    ITERATOR_MODE_END,
} iterator_mode_t;

#define IT_FUNC(STRUCT, PREFIX) \
    IT_STRUCT_NAME(STRUCT) *ITERATORS_CONCAT(PREFIX, _iterator_create)(const STRUCT *, iterator_mode_t); \
    void ITERATORS_CONCAT(PREFIX, _iterator_destroy)(IT_STRUCT_NAME(STRUCT) *); \
    int ITERATORS_CONCAT(PREFIX, _iterator_next)(IT_STRUCT_NAME(STRUCT) *); \
    int ITERATORS_CONCAT(PREFIX, _iterator_prev)(IT_STRUCT_NAME(STRUCT) *); \
    bool ITERATORS_CONCAT(PREFIX, _iterator_end)(const IT_STRUCT_NAME(STRUCT) *); \
    int ITERATORS_CONCAT(PREFIX, _iterator_get_data)(const IT_STRUCT_NAME(STRUCT) *, void *); \
    int ITERATORS_CONCAT(PREFIX, _iterator_get_node)(const IT_STRUCT_NAME(STRUCT) *, void *); \
    static inline IT_STRUCT_NAME(STRUCT) *ITERATORS_CONCAT(STRUCT, _iterator_create)(const STRUCT *s, iterator_mode_t mode); \
    static inline void ITERATORS_CONCAT(STRUCT, _iterator_destroy)(IT_STRUCT_NAME(STRUCT) *s); \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_next)(IT_STRUCT_NAME(STRUCT) *s); \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_prev)(IT_STRUCT_NAME(STRUCT) *s); \
    static inline bool ITERATORS_CONCAT(STRUCT, _iterator_end)(const IT_STRUCT_NAME(STRUCT) *s); \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_get_data)(const IT_STRUCT_NAME(STRUCT) *s, void *d); \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_get_node)(const IT_STRUCT_NAME(STRUCT) *s, void *n); \
    \
    static inline IT_STRUCT_NAME(STRUCT) *ITERATORS_CONCAT(STRUCT, _iterator_create)(const STRUCT *s, iterator_mode_t mode) \
    { \
        return ITERATORS_CONCAT(PREFIX, _iterator_create)(s, mode); \
    } \
    \
    static inline void ITERATORS_CONCAT(STRUCT, _iterator_destroy)(IT_STRUCT_NAME(STRUCT) *s) \
    { \
        ITERATORS_CONCAT(PREFIX, _iterator_destroy)(s); \
    } \
    \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_next)(IT_STRUCT_NAME(STRUCT) *s) \
    { \
        return ITERATORS_CONCAT(PREFIX, _iterator_next)(s); \
    } \
    \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_prev)(IT_STRUCT_NAME(STRUCT) *s) \
    { \
        return ITERATORS_CONCAT(PREFIX, _iterator_prev)(s); \
    } \
    \
    static inline bool ITERATORS_CONCAT(STRUCT, _iterator_end)(const IT_STRUCT_NAME(STRUCT) *s) \
    { \
        return ITERATORS_CONCAT(PREFIX, _iterator_end)(s); \
    } \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_get_data)(const IT_STRUCT_NAME(STRUCT) *s, void *d) \
    { \
            return ITERATORS_CONCAT(PREFIX, _iterator_get_data)(s, d); \
    } \
    \
    static inline int ITERATORS_CONCAT(STRUCT, _iterator_get_node)(const IT_STRUCT_NAME(STRUCT) *s, void *n) \
    { \
            return ITERATORS_CONCAT(PREFIX, _iterator_get_node)(s, n); \
    }

#define FOR_EACH(iterator, struct, type, node, data) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_BEGIN); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define FOR_EACH_REV(iterator, struct, type, node, data) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_END); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _prev)(iterator) \
            )


#define FOR_EACH_DATA(iterator, struct, type, data) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_BEGIN); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define FOR_EACH_DATA_REV(iterator, struct, type, data) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_END); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _prev)(iterator) \
            )


#define FOR_EACH_NODE(iterator, struct, type, node) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_BEGIN); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define FOR_EACH_NODE_REV(iterator, struct, type, node) \
        for (iterator = ITERATORS_CONCAT(IT_STRUCT_NAME(type), _create)(struct, ITERATOR_MODE_END); \
                ( \
                    iterator != NULL && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _end)(iterator) && \
                    !ITERATORS_CONCAT(IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) \
                ); \
                ITERATORS_CONCAT(IT_STRUCT_NAME(type), _prev)(iterator) \
            )

#endif