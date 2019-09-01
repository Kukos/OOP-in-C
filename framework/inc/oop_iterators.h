#ifndef OOP_ITERATORS_H
#define OOP_ITERATORS_H

/*
    Functions:
    Struct is name of your struct pass to macros as "PREFIX"
    1)
        Create iterator
        PARAMS
        @IN struct - pointer to struct
    	@IN mode - iterator init mode
        RETURN:
        %NULL iff failure
        %Pointer to new iterator iff success
        Struct* Struct_iterator_create(Struct* struct, oop_iterator_init_mode_t mode);
    2)
        Deallocate iterator memory
        PARAMS
        @iterator - pointer to iterator
        RETURN:
        This is void function
        void Struct_iterator_destroy(Struct_iterator* iterator);
    3)
        Go to the next value
        PARAMS
        @IN iterator - pointer iterator
        RETURN:
        %0 iff success
        %Non-zero value iff failure
        int Struct_iterator_next(Struct_iterator* iterator);
    4)
        Go to the prev value
        PARAMS
        @IN iterator - pointer iterator
        RETURN:
        %0 iff success
        %Non-zero value iff failure
        int Struct_iterator_prev(Struct_iterator* iterator);
    5)
        Check the end of iterator
        PARAMS
        @IN iterator - pointer to iterator
        RETURN:
        %FALSE iff not end
        %TRUE iff end
        bool Struct_iterator_end(Struct_iterator* iterator);
    6)
        Get data from iterator (Pass addr of data as val)
        PARAMS
        @IN - pointer iterator
        @OUT val - pointer to value ((void *)&struct)
        RETURN:
        %0 iff success
        %Non-zero value iff failure
        int Struct_iterator_get_data(Struct_iterator* iterator, void* val);
    7)
        Get node from iterator (Pass addr of node as node)
        PARAMS
        @IN - pointer iterator
        @OUT node - pointer to node ((void *)&struct)
        RETURN:
        %0 iff success
        %Non-zero value iff failure
        int Struct_iterator_get_node(Struct_iterator* iterator, void* node);
    Macros:
    @PARAMS
        ptr --> instance of your struct
        type   --> typeof(ptr)
        node   --> instance of your node
        data   --> instance of your data
    1)
        OOP_FOR_EACH(ptr, type, node, data)  ---> from BEGIN to END
    2)
        OOP_FOR_EACH_REVERSE(ptr, type, node, data) --> from END to BEGIN
    3)
        OOP_FOR_EACH_DATA(ptr, type, data) --> from BEGIN to END, return only data
    4)
        OOP_FOR_EACH_DATA_REVERSE(ptr, type, data) --> from END to BEGIN, return only data
    5)
        OOP_FOR_EACH_NODE(ptr, type, node) --> from BEGIN to END, return only node
    6)
        OOP_FOR_EACH_NODE_REVERSE(ptr, type, node) --> from END to BEGIN, return only node
*/

#include <stdbool.h>

#define _OOP_IT_CONCAT(x, y) x##y
#define OOP_IT_CONCAT(x, y) _OOP_IT_CONCAT(x, y)

#define OOP_IT_STRUCT_NAME(PREFIX) OOP_IT_CONCAT(PREFIX, _iterator)

typedef enum oop_iterator_init_mode
{
    OOP_ITERATOR_INIT_MODE_NORMAL,
    OOP_ITERATOR_INIT_MODE_REVERSE,
} oop_iterator_init_mode_t;

#define OOP_ITERATOR_HEADER(STRUCT, PREFIX) \
    OOP_IT_STRUCT_NAME(STRUCT)* OOP_IT_CONCAT(PREFIX, _iterator_create)(const STRUCT*, oop_iterator_init_mode_t); \
    void OOP_IT_CONCAT(PREFIX, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)*); \
    int OOP_IT_CONCAT(PREFIX, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)*); \
    int OOP_IT_CONCAT(PREFIX, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)*); \
    bool OOP_IT_CONCAT(PREFIX, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)*); \
    int OOP_IT_CONCAT(PREFIX, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict, void* restrict); \
    int OOP_IT_CONCAT(PREFIX, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict, void* restrict); \
    static inline OOP_IT_STRUCT_NAME(STRUCT) *OOP_IT_CONCAT(STRUCT, _iterator_create)(const STRUCT *s, oop_iterator_init_mode_t mode); \
    static inline void OOP_IT_CONCAT(STRUCT, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline bool OOP_IT_CONCAT(STRUCT, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict d); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict n); \
    \
    static inline OOP_IT_STRUCT_NAME(STRUCT)* OOP_IT_CONCAT(STRUCT, _iterator_create)(const STRUCT* s, oop_iterator_init_mode_t mode) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_create)(s, mode); \
    } \
    \
    static inline void OOP_IT_CONCAT(STRUCT, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        OOP_IT_CONCAT(PREFIX, _iterator_destroy)(s); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_next)(s); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_prev)(s); \
    } \
    \
    static inline bool OOP_IT_CONCAT(STRUCT, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_end)(s); \
    } \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict d) \
    { \
            return OOP_IT_CONCAT(PREFIX, _iterator_get_data)(s, d); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict n) \
    { \
            return OOP_IT_CONCAT(PREFIX, _iterator_get_node)(s, n); \
    }

#define OOP_FOR_EACH(iterator, ptr, type, node, data) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_NORMAL); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define OOP_FOR_EACH_REVERSE(iterator, ptr, type, node, data) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_REVERSE); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _prev)(iterator) \
            )

#define OOP_FOR_EACH_DATA(iterator, ptr, type, data) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_NORMAL); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define OOP_FOR_EACH_DATA_REVERSE(iterator, ptr, type, data) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_REVERSE); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_data)(iterator, (void *)&(data)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _prev)(iterator) \
            )

#define OOP_FOR_EACH_NODE(iterator, ptr, type, node) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_NORMAL); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _next)(iterator) \
            )

#define OOP_FOR_EACH_NODE_REVERSE(iterator, ptr, type, node) \
        for (   iterator = OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _create)(ptr, OOP_ITERATOR_INIT_MODE_REVERSE); \
                ( \
                    iterator != NULL && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _end)(iterator) && \
                    !OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _get_node)(iterator, (void *)&(node)) \
                ); \
                OOP_IT_CONCAT(OOP_IT_STRUCT_NAME(type), _prev)(iterator) \
            )


/* FOR INTERFACES (FULL ABSTRACT CLASSES) */
/* Like OOP_ITERATOR_HEADER but most functions are inline and containers framework friendly */
#define OOP_ITERATOR_HEADER_FOR_ABSTRACT_CLASS(STRUCT, PREFIX) \
    static inline void* OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(const OOP_IT_STRUCT_NAME(STRUCT)* it); \
    static inline void OOP_IT_CONCAT(PREFIX, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* it); \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* it); \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* it); \
    static inline bool OOP_IT_CONCAT(PREFIX, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* it); \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict it, void* restrict data); \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict it, void* restrict node); \
    static inline OOP_IT_STRUCT_NAME(STRUCT)* OOP_IT_CONCAT(STRUCT, _iterator_create)(const STRUCT* s, oop_iterator_init_mode_t mode); \
    static inline void OOP_IT_CONCAT(STRUCT, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline bool OOP_IT_CONCAT(STRUCT, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* s); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict d); \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict n); \
    \
    static inline void* OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(const OOP_IT_STRUCT_NAME(STRUCT)* it) \
    { \
        if (it == NULL) \
            return NULL; \
        \
        return it->____iterator; \
    } \
    \
    static inline void OOP_IT_CONCAT(PREFIX, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* it) \
    { \
        if (it == NULL) \
            return; \
        \
        it->____destroy(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it)); \
        FREE(it); \
    } \
    \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* it) \
    { \
        if (it == NULL) \
            return 1; \
        \
        return it->____next(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it)); \
    } \
    \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* it) \
    { \
        if (it == NULL) \
            return 1;\
        \
        return it->____prev(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it)); \
    } \
    \
    static inline bool OOP_IT_CONCAT(PREFIX, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* it) \
    { \
        if (it == NULL) \
            return true; \
        \
        return it->____end(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it)); \
    } \
    \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict it, void* restrict data) \
    { \
        if (it == NULL) \
            return 1; \
        \
        return it->____get_data(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it), data); \
    } \
    \
    static inline int OOP_IT_CONCAT(PREFIX, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict it, void* restrict node) \
    { \
        if (it == NULL) \
            return 1; \
        \
        return it->____get_node(OOP_IT_CONCAT(PREFIX, _iterator_get_iterator)(it), node); \
    } \
    \
    static inline OOP_IT_STRUCT_NAME(STRUCT)* OOP_IT_CONCAT(STRUCT, _iterator_create)(const STRUCT* s, oop_iterator_init_mode_t mode) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_create)(s, mode); \
    } \
    \
    static inline void OOP_IT_CONCAT(STRUCT, _iterator_destroy)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        OOP_IT_CONCAT(PREFIX, _iterator_destroy)(s); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_next)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_next)(s); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_prev)(OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_prev)(s); \
    } \
    \
    static inline bool OOP_IT_CONCAT(STRUCT, _iterator_end)(const OOP_IT_STRUCT_NAME(STRUCT)* s) \
    { \
        return OOP_IT_CONCAT(PREFIX, _iterator_end)(s); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_data)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict d) \
    { \
            return OOP_IT_CONCAT(PREFIX, _iterator_get_data)(s, d); \
    } \
    \
    static inline int OOP_IT_CONCAT(STRUCT, _iterator_get_node)(const OOP_IT_STRUCT_NAME(STRUCT)* restrict s, void* restrict n) \
    { \
            return OOP_IT_CONCAT(PREFIX, _iterator_get_node)(s, n); \
    }


#endif