

#include <stdio.h>
#include <stdlib.h>
#include "MyLinkedList.h"

typedef struct {
    double data;
    Node *next;
} Node;

typedef struct {
    Node *head;
    unsigned int size;
} _MyLinkedList;

Node* createNode(doule data, Node* next)
{
    Node *pNode = (Node*)malloc(sizeof(Node));
    pNode->data = data;
    pNode->next = next;

    return p;
}

MyLinkedListP createList()
{
    MyLinkedListP pList = (MyLinkedListP)malloc(sizeof(List));
    pList->head = NULL;
    pList->size = 0;
    return pList;
}

void insertFirst(MyLinkedListP pList, double data)
{
    pList->head = createNode(data, pList->head);
    pList->size++;
}

void printList(MyLinkedListP pList)
{
    Node *pNode = pList->head;

    while (pNode)
    {
        printf("(%f)->", pNode->data);
        pNode = pNode->next;
    }
    printf("|| size: %u \n", pList->size);
}

MyLinkedListP cloneList(MyLinkedListP pList)
{
    _MyLinkedList *newList = createList();

    Node *old = pList->head, **copy = &(newList->head);
    newList->size = pList->size;

    while (old)
    {
        *copy = createNode(old->data, NULL);
        old = old->next;
        copy = &(*copy)->next;
    }

    return newList;
}

void freeList(MyLinkedListP pList)
{
    Node *pNode = pList->head, *pNode2;
    while (pNode)
    {
        pNode2 = pNode;
        pNode = pNode->next;
        free(pNode2);
    }

    free(pList);
}

