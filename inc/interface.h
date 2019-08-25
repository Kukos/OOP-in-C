#ifndef INTERFACE_H
#define INTERFACE_H

#include <public.h>
#include <private.h>

/* callbacks for interface */
typedef size_t (*interface_object_get_size_f)(const void* objectp);
typedef void* (*interface_object_get_object_f)(const void* objectp);
typedef void (*interface_object_destroy_f)(void* objectp);
typedef void (*interface_object_deinit_f)(void *objectp);

/* Interface need pointer to true object and callbacks like pure abstract class
   Object which was use to create interface should not be used directly, only via this interface
*/
typedef struct Interface_object
{
    void* object;

    interface_object_get_size_f  get_size;
    interface_object_get_object_f get_object;
    interface_object_destroy_f destroy; /* this is only needed for interface destroy */
    interface_object_deinit_f deinit; /* this is only needed for interface deinit and destroy */

} Interface_object;

/* Those functions are the same like alwyas: <class>_create ... */
Interface_object* interface_object_create(void* object,
                                          interface_object_get_size_f get_size,
                                          interface_object_get_object_f get_object,
                                          interface_object_deinit_f deinit,
                                          interface_object_destroy_f destroy);

void interface_object_destroy(Interface_object* iobject);

void interface_object_init(Interface_object* iobject,
                           void* object,
                           interface_object_get_size_f get_size,
                           interface_object_get_object_f get_object,
                           interface_object_deinit_f deinit,
                           interface_object_destroy_f destroy);

void interface_object_deinit(Interface_object* iobject);

/* Those are wrappers to call functions from true object */
static inline size_t interface_object_get_size(Interface_object* iobject);
static inline void* interface_object_get_object(Interface_object* iobject);

static inline size_t interface_object_get_size(Interface_object* iobject)
{
    return iobject == NULL ? 0 : iobject->get_size(iobject->object);
}

static inline void* interface_object_get_object(Interface_object* iobject)
{
    return iobject == NULL ? NULL : iobject->get_object(iobject->object);
}

/*  Object has functions like size_t object_public_get_size(const Object_Public* objectp)
    We have size_t f(const void*)

    That's why we need a wrappers
*/

#define INTERFACE_OBJECT_WRAPPERS_CREATE(type, class_name) \
    static inline size_t class_name##_get_size_interface_wrapper(const void* object); \
    static inline void* class_name##_get_object_interface_wrapper(const void* object); \
    static inline void class_name##_deinit_interface_warpper(void* object); \
    static inline void class_name##_destroy_interface_wrapper(void* object); \
    \
    static inline size_t class_name##_get_size_interface_wrapper(const void* object) \
    { \
        return class_name##_get_size((const type *)object); \
    } \
    \
    static inline void* class_name##_get_object_interface_wrapper(const void* object) \
    { \
        return class_name##_get_object((const type *)object); \
    } \
    \
    static inline void class_name##_deinit_interface_warpper(void* object) \
    { \
        class_name##_deinit((type *)object); \
    } \
    \
    static inline void class_name##_destroy_interface_wrapper(void* object) \
    { \
        class_name##_destroy((type *)object); \
    }


/* This is not part of interface but part of object_public, but to keep demo consistency I put this code here */
INTERFACE_OBJECT_WRAPPERS_CREATE(Object_public, object_public)

/* This is not part of interface but part of object_private, but to keep demo consistency I put this code here */
INTERFACE_OBJECT_WRAPPERS_CREATE(Object_private, object_private)

#endif