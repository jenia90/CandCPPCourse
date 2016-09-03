//
// Created by jenia on 28/08/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define SIZE_OF_INT sizeof(int)

/**
 * @brief clone an int
 */
void* cloneInt(const void* i)
{
    int *temp = malloc(sizeof(int));
    return memcpy(temp, i, SIZE_OF_INT);
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
    return memcmp(i1, i2, SIZE_OF_INT);
}
