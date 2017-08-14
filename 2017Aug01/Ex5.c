/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex5.c                */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define FAILED (0)
#define SUCCESS (1)

typedef struct _DNODE_{
    int data;
    struct _DNODE_ *next;
    struct _DNODE_ *prev;
} _DNODE_;

typedef struct _DOUBLY_LINKED_LIST_{
    _DNODE_ *head;
    _DNODE_ *tail;
    _DNODE_ *current;
} _DLINKED_LIST_;

/*--------------------------------------------------------------*/

void initializeDList(_DLINKED_LIST_*);                /* Initializes the doubly linked list */
int addDHead(_DLINKED_LIST_*, int);                 /* Adds data to the doubly linked lists's head */
int addDTail(_DLINKED_LIST_*, int);                 /* Adds data to the doubly linked list's tail */
void removeDNode(_DLINKED_LIST_*, _DNODE_*);               /* Removes a node from the doubly linked list */
_DNODE_ *getDNode(const _DLINKED_LIST_*, int);   /* Returns a pointer to the node containing a specific data item */
void displayDLinkedList(const _DLINKED_LIST_*);    /* Displays the doubly linked list */
int DlistEmpty(const _DLINKED_LIST_*);
void freeDList(_DLINKED_LIST_ *); /*Free the allocated doubly linked list from the memory*/

/*--------------------------------------------------------------*/

/* Initializes the doubly linked list */
void initializeDList(_DLINKED_LIST_ *Dlist){
    Dlist->head = Dlist->tail = Dlist->current = NULL;
}

/* Adds data to the doubly linked lists's head */
int addDHead(_DLINKED_LIST_ *Dlist, int data){
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
int addDTail(_DLINKED_LIST_ *Dlist , int data){
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

/* REVERSE  THE DESIRED DOUBlY LINKED LIST  AND RETURNS THE HEAD POINTER OF THE LIST*/
_DNODE_ * reverseDLinkedList(_DLINKED_LIST_  *Dlist){
    if(Dlist->head!=NULL){
        _DNODE_ *tail = Dlist->head; /*will be tail after reversing*/
        _DNODE_ *cur = Dlist->head;
        _DNODE_ *nt = cur->next;
        _DNODE_ *prev = NULL;

        if(Dlist->head == NULL ) return NULL ;
        while(cur!=NULL){
            nt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nt;
        }
        Dlist->head = prev;
        Dlist->tail = tail;
        _DNODE_ *temp=Dlist->head;
        while(temp!=Dlist->tail){
            temp->next->prev = temp;
            temp = temp->next;
        }
        return prev;
    }
    return NULL;
}


/* THIS FUNCTION ADD A NODE CONINING THE PROVIDED VALUE IN THE DESIRED LINKED LIST AFTER A CERTAIN GIVEN NODE */
int addDNode(_DLINKED_LIST_ *Dlist ,_DNODE_ *Dnode,  int  data){
    _DNODE_ *afterThis = getDNode(Dlist , data);
    //printf("%s\n", "in func addNode");
    if(afterThis == NULL ) return FAILED;

    else  {
        Dnode->next = afterThis->next;
        if(afterThis->next != NULL ) afterThis->next->prev = Dnode;
        else{
            Dlist->tail = Dnode;
        }
        Dnode->prev = afterThis;
        afterThis->next = Dnode;
    }
    return SUCCESS;
}

/* Returns a pointer to the node containing a specific data item */
_DNODE_ *getDNode(const _DLINKED_LIST_ *Dlist, int data){
    _DNODE_ *Dnode = Dlist->head;
    while(Dnode!=NULL){
        if(Dnode->data==data){
            return Dnode;
        }
        Dnode = Dnode->next;
    }
    return NULL;
}

/* Displays the doubly linked list */
void displayDLinkedList(const _DLINKED_LIST_ *Dlist){
    _DNODE_ *Dnode = Dlist->head;
    //printf("D-LINKEDLIST: -head-TO-tail-\n");
    printf("\nHEAD--> ");
    while(Dnode!=NULL){
        printf("%d <--> " , Dnode->data);
        Dnode = Dnode->next;
    }
    printf("\b\bTAIL\n");
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


/* Entry point */
int main(int argc, char const *argv[]) {
    srand(time(NULL));  // seed for random number generation
    int n, data, val;
    scanf("%d" , &n);
    _DLINKED_LIST_ Dlist;
    initializeDList(&Dlist);
    for(int i=0; i<n/2; i++){
        data = rand()%10+10;
        printf("Adding Head: %d\n" ,data);
        addDHead(&Dlist , data);
    }
    n = n - (n/2);
    for(int i=0; i<n; i++){
        data = rand()%10+15;
        printf("Adding Tail: %d\n" ,data);
        addDTail(&Dlist , data);
    }
    displayDLinkedList(&Dlist);

    printf("%s\n","Add a node after a node containing data=val\nInput Val: " );
    scanf(" %d" , &val);
    printf("Input data: "); scanf(" %d", &data);
    _DNODE_ *newNode = (_DNODE_*)malloc(sizeof(_DNODE_));
    newNode->data = data;
    if(addDNode(&Dlist , newNode , val)==0){
        printf("Failed to add node.\n");
    } else {
        printf("Node with data(=%d) Successfully added after a node containing value: %d\n",data ,val );
    }

    displayDLinkedList(&Dlist);

    printf("Input node value to delete: \n");
    scanf(" %d" , &val);
    printf("\nDeleting All Nodes with data-value = %d\n", val);

    _DNODE_ *temp = getDNode(&Dlist , val);
    if(temp!=NULL){
        do{
            removeDNode(&Dlist , temp);
            temp = getDNode(&Dlist , val);
        } while(temp!=NULL);
    } else {
        printf("Desired data-value is not in the list.\n");
    }
    displayDLinkedList(&Dlist);
    printf("Reversing The DList:\n");
    reverseDLinkedList(&Dlist);

    displayDLinkedList(&Dlist);
    freeDList(&Dlist);
    return 0;
}
