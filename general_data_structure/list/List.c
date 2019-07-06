#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
#define ElemType int
#define OK 1
#define ERR 0
#define true 1
#define false 0
#define bool int
#define Status int

typedef struct
{
    ElemType *elem;
    int length;
    int listSize;
} sqList;

Status initList(sqList *l)
{
    l->elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    l->length = 0;
    l->listSize = LIST_INIT_SIZE;
    return OK;
}

Status ensureCapacity(sqList *l)
{
    if (l->length == l->listSize)
    {
        l->elem = (ElemType *)realloc(l->elem, (l->listSize + LIST_INCREMENT) * sizeof(ElemType));
        if (l->elem == NULL)
        {
            printf("memory allocated failed");
            return ERR;
        }
        l->listSize += LIST_INCREMENT;
        return OK;
    }
}

Status destroyList(sqList *l)
{
    free(l->elem);
    l->elem = NULL;
    if (l->elem != NULL)
    {
        return ERR;
    }
    return OK;
}

Status clearList(sqList *l)
{
    l->length = 0;
    if (l->length != 0)
    {
        return ERR;
    }
    return OK;
}

bool listEmpty(sqList l)
{
    if (l.length == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int listLength(sqList l)
{
    return l.length;
}

Status getElem(sqList l, int i, ElemType *e)
{
    if (i > l.length)
    {
        // print somthing to indicate error
        // index out of range

        printf("index out of range, length=%d, index=%d\n", l.length, i);
        return ERR;
    }
    *e = l.elem[i];
    return OK;
}

int locateElem(sqList l, ElemType e, int (*compare)(ElemType, ElemType))
{
    for (int i = 0; i < l.length; i++)
    {
        if (compare(e, l.elem[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

Status priorElem(sqList l, ElemType curElem, ElemType *preElem)
{
    *preElem = -1;
    for (int i = 0; i < l.length; i++)
    {
        if (curElem == l.elem[i])
        {
            return OK;
        }
        *preElem = l.elem[i];
    }
    *preElem = -1;
    return ERR;
}

Status nextElem(sqList l, ElemType curElem, ElemType *nextElem)
{
    *nextElem = -1;
    for (int i = 0; i < l.length; i++)
    {
        if (l.elem[i] == curElem)
        {
            if (i < l.length - 1)
            {
                *nextElem = l.elem[i + 1];
            }
            else
            {
                *nextElem = -1;
            }
            return OK;
        }
    }
    return ERR;
}
Status listInsert(sqList *l, int i, ElemType e)
{
    if (i > l->length || i < 0)
    {
        printf("index out of range, length=%d, index=%d\n", l->length, i);
        return ERR;
    }
    ensureCapacity(l);
    for (int k = l->length; k > i; k--)
    {
        l->elem[k] = l->elem[k - 1];
    }
    l->elem[i] = e;
    l->length += 1;
    return OK;
}

Status listDelete(sqList *l, int i, ElemType *e)
{
    if (i > l->length - 1 || i < 0)
    {
        printf("index out of range, length=%d, index=%d\n", l->length, i);
        return ERR;
    }
    *e = l->elem[i];
    for (int k = i; k < l->length - 1; k++)
    {
        l->elem[k] = l->elem[k + 1];
    }
    l->length -= 1;
    return OK;
}

void listTraverse(sqList l)
{
    for (int i = 0; i < l.length; i++)
    {
        printf("%d: %d\n", i, l.elem[i]);
    }
}

int intCompare(int a, int b)
{
    return a == b ? 0 : a > b ? 1 : -1;
}
void main()
{

    sqList l;
    initList(&l);
    listInsert(&l, 0, 5);
    listInsert(&l, 0, 4);
    listInsert(&l, 0, 3);
    listInsert(&l, 0, 2);
    listInsert(&l, 0, 1);
    listTraverse(l);
    ElemType t;
    t = locateElem(l, 2, intCompare);
    printf("%d", t);
    destroyList(&l);
}