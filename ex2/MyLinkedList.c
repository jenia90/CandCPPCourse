/**
* @file MyLinkedList.c
* @author jenia90
* @version 1.0
* @date 25 Aug 2016
*
* @brief Implementation of LinkedList data structure
* @section DESCRIPTION:
* This is a basic implemenation of a LinkedList data structure for storing
* data as strings (char arrays).
*/

#define NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyLinkedList.h"

#define EMPTY_LIST_MSG "Empty!\n"
#define FINISHING_STRING "|| size: %u \n"
#define NODE_STRING "(%s)->"

/**
 * @brief A LinkedList node structure and pointer type definition
 */
typedef struct Node
{
    char *data;
    struct Node *next;
} *NodeP;

/**
 * @brief A LinkedList struct which defines the head Node of the list and its size.
 */
struct _MyLinkedList
{
    NodeP head;
    unsigned int size;
};

/**
 * @brief Allocates a new LinkedList node
 * @param data the data to be stored in the Node
 * @param next pointer to the next node
 * @return pointer to the new allocated Node if successful; null otherwise
 */
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
 * @brief Frees memory allocated to a given Node.
 * @param n Node pointer to free.
 */
void freeNode(NodeP n)
{
    free(n->data);
    free(n);
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
            printf(NODE_STRING, pNode->data);
            pNode = pNode->next;
        }
        printf(FINISHING_STRING, l->size);
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
    if(!newList)
    {
        return NULL;
    }

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
    if(l)
    {
        NodeP pNode = l->head, pNode2 = NULL;
        while (pNode)
        {
            pNode2 = pNode;
            pNode = pNode->next;
            freeNode(pNode2);
        }
        free(l->head);
        free(l);
    }
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
    if (!l)
    {
        return MYLIST_ERROR_CODE;
    }

    if (l->size == 0)
    {
        return 0;
    }

    int count = 0;
    NodeP currNode = l->head, prevNode = NULL;

    // Iterate over each Node in the list.
    while(currNode)
    {
        // if we found the required node we check if its the list head or not
        // and deal with each case separately.
        if(strcmp(currNode->data, val) == 0)
        {
            if(currNode == l->head)
            {
                l->head = currNode->next; // assign new head
                freeNode(currNode); // free obsolete Node memory
                currNode = l->head; // get next Node to check
                count++;
                l->size--;
            }
            else
            {
                //assert(prevNode);
                // link previous Node next pointer to next Node of current Node
                prevNode->next = currNode->next;
                freeNode(currNode); // free obsolete Node memory
                currNode = prevNode->next; // get next Node to check
                l->size--;
                count++;
            }
        }
        else
        {
            prevNode = currNode;
            currNode = currNode->next;
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
bool insertFirst(MyLinkedListP l, char *data)
{
    l->head = createNode(data, l->head);
    if (!l->head)
    {
        return false;
    }

    l->size++;

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
    if (!l)
    {
        return MYLIST_ERROR_CODE;
    }

    int count = 0;
    NodeP currNode = l->head;

    while(currNode)
    {
        if(strcmp(currNode->data, val) == 0)
        {
            count++;
        }

        currNode = currNode->next;
    }

    return count;
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
    // init the size variable with the memory allocated for the linkedlist itself
    int size = sizeof(MyLinkedListP);
    NodeP currNode = l->head;

    // foreach node in the list we get its allocated size and the size of the data it holds
    while(currNode)
    {
        size += sizeof(NodeP) + strlen(currNode->data) + 1;
        currNode = currNode->next;
    }

    return size;
}