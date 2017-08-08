/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex1.c                */

/* required function in this exercise is   getCNode() */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FAILED (0)
#define SUCCESS (1)


/* defining a node type */
typedef struct _NODE_{
    /* *data : can be used if you want to point to any type of data*/
    /*whether be a structure of two int or a structure with a string and a double value. */
    void *data;
    /* next pointer points to next element in the list*/
    struct _NODE_ *next;
} _NODE_;

/* Linked list type holds a linked list */
typedef struct _SINGLY_LINKED_LIST_{
    _NODE_ *head;
    _NODE_ *tail;
    _NODE_ *current;
} _LINKED_LIST_;


/* typedef to change to a appropriate name */
typedef _NODE_ _CNODE_;
typedef _LINKED_LIST_ _CLINKED_LIST_;

typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */


/* initializes a singly circular linked list*/
void initializeCList(_CLINKED_LIST_ *Clist){
    Clist->head = Clist->tail = Clist->current = NULL;
}

/* add a head element to the circular linked list */
int addCHead(_CLINKED_LIST_ *Clist, void *data){
    _CNODE_ *newCnode = (_CNODE_ *)malloc(sizeof(_CNODE_));
    if(newCnode == NULL) return FAILED; /*if memory allocation failed*/
    newCnode->next= NULL;   newCnode->data = data;

    /*if list is empty*/
    if(Clist->head == NULL ){
        Clist->head = Clist->tail = newCnode;
    } else {
        /* if list is not empty*/
        Clist->tail->next = newCnode;
        newCnode->next = Clist->head;
        Clist->head = newCnode;
    }
    return SUCCESS;
}

/* add a tail element to the circular linked list */
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

/* remove a desired node from the circular node */
int removeCNode(_CLINKED_LIST_ *Clist, _CNODE_ *cnode){
    /* if cnode is the head element */
    if(cnode == Clist->head){
        Clist->tail->next = Clist->head = Clist->head->next;
        free(cnode);
        return SUCCESS;
    } else if (cnode == Clist->tail){
        /* if cnode is the tail element  */
        _CNODE_ *tmp = Clist->head;
        while(tmp->next!=Clist->tail){
            tmp = tmp->next;
        }
        tmp->next = Clist->tail->next;
        Clist->tail = tmp;
        free(cnode);
    } else {
        /* if it is in middle of the list */
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

/* returns a node on the basis of some comparison */
/* compare here is the function pointer */
_CNODE_ *getCNode(const _CLINKED_LIST_ *Clist, COMPARE compare ,  void *data){
    _CNODE_ *cnode = Clist->head;
    while(cnode != Clist->head){
        if(compare(cnode->data, data))  return cnode;
        cnode = cnode->next;
    }
    return NULL;
}

/* display the circular linked list */
/* display here is the function pointer */
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

/* returns 1 if the circular linked list is empty*/
int ClistEmpty(const _CLINKED_LIST_ *Clist){
    return (Clist->head == NULL);
}

/* free the linked list from the memory */
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

/* structure of the desired data */
typedef struct student {
    int val;
}   student;

/* comparison function for the desired data structure */
int comparestudent(student *e1, student *e2) {
    if(e1->val==e2->val) { return SUCCESS; }
    else return FAILED;
}

/* display fucntion of the desired data structure */
void displaystudent(student *e) {
    printf("Val: %d\n",  e->val);
}


int main(){
    _CLINKED_LIST_ Clist;
    initializeCList(&Clist);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    student *samuel = (student*) malloc(sizeof(student));
    samuel->val = 32;
    student *sally = (student*) malloc(sizeof(student));
    sally->val = 28;
    student *susan = (student*) malloc(sizeof(student));
    susan->val = 45;
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    displayCLinkedList(&Clist, (DISPLAY)displaystudent);
    addCHead(&Clist , samuel);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));

    addCHead(&Clist , sally);
    addCHead(&Clist , susan);
    addCTail(&Clist, sally);
    displayCLinkedList(&Clist, (DISPLAY)displaystudent);
    removeCNode(&Clist, (Clist.head)->next);
    displayCLinkedList(&Clist, (DISPLAY)displaystudent);
    displaystudent((Clist.tail)->next->data);
    removeCNode(&Clist, (Clist.tail)->next);
    displayCLinkedList(&Clist, (DISPLAY)displaystudent);
    removeCNode(&Clist, Clist.tail);
    displayCLinkedList(&Clist, (DISPLAY)displaystudent);

    freeCList(&Clist);
    printf("List Empty: %d\n" , ClistEmpty(&Clist));
    return 0;
}
