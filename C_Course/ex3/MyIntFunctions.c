/**
* @file MyIntFunctions.c
* @author jenia90
* @version 1.0
* @date 1 Sep 2016
*
* @brief A file containing set of functions for dealing with int values in a hash table
* @section DESCRIPTION:
* A set of basic functions to deal with int keys in a hash table data structure
*/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#define SIZE_OF_INT sizeof(int)

/**
 * @brief clone an int
 */
void* cloneInt(const void* i)
{
    assert(i);
    return memcpy(malloc(sizeof(int)), i, SIZE_OF_INT);
}

/**
 * @brief free an int
 */
void freeInt( void* i)
{
    assert(i);
    free(i);
}

/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to an int
 * @return number between 0-(tableSize-1)

 */
int intFcn (const void* key, size_t tableSize)
{
    assert(key);
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
    assert(key);
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
    assert(i1 && i2);
    return memcmp(i1, i2, SIZE_OF_INT);
}
