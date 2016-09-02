//
// Created by jenia on 28/08/2016.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief clone a string
 */
void* cloneStr(const void* s)
{
    return strcpy(malloc(strlen(s) + 1), s);
}

/**
 * @brief free an string
 */
void freeStr(void* s)
{
    free(s);
}

/**
 * @brief hash value of key for HashTable with size tableSize
 *  assuming key pointer to string
 * @return number between 0-(tableSize-1)

 */
int strFcn (const void*  s, size_t tableSize)
{
    int res, i, k = 0;

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
    printf("%s", (char *)s);
}

/**
 *  strCompare - pointer to int comparison function:
 * @brief compare 2 strings
 *   returns zero int if both strings are equal, otherwise
 *   returns non-zero.
 */
int strCompare(const void* s1, const void* s2)
{
    return strcmp(s1, s2);
}