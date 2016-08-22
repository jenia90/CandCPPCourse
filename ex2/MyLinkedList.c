

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
} *MyLinkedListP;

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

int getSize(MyLinkedListP l)
{
    return l->size;
}

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
