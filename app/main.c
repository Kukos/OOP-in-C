#include <public.h>
#include <private.h>
#include <interface.h>
#include <polymorphism.h>
#include <singleton.h>
#include <object_alloca.h>

#include <stdio.h>

void demo_public(void);
void demo_private(void);
void demo_interface(void);
void demo_polymorphism(void);
void demo_singleton(void);
void demo_object_alloca(void);

void demo_public(void)
{
    Object_public *object1;

    /* Object is public so it can be allocated on stack */
    Object_public object2;

    int data = 41;

    printf("Demo Public\n\n");
    object1 = object_public_create(&data, sizeof(data));
    object_public_init(&object2, &data, sizeof(data));

    /* Object is public, so we have direct access to fields */
    printf("OBJ1->size=%zu,data=%d\n", object_public_get_size(object1), *(int *)object1->object);

    /* Nothing is changing in objects, there have own copy of data */
    data = 17;
    printf("Data has been changed to:%d\n", data);

    /* Object is public, so we have direct access to fields */
    printf("OBJ2->size=%zu,data=%d\n", object2.size, *(int *)object_public_get_object(&object2));

    /* <class>_create alloc memory on heap, so we need to call <class>_destroy */
    object_public_destroy(object1);

    /* always call deinit after init (like in this case init allocate memory for fields) */
    object_public_deinit(&object2);

    printf("\n");
}

void demo_private(void)
{
    Object_private *object1;

    /* Object is public so it can't be allocated on stack */
    /* Object_private object2; */

    int data = 41;

    printf("Demo Private\n\n");
    object1 = object_private_create(&data, sizeof(data));

    /* Object is private, so we have not direct access to fields */
    /* size_t size = object1->size */
    printf("OBJ1->size=%zu,data=%d\n", object_private_get_size(object1), *(int *)object_private_get_object(object1));

    /* Nothing is changing in objects, there have own copy of data */
    data = 17;
    printf("Data has been changed to:%d\n", data);

    printf("OBJ1->size=%zu,data=%d\n", object_private_get_size(object1), *(int *)object_private_get_object(object1));

    /* <class>_create alloc memory on heap, so we need to call <class>_destroy */
    object_private_destroy(object1);

    printf("\n");
}

void demo_interface(void)
{
    Interface_object interface1;
    Object_public object1;

    Interface_object *interface2;
    Object_public *object2;
    int data = 41;

    printf("Demo Interface\n");

    object_public_init(&object1, &data, sizeof(data));
    interface_object_init(&interface1,
                          &object1,
                          object_public_get_size_interface_wrapper,
                          object_public_get_object_interface_wrapper,
                          object_public_deinit_interface_warpper,
                          NULL); /* object is allocated on stack */

    printf("Interface1->size=%zu,data=%d\n", interface_object_get_size(&interface1), *(int *)interface_object_get_object(&interface1));

    interface_object_deinit(&interface1);

    object2 = object_public_create(&data, sizeof(data));
    interface2 = interface_object_create(object2,
                                         object_public_get_size_interface_wrapper,
                                         object_public_get_object_interface_wrapper,
                                         object_public_deinit_interface_warpper,
                                         object_public_destroy_interface_wrapper); /* Object allocated on heap */

    printf("Interface2->size=%zu,data=%d\n", interface_object_get_size(interface2), *(int *)interface_object_get_object(interface2));

    interface_object_destroy(interface2);
    printf("\n");
}

void demo_polymorphism(void)
{
    Interface_object* interface;
    int data = 41;

    printf("Demo Polymorphism\n");

    interface = interface_object_create_object_public(&data, sizeof(data));
    printf("Interface(Public)->size=%zu,data=%d\n", interface_object_get_size(interface), *(int *)interface_object_get_object(interface));

    interface_object_destroy(interface);

    data = 17;
    printf("Data has been changed to 17\n");

    interface = interface_object_create_object_private(&data, sizeof(data));
    printf("Interface(Private)->size=%zu,data=%d\n", interface_object_get_size(interface), *(int *)interface_object_get_object(interface));

    interface_object_destroy(interface);

    printf("\n");
}

void demo_singleton(void)
{
    printf("Demo Singleton\n");

    printf("Setting int to 10\n");
    class_int_set(10);
    printf("Int = %d\n", class_int_get());

    printf("Setting double to 3.14\n");
    class_double_set(3.14);
    printf("Double = %lf\n", class_double_get());

    printf("\n");
}

void demo_object_alloca(void)
{
    printf("Demo object alloca\n");

    /* Private object cannot be alloc on stack, due forward declaration and placeholder,
       But OBJECT_ALLOCA works as well
    */

    Object_private* objectp;
    int data = 41;

    OBJECT_ALLOCA(objectp, object_private_sizeof(sizeof(data)));

    object_private_init(objectp, &data, sizeof(data));
    printf("StackObject->size=%zu,data=%d\n", object_private_get_size(objectp), *(int *)object_private_get_object(objectp));

    object_private_deinit(objectp);

    printf("\n");
}

int main(void)
{
    demo_public();
    demo_private();
    demo_interface();
    demo_polymorphism();
    demo_singleton();
    demo_object_alloca();

    return 0;
}