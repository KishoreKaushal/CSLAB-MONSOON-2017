#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "dataStructures.h"

int stackEmpty(const _STACK_ *stack) {
    return (stack->head == NULL);
}

void initializeStack(_STACK_ *stack){
    stack->head = NULL;
    stack->current = NULL;
    stack->tail = NULL;
}

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
    return SUCCESS;
}

void *pop(_STACK_ *stack) {
    _NODE_ *node = stack->head ;
    if(node == NULL) {
        return NULL;
    } else if (node == stack->tail) {
        stack->head = stack->tail = NULL;
        void *data = node->data;
        free(node);
        return data;
    } else {
        stack->head = stack->head->next;
        void *data = node->data;
        free(node);
        return data;
    }
}

void displayStack(_STACK_ *stack , DISPLAY display) {
    _NODE_ *node;
    node =  stack->head;
    printf("STACK: -head-TO-tail-\n");
    while (node != NULL){
        display(node->data);
        node = node->next;
    }
    printf("\n");
}

void destroyStack(_STACK_ *stack){
    _NODE_ *node;
    node  = stack->head;
    while(1){
        if(node == NULL ) {
            break;
        }
        stack->head = stack->head->next;
        free(node);
        node = stack->head;
    }
}

typedef struct _employee {
        char name[32];
            unsigned char age;
}   Employee;

int compareEmployee(Employee *e1, Employee *e2) {
        if(strcmp(e1->name, e2->name)==0) { return SUCCESS; }
            else return FAILED;
}

void displayEmployee(Employee *e) {
        printf("Name: %s\tAge: %d\n", e->name, e->age);
}

int main(){
	_STACK_ stack;
    initializeStack(&stack);
    displayStack(&stack, (DISPLAY)displayEmployee); //type casting is must

    printf("stackEmpty: %d\n", stackEmpty(&stack));

    Employee *samuel = (Employee*) malloc(sizeof(Employee));
    strcpy(samuel->name, "Samuel");
    samuel->age = 32;
    Employee *sally = (Employee*) malloc(sizeof(Employee));
    strcpy(sally->name, "Sally");
    sally->age = 28;
    Employee *susan = (Employee*) malloc(sizeof(Employee));
    strcpy(susan->name, "Susan");
    susan->age = 45;

    push(&stack, samuel);
    push(&stack, sally);
    push(&stack, susan);

    push(&stack, samuel);
    push(&stack, sally);
    push(&stack, susan);
    displayStack(&stack, (DISPLAY)displayEmployee);

    printf("stackEmpty: %d\n", stackEmpty(&stack));

    Employee *employee;

    for(int i=0; i<4; i++) {
        employee = (Employee*) pop(&stack);
        printf("Popped %s\n", employee->name );
        displayStack(&stack, (DISPLAY)displayEmployee);
    }
    displayStack(&stack, (DISPLAY)displayEmployee);
    destroyStack(&stack);
    displayStack(&stack, (DISPLAY)displayEmployee);
    printf("stackEmpty: %d\n", stackEmpty(&stack));

    return 0;
}
