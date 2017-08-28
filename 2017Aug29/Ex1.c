#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _NODE_ {
    void *data;
    struct _NODE_ *next;
} _NODE_ ;

typedef struct _STACK_ {
    _NODE_ *head;
    _NODE_ *tail;
} _STACK_ ;
typedef struct _STACK_* stack;

typedef struct string{
    char *str;
    int len;
} string;

stack newStack();
void stackPush(stack *stk, string x);
string stackPop(stack *stk);
int stackSize(stack stk);
int stackIsEmpty(const stack stk);
void stackTop(stack stk); //print top

void initializeStack(stack *stk);
void destroyStack(stack *stk);
void displayStack(const stack *stk);

int main(){
    s = newStack();
    returnn 0;
}
