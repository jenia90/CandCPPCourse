/**
* @file MyStringFunctions.c
* @author jenia90
* @version 1.0
* @date 1 Sep 2016
*
* @brief A file containing set of functions for dealing with string (char *) values in a hash table
* @section DESCRIPTION:
* A set of basic functions to deal with string (char *) keys in a hash table data structure
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define PRINT_STR "%s"

/**
 * @brief clone a string
 */
void* cloneStr(const void* s)
{
    assert(s);
    return strcpy(malloc(strlen(s) + 1), s);
}

/**
 * @brief free an string
 */
void freeStr(void* s)
{
    assert(s);
    free(s);
}

/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to string
 * @return number between 0-(tableSize-1)

 */
int strFcn (const void*  s, size_t tableSize)
{
    assert(s);
    int res, i, k = 0;

    // sums each of the string's char value.
    for(i = 0; i < (int)strlen((char *)s); i++)
    {
        k += ((char *)s)[i];
    }

    res = k % (int)tableSize;

    return res < 0 ? res + (int)tableSize : res;
}

/**
 * @brief print a string
 *  assuming key pointer to string
 *
 */
void strPrint (const void*  s)
{
    assert(s);
    printf(PRINT_STR, (char *)s);
}

/**
 *  strCompare - pointer to int comparison function:
 * @brief compare 2 strings
 *   returns zero int if both strings are equal, otherwise
 *   returns non-zero.
 */
int strCompare(const void* s1, const void* s2)
{
    assert(s1 && s2);
    return strcmp(s1, s2);
}