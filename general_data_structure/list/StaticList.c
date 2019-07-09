#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR 0
#define bool int
#define true 1
#define false 0
#define ElemType int
#define Status int
#define INIT_LIST_SIZE 100
#define INCREMENT_SIZE 10

typedef struct
{
    ElemType data;
    int next; // or name it as cur.
} Node;

typedef struct
{
    Node *elem;
    int length;
    int listSize;
} StaticLinkedList;
Status ensureCapacity(StaticLinkedList *sl)
{
    if (sl->length == sl->listSize)
    {
        sl->elem = realloc(sl->elem, sizeof(Node) * (INCREMENT_SIZE + sl->listSize));
    }
    if (sl->elem == NULL)
    {
        printf("memory allocation failed");
        return ERR;
    }
    return OK;
}

Status initStaticLinkedList(StaticLinkedList *sl)
{
    // 初始化静态列表
    sl->elem = (Node *)malloc(sizeof(Node) * INIT_LIST_SIZE);
    if (sl->elem == NULL)
    {
        printf("malloc memory failed");
        return ERR;
    }
    sl->length = 0;
    sl->listSize = INIT_LIST_SIZE;
    // 初始化空闲列表
    for (int i = 0; i < sl->listSize; i++)
    {
        sl->elem[i].next = i + 1;
    }
    sl->elem[sl->listSize - 1].next = 0;
    return OK;
}

int mallocNode(StaticLinkedList *sl)
{
    int next = sl->elem[0].next; // next就是分配出来的空间
    if (sl->elem[0].next != 0)   // 如果空闲列表没满
    {
        sl->elem[0].next = sl->elem[next].next; //将sl->elem[next]指向next的下一个
    }
    return next;
}

Status append(StaticLinkedList *sl, ElemType val)
{
    ensureCapacity(sl);
    int location = mallocNode(sl);
    sl->elem[location].data = val;
}
void main()
{
    StaticLinkedList sl;
    initStaticLinkedList(&sl);
}