#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0
#define Status int
#define OK 1
#define ERR 0
#define ElemType int

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} LinkQueue;

Status initQueue(LinkQueue *q)
{
    q->front = (Node *)malloc(sizeof(Node));
    q->rear = (Node *)malloc(sizeof(Node));
    if (q->front == NULL || q->rear == NULL)
    {
        printf("memory allocation failed.");
        return ERR;
    }
    Node *rearNode = (Node *)malloc(sizeof(Node));
    if (rearNode == NULL)
    {
        printf("memory allocation failed.");
        return ERR;
    }
    rearNode->next = NULL;
    q->front->next = rearNode;
    q->rear->next = rearNode;
}

Status destroyQueue(LinkQueue *q)
{
    // not sure whether free like this would work, check later
    Node *t = q->front->next;
    while (t != q->rear->next)
    {
        Node *k = t;
        free(k);
        k->next = NULL;
        t = t->next;
    }
    return OK;
}

Status clearQueue(LinkQueue *q)
{
    Node *t = q->front->next;
    while (t != q->rear->next)
    {
        Node *k = t;
        free(k);
        k = NULL;
        t = t->next;
    }
    return OK;
}

bool queueEmpty(LinkQueue q)
{
    return q.front->next == q.rear->next;
}

int queueLength(LinkQueue q)
{
    int length = 0;
    Node *t = q.front->next;
    while (t != q.rear->next)
    {
        length += 1;
        t = t->next;
    }
    return length;
}

Status getHead(LinkQueue q, ElemType *e)
{
    if (queueEmpty(q))
    {
        printf("empty queue.\n");
        return ERR;
    }
    *e = q.front->next->next->data;
    return OK;
}

Status enQueue(LinkQueue *q, ElemType e)
{
    Node *t = (Node *)malloc(sizeof(Node));
    t->data = e;
    t->next == NULL;
    q->rear->next->next = t;
    q->rear->next = t;
    return OK;
}

Status deQueue(LinkQueue *q, ElemType *e)
{
    if (queueLength(*q) == 0)
    {
        printf("empty queue.\n");
        return ERR;
    }
    *e = q->front->next->next->data;
    Node *t = q->front->next->next;
    free(q->front->next);
    q->front->next = NULL;
    q->front->next = t;
    return OK;
}

void QueueTraverse(LinkQueue q)
{
    Node *t = q.front->next;
    while (t != q.rear->next)
    {
        t = t->next;
        printf("%d,", t->data);
    }
    printf("\n");
}
void main()
{
    LinkQueue q;
    initQueue(&q);
    enQueue(&q, 1);
    enQueue(&q, 2);
    enQueue(&q, 3);
    enQueue(&q, 4);
    enQueue(&q, 5);
    enQueue(&q, 6);
    QueueTraverse(q);
    int t;
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
    deQueue(&q, &t);
    printf("%d, ", t);
}