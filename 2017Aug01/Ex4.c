/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex4.c                */

/* Implementing search in a circular linked list */

#include<stdio.h>
#include<stdlib.h>

#define SUCCESS (1)
#define FAILED (0)

/* DISPLAY: type cast a function to void(*)(void*) */
typedef void (*DISPLAY)(void*);
/* COMPARE: type cast a function to int(*)(void*, void*) */
typedef int (*COMPARE)(void* , void*);


typedef struct _NODE_{
    void *data;
    struct _NODE_ *next;
} _CNODE_;

typedef struct _SINGLY_LINKED_LIST_{
    _CNODE_ *head;
    _CNODE_ *tail;
} _CLINKED_LIST_;


/* Returns a pointer to a node in the list on the basis of comparison result  */
_CNODE_ *getCNode(const _CLINKED_LIST_ *Clist, COMPARE compare ,  void *data){
    _CNODE_ *cnode = Clist->head;
    while(cnode != Clist->head){
        if(compare(cnode->data, data))  return cnode;
        cnode = cnode->next;
    }
    return NULL;
}

/* Initializes the list*/
void initializeCList(_CLINKED_LIST_ *Clist){
    Clist->head = NULL;
    Clist->tail = NULL;
}

/* Add a node before the head of the circular linked list */
int addCHead(_CLINKED_LIST_ *Clist, void *data){
    _CNODE_ *newCnode = (_CNODE_ *)malloc(sizeof(_CNODE_));
    if(newCnode == NULL) return FAILED;
    newCnode->next= NULL;   newCnode->data = data;

    if(Clist->head == NULL ){
        Clist->head = Clist->tail = newCnode;
    } else {
        Clist->tail->next = newCnode;
        newCnode->next = Clist->head;
        Clist->head = newCnode;
    }
    return SUCCESS;
}

/* Add a node at the tail on the list */
int addCTail(_CLINKED_LIST_ *Clist, void *data){
    _CNODE_ *newCnode = (_CNODE_ *)malloc(sizeof(_CNODE_));
    if(newCnode == NULL) return FAILED;
    newCnode->next = NULL;  newCnode->data = data;

    if(Clist->head == NULL ){
        Clist->tail = Clist->head = newCnode;
    } else {
        Clist->tail->next = newCnode;
        newCnode->next = Clist->head;
        Clist->tail = newCnode;
    }
    return SUCCESS;
}

/* Removes a node from the circular list */
int removeCNode(_CLINKED_LIST_ *Clist, _CNODE_ *cnode){
    if(cnode == Clist->head){
        Clist->tail->next = Clist->head = Clist->head->next;
        free(cnode);
        return SUCCESS;
    } else if (cnode == Clist->tail){
        _CNODE_ *tmp = Clist->head;
        while(tmp->next!=Clist->tail){
            tmp = tmp->next;
        }
        tmp->next = Clist->tail->next;
        Clist->tail = tmp;
        free(cnode);
    } else {
        _CNODE_ *tmp = Clist->head;
        while(tmp->next != cnode){
            tmp = tmp->next;
        }
        tmp->next = cnode->next;
        free(cnode);
        return SUCCESS;
    }
    return FAILED;
}

/* Display the List Nodes data on the basis of some display function */
void displayCLinkedList(const _CLINKED_LIST_ *Clist, DISPLAY display){
    _CNODE_ *cnode = Clist->head;
    printf("%s\n", "Clist: -head-TO-tail-" );
    if(cnode!=NULL){
        display(cnode->data);
        cnode = cnode->next;
        while(cnode != Clist->tail){
            display(cnode->data);
            cnode = cnode->next;
        }
        display(cnode->data);
    }
    printf("\n");
}

/* Returns 1 if the list is empty */
int ClistEmpty(const _CLINKED_LIST_ *Clist){
    return (Clist->head == NULL);
}

/* Free the list from the memory */
void freeCList(_CLINKED_LIST_ *Clist){
    _CNODE_ *cnode = Clist->head;
    Clist->tail->next = NULL;
    while(cnode != NULL){
        Clist->head  = Clist->head->next;
        free(cnode);
        cnode = Clist->head;
    }
    Clist->head = Clist->tail = NULL;
}

/* the data element of the node */
typedef struct INTdata {
    int val;
} INTdata ;


int compareINTdata(INTdata *e1, INTdata *e2) {
    if(e1->val==e2->val) { return SUCCESS; }
    else return FAILED;
}

void displayINTdata(INTdata *e) {
    printf("val: %d\n", e->val);
}

int main(){
    _CLINKED_LIST_ Clist;
    initializeCList(&Clist);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    INTdata *samuel = (INTdata*) malloc(sizeof(INTdata));
    samuel->val = 32;
    INTdata *sally = (INTdata*) malloc(sizeof(INTdata));
    sally->val = 28;
    INTdata *susan = (INTdata*) malloc(sizeof(INTdata));
    susan->val = 45;
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    printf("%d\n" , __LINE__);
    displayCLinkedList(&Clist, (DISPLAY)displayINTdata);
    //printf("%d\n" , __LINE__);
    addCHead(&Clist , samuel);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));

    addCHead(&Clist , sally); printf("%d\n" , __LINE__);
    addCHead(&Clist , susan); printf("%d\n" , __LINE__);
    addCTail(&Clist, sally); printf("%d\n" , __LINE__);

    displayCLinkedList(&Clist, (DISPLAY)displayINTdata); printf("%d\n" , __LINE__);

    removeCNode(&Clist, (Clist.head)->next);
    printf("%d\n" , __LINE__);

    displayCLinkedList(&Clist, (DISPLAY)displayINTdata);
    printf("%d\n" , __LINE__);

    displayINTdata((Clist.tail)->next->data);
    removeCNode(&Clist, (Clist.tail)->next);
    printf("%d\n" , __LINE__);

    displayCLinkedList(&Clist, (DISPLAY)displayINTdata);


    printf("%d\n" , __LINE__);
    removeCNode(&Clist, Clist.tail);
    printf("%d\n" , __LINE__);
    displayCLinkedList(&Clist, (DISPLAY)displayINTdata);
    printf("%d\n" , __LINE__);

    freeCList(&Clist);
    printf("%d\n" , __LINE__);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    printf("%d\n" , __LINE__);
    return 0;
}
