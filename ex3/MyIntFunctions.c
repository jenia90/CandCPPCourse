//
// Created by jenia on 28/08/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include "Key.h"


/**
 * @brief clone an int
 */
void* cloneInt(const void* i)
{
    int *temp = (int *) i;
    return temp;
}

/**
 * @brief free an int
 */
void freeInt( void* i)
{
    free(i);
}

/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to an int
 * @return number between 0-(tableSize-1)

 */
int intFcn (const void* key, size_t tableSize)
{
    int res = *(int*)key % (int)tableSize;
    return res < 0 ? res + (int)tableSize : res;
}
/**
 * @brief print a string
 *  assuming key pointer to an int
 *
 */
void intPrint (const void* key)
{
    printf("%d", *(int*)key);
}

/**
 * @brief compare 2 ints
 *   returns zero int if both ints are equal, otherwise
 *   returns non-zero.
 *
 */
int intCompare(const void *i1, const void *i2)
{
    int val1 = *(int*)i1, val2 = *(int*)i2;
    return val1 - val2;
}
