#include<stdio.h>
#include<string.h>
#include "dataStructures.h"
#include<stdlib.h>

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
        newNode->next = queue->head;
        queue->head = newNode;
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
void destroyQueue(_QUEUE_ *queue) {
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
    _QUEUE_ q;
    initializeQueue(&q);
    displayQueue(&q, (DISPLAY)displayEmployee); //type casting is must

    printf("queueEmpty: %d\n", queueEmpty(&q));

    Employee *samuel = (Employee*) malloc(sizeof(Employee));
    strcpy(samuel->name, "Samuel");
    samuel->age = 32;
    Employee *sally = (Employee*) malloc(sizeof(Employee));
    strcpy(sally->name, "Sally");
    sally->age = 28;
    Employee *susan = (Employee*) malloc(sizeof(Employee));
    strcpy(susan->name, "Susan");
    susan->age = 45;

    enqueue(&q, samuel);
    enqueue(&q, sally);
    enqueue(&q, susan);

    enqueue(&q, samuel);
    enqueue(&q, sally);
    enqueue(&q, susan);
    displayQueue(&q, (DISPLAY)displayEmployee);

    printf("queueEmpty: %d\n", queueEmpty(&q));

    Employee *employee;

    for(int i=0; i<4; i++) {
        employee = (Employee*) dequeue(&q);
        printf("Popped %s\n", employee->name );
        displayQueue(&q, (DISPLAY)displayEmployee);
    }
    displayQueue(&q, (DISPLAY)displayEmployee);
    destroyQueue(&q);
    displayQueue(&q, (DISPLAY)displayEmployee);
    printf("queueEmpty: %d\n", queueEmpty(&q));

    return 0;
}
