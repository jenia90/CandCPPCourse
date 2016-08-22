

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyLinkedList.h"

#define EMPTY_LIST_MSG "Empty!\n"

typedef struct Node
{
    char *data;
    struct Node *next;
} *NodeP;

struct _MyLinkedList
{
    NodeP head;
    unsigned int size;
};

NodeP createNode(char *data, NodeP next)
{
    NodeP pNode = (NodeP)malloc(sizeof(struct Node));
    if(!pNode)
    {
        return NULL;
    }

    pNode->data = data;
    pNode->next = next;

    return pNode;
}

/**
 * @brief Allocates a new empty LinkedList
 * 			It is the caller's responsibility to free the returned LinkedList.
 *
 * RETURN VALUE:
 * @return a pointer to the new LinkedList, or NULL if the allocation failed.
 */
MyLinkedListP createList()
{
    MyLinkedListP l = (MyLinkedListP) malloc(sizeof(struct _MyLinkedList));
    if (l == NULL)
    {
        return NULL;
    }
    l->head = NULL;
    l->size = 0;
    return l;
}

/**
 * @brief print LinkedList l and it's contents- see school solution for the exact format.
 * @param l the LinkedList to print.
 */
void printList(MyLinkedListP l)
{
    if(l->size == 0)
    {
        printf(EMPTY_LIST_MSG);
    }

    else
    {
        NodeP pNode = l->head;

        while (pNode)
        {
            printf("(%c)->", *pNode->data);
            pNode = pNode->next;
        }
        printf("|| size: %u \n", l->size);
    }
}

/**
 * @brief Allocates a new MyLinkedList with the same values as l. It is the caller's
 * 			responsibility to free the returned LinkedList.
 * @param l the MyLinkedListP to clone.
 * RETURN VALUE:
 *   @return a pointer to the new LinkedList, or NULL if the allocation failed.
 */
MyLinkedListP cloneList(MyLinkedListP l)
{
    MyLinkedListP newList = createList();

    NodeP old = l->head, *copy = &(newList->head);
    newList->size = l->size;

    while (old)
    {
        *copy = createNode(old->data, NULL);
        old = old->next;
        copy = &(*copy)->next;
    }

    return newList;
}

/**
 * @brief Frees the memory and resources allocated to LinkedList l.
 * @param l the LinkedList to free.
 * If l is NULL, no operation is performed.
 */
void freeList(MyLinkedListP l)
{
    NodeP pNode = l->head, pNode2;
    while (pNode)
    {
        pNode2 = pNode;
        pNode = pNode->next;
        free(pNode2);
    }

    free(l);
}

/**
 * @brief remove all the ocuurences of val in l
 * @param l the LinkedList
 * @param val the value - char *
 * RETURN VALUE:
 *   @return number of elements that were removed. or MYLIST_ERROR_CODE if error occured
 */
int removeData(MyLinkedListP l, char *val)
{
    int count = 0;

    NodeP pNode = l->head, rmNode;

    while(pNode)
    {
        rmNode = pNode;
        pNode = pNode->next;

        if(strcmp(rmNode->data, val))
        {
            free(rmNode);
            count++;
        }
    }

    return count;
}

/**
 * @brief add val to the beginning of the list(the List may contain duplicates)
 * UPDATE -- val may be changed /deleted and your list should bot be effected by that.
 * @param l the LinkedList
 * @param val the value - char *
 * RETURN VALUE:
 *   @return true iff succeed
 */
bool insertFirst(MyLinkedListP pList, char *data)
{
    pList->head = createNode(data, pList->head);
    if (!pList->head)
    {
        return false;
    }

    pList->size++;

    return true;
}

/**
 * @brief search val in the list
 * @param l the LinkedList
 * @param val the value to add
 * RETURN VALUE:
 *   @return the number of val ocuurences in the list.  or MYLIST_ERROR_CODE if error occured
 */
int isInList(MyLinkedListP l, char *val)
{
    int count = 0;

    NodeP pNode = l->head;

    while(pNode)
    {
        if(strcmp(pNode->data, val))
        {
            count++;
        }

        pNode = pNode->next;
    }
}

/**
 * @brief get list size
 * @param l the LinkedList
 * RETURN VALUE:
 *   @return number of elements in the list.  or MYLIST_ERROR_CODE if error occured
 */
int getSize(MyLinkedListP l)
{
    return l->size;
}

/**
 * @brief Returns size in bytes of l and all it's contents
 *			eqvuilant to sum of sizeof for all the list contents
 * @param l the LinkedList
 * RETURN VALUE:
 *   @return the allocated size for l
 */
int getSizeOf(MyLinkedListP l)
{
    int size = 0;

    NodeP pNode = l->head;

    while(pNode)
    {
        size += strlen(pNode->data) + 1;
        pNode = pNode->next;
    }

    return size;
}