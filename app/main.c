#include <public.h>
#include <private.h>
#include <stdio.h>

void demo_public(void);
void demo_private(void);

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


int main(void)
{
    demo_public();
    demo_private();
    return 0;
}