#ifndef KISS_H
#define KISS_H

#include <stddef.h>
#include <sys/types.h>
#include <stdbool.h>

/*
    @param[in] str - string

    @return  length of string (exluding \0)
*/
size_t my_strlen(const char* str);

/*
    @param[in] t - array
    @param[in] n - array length
    @param[in] key - key to find

    @return index in array where key is
            -1 if key does not exist in array
*/
ssize_t find_key(const int* t, size_t n, int key);


/*
    @param[in] n - number to check

    @return true if number is a power of 2
            false if not
*/
bool is_power2(unsigned int n);

/*
    @param[in] n - number to allign

    @return minimum power of 2 greater of equal n
*/
unsigned int allign_to_power2(unsigned int n);

/*
    @param[in] t - array
    @param[in] n - array length

    @return value of 3rd max element in array
*/
int max3(const int* t, size_t n);

#endif