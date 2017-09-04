///////// Ex2.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex2.c      //
//////////////////////////////////


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FAILED 0
#define SUCCESS 1

/* ------------- DATA STRUCTURES ----------------- */

typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */

typedef struct _NODE_{
    void *data;
    struct _NODE_ *next;
} _NODE_;

typedef struct _STACK_{
    _NODE_ *head;
    _NODE_ *tail;
    int len;
} _STACK_;

typedef struct  string {
        char data[100];
        int len;
}   string ;


void initializeStack(_STACK_ *) ;               /* Initializes Stack */
void *pop(_STACK_ *);                           /* Pops an element out of the stack from the head */
int push(_STACK_ *, void *);                    /* Pushes an element on the head of the stack */
void displayStack(const _STACK_ *, DISPLAY );         /* Displays the whole stack from head to tail */
void destroyStack(_STACK_ *);                   /* Silently destroy the whole stack */
int stackEmpty(const _STACK_ *);                /* returns 1 if stack is empty */
void stackTop(const _STACK_ *);             /* prints the stack top data */

/* returns 1 if the stack s Empty */
int stackEmpty(const _STACK_ *stack) {
    return (stack->head == NULL);
}

/* Initializes the stack */
void initializeStack(_STACK_ *stack){
    stack->head = NULL;
    stack->tail = NULL;
    stack->len = 0;
}

/* push data onto the stack */
int push(_STACK_ *stack, void *data){
    _NODE_ *newNode = (_NODE_ *)malloc(sizeof(_NODE_));
    if(newNode == NULL ) return FAILED;
    newNode->data = data;
    if(stack->head == NULL ) {
        newNode->next = NULL;
        stack->tail = newNode;
    } else {
        newNode->next = stack->head;
    }
    stack->head = newNode;
    stack->len += 1;
    return SUCCESS;
}


void *pop(_STACK_ *stack) {
    _NODE_ *node = stack->head ;
    if(node == NULL) {
        printf("Stack Empty\n");
        return NULL;
    } else if (node == stack->tail) {
        stack->head = stack->tail = NULL;
        void *data = node->data;
        free(node);
        stack->len-=1;
        return data;
    } else {
        stack->head = stack->head->next;
        void *data = node->data;
        free(node);
        stack->len-=1;
        return data;
    }
}

void displayStack(const _STACK_ *stack , DISPLAY display) {
    _NODE_ *node;
    node =  stack->head;
    printf("STACK: -head-TO-tail-\n");
    while (node != NULL){
        display(node->data);
        node = node->next;
    }
    printf("\n");
}

void stackTop(const _STACK_ *stack){
    if(!stackEmpty(stack)){
        string *str = (string*)(stack->head->data);
        printf("%s\n", str->data);
    }
}

void destroyStack(_STACK_ *stack){
    _NODE_ *node;
    node  = stack->head;
    while(1){
        if(node == NULL ) {
            break;
        }
        stack->head = stack->head->next;
        void *data= node->data;
        free(data);
        free(node);
        node = stack->head;
    }
}

int compareString(string *s1, string *s2) {
        if(strcmp(s2->data, s1->data)==0) { return SUCCESS; }
            else return FAILED;
}

void displayString(string *s) {
        printf("MOVIE: %s\tLEN: %d\n", s->data, s->len);
}

//entry point

int main(){
    int n;
	_STACK_ stack;
    initializeStack(&stack);    //initialize stack
    string *movie;  // movie pointer
    printf("Enter the number of movie: "); scanf("%d" , &n);

    // push into stack
    for (int i=0; i<n; i++){
        movie = (string*) malloc(sizeof(string));
        printf("Enter the movie name: ");
        scanf(" %100[^\n]", movie->data);
        movie->len=strlen(movie->data);
        push(&stack , movie);
    }
    // display the whole stack
    displayStack(&stack, (DISPLAY)displayString); //type casting is must
    // print the stack top
    printf("%s","STACKTOP: " );stackTop(&stack);

    string *str;
    // popp operations
    for(int i=0; i<=n; i++){
        str = (string*)pop(&stack);
        printf("Popped: %s, STACK LENGTH: %d\n", str->data, stack.len);
        free(str);
    }
    //repeat the process again
    printf("Enter the number of movie: "); scanf("%d" , &n);

    // push a few more movies
    for (int i=0; i<n; i++){
        movie = (string*) malloc(sizeof(string));
        printf("Enter the movie name: \n");
        scanf(" %100[^\n]", movie->data);
        movie->len=strlen(movie->data);
        push(&stack , movie);
    }
/*
    for(int i=0; i<=n; i++){
        str = (string*)pop(&stack);
        printf("Popped: %s\n", str->data);
        free(str);
    }
*/

    // print the stack length
    printf("\nSTACK LENGTH: %d\n",  stack.len);

    destroyStack(&stack);
    return 0;
}
