#ifndef OOP_CHECKER_H
#define OOP_CHECKER_H

#define OOP_CHECK_FUNC_NAME_CONVENTION(class_name) \
    static inline void oop_##class_name##_func_name_checker(void) \
    { \
        typedef void (*oop_func_checker)(void); \
        oop_func_checker ptr = (oop_func_checker)class_name##_init; \
        ptr = (oop_func_checker)class_name##_deinit; \
        ptr = (oop_func_checker)class_name##_create; \
        ptr = (oop_func_checker)class_name##_destroy; \
        ptr = (oop_func_checker)class_name##_sizeof; \
        \
        (void)ptr; \
    }

#define OOP_CHECK_FUNC_ITERATOR(class_name) \
    static inline void oop_##class_name##_func_iterator_checker(void) \
    { \
        typedef void (*oop_func_checker)(void); \
        oop_func_checker ptr = (oop_func_checker)class_name##_iterator_create; \
        ptr = (oop_func_checker)class_name##_iterator_destroy; \
        ptr = (oop_func_checker)class_name##_iterator_next; \
        ptr = (oop_func_checker)class_name##_iterator_prev; \
        ptr = (oop_func_checker)class_name##_iterator_end; \
        ptr = (oop_func_checker)class_name##_iterator_get_data; \
        ptr = (oop_func_checker)class_name##_iterator_get_node; \
        \
        (void)ptr; \
    } \

#endif