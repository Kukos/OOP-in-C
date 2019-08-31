#include <kiss.h>
#include <limits.h>

#define KISS
#ifndef KISS
size_t my_strlen(const char* str)
{
    const char* ptr = str;
    const char* const start = ptr;

    while (*ptr++);

    return (size_t)(ptr - start - 1);
}

ssize_t find_key(const int* t, size_t n, int key)
{
    if (n == 0) return -1;
    if (t[n - 1] == key) return (ssize_t)n - 1;
    return find_key(t, n - 1, key);
}

bool is_power2(unsigned int n)
{
    if (n <= 1) return n == 1;

    return n % 2 ? false : is_power2(n / 2);
}

unsigned int allign_to_power2(unsigned int n)
{
    unsigned i = 0;

    if (is_power2(n))
        return  n;

    while (n)
    {
        n >>= 1U;
        ++i;
    }

    return 1U << i;
}

int max3(const int* t, size_t n)
{
    int values[3] = {INT_MIN, INT_MIN, INT_MIN};

    for (size_t i = 0; i < n; ++i)
    {
        if (t[i] > values[0])
        {
            values[2] = values[1];
            values[1] = values[0];
            values[0] = t[i];
        }
        else if (t[i] > values[1])
        {
            values[2] = values[1];
            values[1] = t[i];
        }
        else if (t[i] > values[2])
        {
            values[2] = t[i];
        }
    }

    return values[2];
}
#else

size_t my_strlen(const char* str)
{
    size_t i = 0;
    while (str[i] != '\0')
        ++i;

    return i;
}

ssize_t find_key(const int* t, size_t n, int key)
{
    for (size_t i = 0; i < n; ++i)
        if (t[i] == key)
            return (ssize_t)i;

    return -1;
}

bool is_power2(const unsigned int n)
{
    if (n == 0) return false;

    /*
        Power2 is the only one set of number that fullfils this property.
        We have set only 1 bit (1 << k). So we have
        1 000 ... 000
        When we substract 1 from number we will have 0 and all 1
        0 111 ... 111

        Lemma:
            Let b be the base of numbers. Let n = b^k. Then b - 1 and b are different for all positions.

        Proof (Substraction on paper)
        When we need substarct m from number n. We will have 2 cases.  On position p n[p] >= m[p] then n[p] = n[p] - m[p]
        if n[p] <= m[p] then you need borrow from p + 1.

        Let m = 1. N = b^k --> (b - 1) 0000. 000 Then substraction will go into 2nd case until reach digit (b - 1)

        So from lemma we have:
            n & (n - 1) == 0 <-> n is power of 2

    */
    return (n & (n - 1)) == 0;
}

static inline unsigned log2_ceil(unsigned int n);
static inline unsigned log2_ceil(unsigned int n)
{
    if (n == 0) return 0;
    if (n == 1) return 0;

    unsigned i = 0;
    while (n > 0)
    {
        n /= 2;
        ++i;
    }

    return i;
}


unsigned int allign_to_power2(unsigned int n)
{
    /*
        To allign number to power of 2
        We need to calculate:
        2^(ceil(log2(n)))
    */
    return 1U << log2_ceil(n);
}

/*
    Idea is simple.
    We will remember 3 greatest numbers from subset t[0] ... t[i].

    In ith step we will change t[i] with one of the biggest value if t[i] is >= than our value.
    All values <= than changed biggers value will be shifted.

    I.e

    we have 3 2 1 and t[i] = 3
    Then 2nd max will be 3. But 3rd max should be changed also, because we are sure
    that 2nd max was >= than 3rd max. So if 2nd max is no longer 2nd. Then he will be 3rd.
*/
int max3(const int* t, size_t n)
{
    int values[3] = {INT_MIN, INT_MIN, INT_MIN};

    for (size_t i = 0; i < n; ++i)
    {
        if (t[i] > values[0])
        {
            values[2] = values[1];
            values[1] = values[0];
            values[0] = t[i];
        }
        else if (t[i] > values[1])
        {
            values[2] = values[1];
            values[1] = t[i];
        }
        else if (t[i] > values[2])
        {
            values[2] = t[i];
        }
    }

    return values[2];
}

#endif