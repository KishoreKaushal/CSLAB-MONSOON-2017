///////// Ex2.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex2.c      //
//////////////////////////////////


#include<stdio.h>
#include<stdlib.h>

#define FAILED (0)
#define SUCCESS (1)


typedef struct _NODE_{
    int data;
    struct _NODE_ *next;
} _NODE_;

typedef struct _QUEUE_{
    _NODE_ *front;
    _NODE_ *rear;
    int len;
} _QUEUE_;

void initializeQueue(_QUEUE_ *);                /* Initializes Queue*/
int enqueue(_QUEUE_ *, int );                 /* Adds an element in the queue(FIFO) */
int dequeue(_QUEUE_ *);                       /* Removes an element from the queue at rear position*/
void displayQueue(_QUEUE_ *);        /* Displays the whole queue */
void destroyQueue(_QUEUE_ *);                   /* Destroy the whole queue */
int queueEmpty(const _QUEUE_ *);                /* returns 1 if the queue is empty. */
int queueSize(_QUEUE_ *);                       /*returns the queue Size*/
void queueFront(_QUEUE_ *);                     /*prints front of the queue*/

/* Initializes Queue */
void initializeQueue(_QUEUE_ * queue) {
    queue->front = NULL ;
    queue->rear = NULL ;
    queue->len = 0;
}

/* returns the queue size */
int queueSize(_QUEUE_ * queue){
    return queue->len;
}

/* prints the fron of the queue*/
void queueFront(_QUEUE_ * queue){
    if(queue->len>0)
        printf("Queue Front: %d\n", queue->front->data);
}

/* Adds an element to the Queue(FIFO)  */
int enqueue(_QUEUE_ *queue, int data ) {
    if(queue->len<10){
        _NODE_ *newNode = (_NODE_*) malloc(sizeof(_NODE_));
        if (newNode == NULL ) return FAILED;
        newNode->data = data ;
        newNode->next = NULL;
        if(queue->front == NULL) {
            queue->front = queue->rear = newNode;
        } else {
            newNode->next = queue->front;
            queue->front = newNode;
        }
        queue->len+=1;
        return SUCCESS;
    } else {
        printf("Queue Full\n");
        return FAILED;
    }
}

/* Removes an element from the queue at front position*/
int dequeue(_QUEUE_ * queue){
    if( queueEmpty(queue) ) {
        printf("Queue Empty\n");
        return FAILED;
    }
    _NODE_ *tmp = queue->front;
    int data = queue->front->data;
    if(queue->front == queue->rear ){
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    free(tmp);
    queue->len-=1;
    return data;
}

/* Displays the whole queue */
void displayQueue(_QUEUE_ * queue){
    _NODE_ *node = queue->front;
    printf("%s\n", "Queue: -front-TO-rear-" );
    while(node != NULL) {
        printf("%d\n", node->data);
        node = node->next;
    }
    printf("\n");
}

/* Destroy the whole Queue */
void destroyQueue(_QUEUE_ *queue) {
    _NODE_ *tmp = queue->front;
    while (queue->front != NULL ){
        queue->front = queue->front->next;
        free(tmp);
        tmp = queue->front;
    }
    queue->front = queue->rear = NULL;
    queue->len =0;
}

/* returns 1 if the queue is empty */
int queueEmpty(const _QUEUE_ * queue ){
    return (queue->front == NULL);
}

void printMenu(){
    printf("\n\t<a>. Enqueue Integer\n");
    printf("\t<b>. Dequeue Integer\n");
    printf("\t<c>. Queue Size\n");
    printf("\t<d>. Queue Front\n");
    printf("\t<e>. Print Queue\n\n");
    printf("\t<q>. Exit\n");
    printf("\tOpt: ");
}

int main(){
    _QUEUE_ q;
    initializeQueue(&q);
    char op='a'; int data;
    while( op<='e' && 'a'<=op){
        printMenu();
        scanf(" %c", &op);
        printf("\n");
        switch(op){
            case 'q': destroyQueue(&q);
                    printf("Exiting...\n");
                break;
            case 'a': scanf(" %d", &data);
                    enqueue(&q, data);
                break;
            case 'b': if(!queueEmpty(&q))
                        printf("Dequeue Get : %d\n", dequeue(&q));
                    else
                        printf("Queue Empty \n");
                break;
            case 'c': printf("Queue Size: %d\n", queueSize(&q));
                break;
            case 'd': queueFront(&q);
                break;
            case 'e':
                    if(queueEmpty(&q)) printf("Queue Empty\n");
                    while(!queueEmpty(&q)){
                        printf("\n%d ", dequeue(&q));
                    }
                break;
            default : break;
        }
    }
    destroyQueue(&q);
    return 0;
}
