#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataStructures.h"


void initializeList(_LINKED_LIST_ *list){
    list->head = NULL;
    list->current = NULL;
    list->tail = NULL;
}

int addHead(_LINKED_LIST_* list, void* data){
    _NODE_ *node = (_NODE_*)malloc(sizeof(_NODE_));
    if(node == NULL) return 0;
    node->data = data;
    if(list->head == NULL){
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;
    return 1;
}

int addTail(_LINKED_LIST_* list, void* data){
    _NODE_ *node = (_NODE_*)malloc(sizeof(_NODE_));
    if(node == NULL) return 0;
    node->data = data;
    node->next = NULL;
    if(list->head == NULL ){
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int searchList(const _LINKED_LIST_ *list, void *data){
    _NODE_ * node = list->head ;
    while(node != NULL) {
        if(node->data == data){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

_NODE_ *getNode(const _LINKED_LIST_ *list, COMPARE compare, void *data){
    _NODE_ *node = list->head;
    while(node != NULL ){
        if(compare(node->data, data) == 0){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void displayLinkedList(const _LINKED_LIST_ *list , DISPLAY display){
    //printf("Linked List\n");
    _NODE_ *current = list->head;
    while(current != NULL){
        display(current->data);
        current = current->next;
    }
}


void removeNode(_LINKED_LIST_ *list, _NODE_ *node) {
    if (node == list->head) {
        if (list->head->next == NULL) {
            list->head = list->tail = NULL;
        } else {
            list->head = list->head->next;
        }
    } else {
        _NODE_ *tmp = list->head;
        while (tmp != NULL && tmp->next != node) {
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            tmp->next = node->next;
        }
    }
    free(node);
}

int listEmpty(const _LINKED_LIST_ *list) {
    return (list->head == NULL);
}

void freeList(_LINKED_LIST_ *list) {
    while(!listEmpty(list)){
        removeNode(list, list->head);
    }
}


/* Declaring  structure for the employee data */
/*

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
    _LINKED_LIST_ list;
    initializeList(&list);
    Employee *samuel = (Employee*) malloc(sizeof(Employee));
    strcpy(samuel->name, "Samuel");
    samuel->age = 32;
    Employee *sally = (Employee*) malloc(sizeof(Employee));
    strcpy(sally->name, "Sally");
    sally->age = 28;
    Employee *susan = (Employee*) malloc(sizeof(Employee));
    strcpy(susan->name, "Susan");
    susan->age = 45;

    addHead(&list , samuel);
    displayLinkedList(&list , (DISPLAY)displayEmployee);
    printf("\n");
    addHead(&list , sally);
    displayLinkedList(&list , (DISPLAY)displayEmployee);
    printf("\n");
    addTail(&list , susan);
    displayLinkedList(&list , (DISPLAY)displayEmployee);
    printf("\n");
    freeList(&list);
    displayLinkedList(&list , (DISPLAY)displayEmployee);
    return 0;
}
*/
