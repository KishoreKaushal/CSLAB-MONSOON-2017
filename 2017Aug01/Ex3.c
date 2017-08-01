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
typedef struct student {
    char name[32];
    int id;
}   student;

int compareStudent(student *s1, student *s2) {
    if(s1->id==s2->id) { return SUCCESS; }
        else return FAILED;
}

void displayStudent(student *s) {
    printf("NAME: %s\tID: %d\n", s->name, s->id);
}


int main(){
    _LINKED_LIST_ list;
    initializeList(&list);
    student *samuel = (student*) malloc(sizeof(student));
    strcpy(samuel->name, "Samuel");
    samuel->id = 32;
    student *sally = (student*) malloc(sizeof(student));
    strcpy(sally->name, "Sally");
    sally->id = 28;
    student *susan = (student*) malloc(sizeof(student));
    strcpy(susan->name, "Susan");
        susan->id = 45;

    addHead(&list , samuel);
    displayLinkedList(&list , (DISPLAY)displayStudent);
    printf("\n");
    addHead(&list , sally);
    displayLinkedList(&list , (DISPLAY)displayStudent);
    printf("\n");
    addTail(&list , susan);
    displayLinkedList(&list , (DISPLAY)displayStudent);
    printf("\n");
    freeList(&list);
    displayLinkedList(&list , (DISPLAY)displayStudent);
    return 0;
}
