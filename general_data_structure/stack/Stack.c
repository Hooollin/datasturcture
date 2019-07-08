#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0
#define Status int
#define OK 1
#define ERR 0
#define ElemType int

#define INIT_STACK_SIZE 10
#define INCREMENT_SIZE 5

typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;

} Stack;

Status ensureCapacity(Stack *s)
{
    if (s->top - s->base == s->stackSize)
    {
        s->base = (ElemType *)realloc(s->base, sizeof(ElemType) * (s->stackSize + INCREMENT_SIZE));
        // s->base可能不在原来分配的内存基础上增长
        s->top = s->base + s->stackSize;
        s->stackSize += INCREMENT_SIZE;
        return OK;
    }
}

Status initStack(Stack *s)
{
    s->stackSize = INIT_STACK_SIZE;
    s->base = (ElemType *)malloc(sizeof(ElemType) * s->stackSize);
    if (s->base == NULL)
    {
        printf("memory allcation failed.\n");
        return ERR;
    }
    s->top = s->base;
    return OK;
}
Status destroyStack(Stack *s)
{
    if (s == NULL)
    {
        printf("stack not initialized.\n");
        return ERR;
    }
    free(s->top);
    free(s->base);
    return OK;
}

Status clearStack(Stack *s)
{
    s->base = (ElemType *)realloc(s->base, sizeof(ElemType) * INIT_STACK_SIZE);
    if (s->base == NULL)
    {
        printf("memory alloction failed.\n");
        return ERR;
    }
    s->top = s->base;
    return OK;
}

bool stackEmpty(Stack s)
{
    if (s.top == s.base)
    {
        return true;
    }
    return false;
}

int stackLength(Stack s)
{
    return s.top - s.base;
}

Status getTop(Stack s, ElemType *e)
{
    *e = *s.top;
    return OK;
}

Status push(Stack *s, ElemType e)
{
    ensureCapacity(s);
    *s->top = e;
    s->top += 1;
    return OK;
}

Status pop(Stack *s, ElemType *e)
{
    if (s->top == s->base)
    {
        printf("stack is empty.\n");
        return ERR;
    }
    *e = *(s->top - 1);
    s->top -= 1;
    return OK;
}
void stackTraverse(Stack s, void (*visit)(Stack))
{
    visit(s);
}

void main()
{
    Stack s;
    initStack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 4);
    push(&s, 5);
    push(&s, 6);
    push(&s, 7);

    printf("stack size: %d \n", stackLength(s));

    int t;
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
    pop(&s, &t);
    printf("%d \n", t);
}