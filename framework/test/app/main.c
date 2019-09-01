#include <oop.h>

#include <object.h>
#include <array.h>
#include <variables.h>

#include <stdio.h>
#include <stdlib.h>


#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"

#define TO_STRING(x) _TO_STRING(x)
#define _TO_STRING(x) (#x)

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#define TEST(expr) \
    do { \
        if (expr) \
        { \
            fprintf(stderr, COLOR_GREEN "PASSED:"  COLOR_RESET "%s\n", TO_STRING(expr)); \
        } \
        else \
        { \
            fprintf(stderr, COLOR_RED "FAILED:" COLOR_RESET "%s\n", TO_STRING(expr)); \
            exit(1); \
        } \
    } while (0)


void test_alloca(void);
void test_singleton(void);
void test_iterators(void);

void test_alloca(void)
{
    Object_private* op1;
    Object_private* op2;
    Object_private* op3;

    int data1 = 17;
    double data2 = 3.14;
    void* data3 = &data1;

    OOP_OBJECT_ALLOCA(op1, object_private_sizeof(sizeof(data1)));
    OOP_OBJECT_ALLOCA(op2, object_private_sizeof(sizeof(data2)));
    OOP_OBJECT_ALLOCA(op3, object_private_sizeof(sizeof(data3)));

    object_private_init(op1, &data1, sizeof(data1));
    object_private_init(op2, &data2, sizeof(data2));
    object_private_init(op3, &data3, sizeof(data3));

    TEST(object_private_get_size(op1) == sizeof(data1));
    TEST(object_private_get_size(op2) == sizeof(data3));
    TEST(object_private_get_size(op3) == sizeof(data2));

    TEST(*(int *)object_private_get_object(op1) == data1);
    TEST(*(double *)object_private_get_object(op2) == data2);
    TEST(*(void **)object_private_get_object(op3) == data3);

    object_private_deinit(op1);
    object_private_deinit(op2);
    object_private_deinit(op3);
}

void test_singleton(void)
{
    int data1 = 41;
    double data2 = 3.14;
    void* data3 = &data1;

    var1_set(data1);
    var2_set(data2);
    var3_set(data3);

    TEST(var1_get() == data1);
    TEST(var2_get() == data2);
    TEST(var3_get() == data3);

    data1 = 17;
    data2 = 1.89;
    data3 = &data2;

    var1_set(data1);
    var2_set(data2);
    var3_set(data3);

    TEST(var1_get() == data1);
    TEST(var2_get() == data2);
    TEST(var3_get() == data3);
}

OOP_CHECK_FUNC_NAME_CONVENTION(object_private)
OOP_CHECK_FUNC_ITERATOR(array)

void test_iterators(void)
{
    int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Array* a = array_create(ARRAY_SIZE(t));
    for (size_t i = 0; i < ARRAY_SIZE(t); ++i)
        array_set(a, i, t[i]);

    Array_iterator* it;
    int *node;
    int val;
    size_t i = 0;

    OOP_FOR_EACH(it, a, Array, node, val)
    {
        TEST(*node == t[i]);
        TEST(val == t[i]);
        ++i;
    }
    TEST(i == ARRAY_SIZE(t));
    array_iterator_destroy(it);

    i = 0;
    OOP_FOR_EACH_NODE(it, a, Array, node)
    {
        TEST(*node == t[i]);
        ++i;
    }
    TEST(i == ARRAY_SIZE(t));
    array_iterator_destroy(it);

    i = 0;
    OOP_FOR_EACH_DATA(it, a, Array, val)
    {
        TEST(val == t[i]);
        ++i;
    }
    TEST(i == ARRAY_SIZE(t));
    array_iterator_destroy(it);

    i = ARRAY_SIZE(t) - 1;
    OOP_FOR_EACH_REVERSE(it, a, Array, node, val)
    {
        TEST(*node == t[i]);
        TEST(val == t[i]);
        --i;
    }
    TEST(i == (size_t)-1);
    array_iterator_destroy(it);

    i = ARRAY_SIZE(t) - 1;
    OOP_FOR_EACH_NODE_REVERSE(it, a, Array, node)
    {
        TEST(*node == t[i]);
        --i;
    }
    TEST(i == (size_t)-1);
    array_iterator_destroy(it);

    i = ARRAY_SIZE(t) - 1;
    OOP_FOR_EACH_DATA_REVERSE(it, a, Array, val)
    {
        TEST(val == t[i]);
        --i;
    }
    TEST(i == (size_t)-1);
    array_iterator_destroy(it);

    array_destroy(a);
}


int main(void)
{
    test_alloca();
    test_singleton();
    test_iterators();

    return 0;
}