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

/* Initializes Queue */
void initializeQueue(_QUEUE_ * queue) {
    queue->head = NULL ;
    queue->current = NULL ;
    queue->tail = NULL ;
}

/* Adds an element to the Queue(FIFO)  */
int enqueue(_QUEUE_ *queue, void *data ) {
    _NODE_ *newNode = (_NODE_*) malloc(sizeof(_NODE_));
    if (newNode == NULL ) return FAILED;
    newNode->data = data ;
    newNode->next = NULL;
    if(queue->head == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    return SUCCESS;
}

/* Removes an element from the queue at head position*/
void *dequeue(_QUEUE_ * queue){
    if( queueEmpty(queue) ) {
        return NULL;
    }
    _NODE_ *tmp = queue->head;
    void *data = queue->head->data;
    if(queue->head == queue->tail ){
        queue->head = queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    free(tmp);
    return data;
}

/* Displays the whole queue */
void displayQueue(_QUEUE_ * queue, DISPLAY display){
    _NODE_ *node = queue->head;
    printf("%s\n", "Queue: -head-TO-tail-" );
    while(node != NULL) {
        display(node->data);
        node = node->next;
    }
    printf("\n");
}

/* Destroy the whole Queue */
void freeQueue(_QUEUE_ *queue) {
    _NODE_ *tmp = queue->head;
    while (queue->head != NULL ){
        queue->head = queue->head->next;
        free(tmp);
        tmp = queue->head;
    }
    queue->head = queue->tail = NULL;
}

/* returns 1 if the queue is empty */
int queueEmpty(const _QUEUE_ * queue ){
    return (queue->head == NULL);
}
