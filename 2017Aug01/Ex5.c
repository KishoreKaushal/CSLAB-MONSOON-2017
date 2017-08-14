#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FAILED (0)
#define SUCCESS (1)

typedef struct _DNODE_{
    void *data;
    struct _DNODE_ *next;
    struct _DNODE_ *prev;
} _DNODE_;

typedef struct _DOUBLY_LINKED_LIST_{
    _DNODE_ *head;
    _DNODE_ *tail;
    _DNODE_ *current;
} _DLINKED_LIST_;


void initializeDList(_DLINKED_LIST_*);                /* Initializes the doubly linked list */
int addDHead(_DLINKED_LIST_*, void*);                 /* Adds data to the doubly linked lists's head */
int addDTail(_DLINKED_LIST_*, void*);                 /* Adds data to the doubly linked list's tail */
void removeDNode(_DLINKED_LIST_*, _DNODE_*);               /* Removes a node from the doubly linked list */
_DNODE_ *getDNode(const _DLINKED_LIST_*, COMPARE , void*);   /* Returns a pointer to the node containing a specific data item */
void displayDLinkedList(const _DLINKED_LIST_*, DISPLAY);    /* Displays the doubly linked list */
int DlistEmpty(const _DLINKED_LIST_*);
void freeDList(_DLINKED_LIST_ *); /*Free the allocated doubly linked list from the memory*/

/* Initializes the doubly linked list */
void initializeDList(_DLINKED_LIST_ *Dlist){
    Dlist->head = NULL;
    Dlist->tail = NULL;
    Dlist->current = NULL;
}

/* Adds data to the doubly linked lists's head */
int addDHead(_DLINKED_LIST_ *Dlist, void *data){
    _DNODE_ *newDnode = (_DNODE_ *)malloc(sizeof(_DNODE_));
    if(newDnode == NULL ) return FAILED;
    newDnode->data = data;
    newDnode->next = newDnode->prev = NULL;
    if(Dlist->head == NULL ){
        Dlist->tail = newDnode;
    } else {
        newDnode->next = Dlist->head;
        Dlist->head->prev = newDnode;
    }
    Dlist->head = newDnode;
    return SUCCESS;
}

/* Adds data to the doubly linked list's tail */
int addDTail(_DLINKED_LIST_ *Dlist , void *data){
    _DNODE_ *newDnode = (_DNODE_ *)malloc(sizeof(_DNODE_));
    if (newDnode == NULL ) return FAILED;
    newDnode->next = newDnode->prev = NULL;
    newDnode->data = data;
    if(Dlist->head == NULL ) {
        Dlist->head = Dlist->tail = newDnode;
    } else {
        Dlist->tail->next = newDnode;
        newDnode->prev = Dlist->tail;
        Dlist->tail = newDnode;
    }
    return SUCCESS;
}

/* Removes a node from the doubly linked list */
void removeDNode(_DLINKED_LIST_ *Dlist, _DNODE_ *Dnode){
    if(Dnode == Dlist->head){
        if(Dlist->head->next == NULL ){
            Dlist->head = Dlist->tail = NULL ;
        } else {
            Dlist->head->next->prev = NULL;
            Dlist->head = Dlist->head->next;
        }
    } else if(Dnode == Dlist->tail) {
        Dlist->tail->prev->next = NULL;
        Dlist->tail = Dlist->tail->prev;
    } else {
        Dnode->next->prev = Dnode->prev;
        Dnode->prev->next = Dnode->next;
    }
    free(Dnode);
}

/* Returns a pointer to the node containing a specific data item */
_DNODE_ *getDNode(const _DLINKED_LIST_ *Dlist, COMPARE compare, void *data){
    _DNODE_ *Dnode = Dlist->head;
    while(Dnode!=NULL){
        if(compare(Dnode->data , data)){
            return Dnode;
        }
        Dnode = Dnode->next;
    }
    return NULL;
}

/* Displays the doubly linked list */
void displayDLinkedList(const _DLINKED_LIST_ *Dlist , DISPLAY display){
    _DNODE_ *Dnode = Dlist->head;
    printf("D-LINKEDLIST: -head-TO-tail-\n");
    while(Dnode!=NULL){
        display(Dnode->data);
        Dnode = Dnode->next;
    }
    printf("\n");
}

/* returns 1 if D-LINKEDLIST is empty.*/
int DlistEmpty(const _DLINKED_LIST_* Dlist){
    return (Dlist->head == NULL);
}

/*Free the allocated doubly linked list from the memory*/
void freeDList(_DLINKED_LIST_ * Dlist){
    _DNODE_ *Dnode = Dlist->head;
    while(Dnode != NULL ){
        Dlist->head = Dlist->head->next;
        free(Dnode);
        Dnode = Dlist->head;
    }
}

/* Defining the student structure */
typedef struct student {
    char name[32];
    int ID;
}   student;

/* To print the student INFO */
void PrintStruc(student *s){
    printf("Name: %s\tID: %d\n", s->name, s->ID);
}

/* Return 1 if s1->ID is greater than s2->ID */
int compareStu(student *s1, student *s2){
    return (s1->ID > s2->ID);
}

/* Entry point */
int main(int argc, char const *argv[]) {

    return 0;
}
