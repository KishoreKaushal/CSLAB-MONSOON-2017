/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex4.c                */

/* required function in this exercise is   getCNode() */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define FAILED (0)
#define SUCCESS (1)


/* defining a node type */
typedef struct _NODE_{
    int data;
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

/* initializes a singly circular linked list*/
void initializeCList(_CLINKED_LIST_ *Clist){
    Clist->head = Clist->tail = Clist->current = NULL;
}

/* add a head element to the circular linked list */
int addCHead(_CLINKED_LIST_ *Clist, int data){
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
int addCTail(_CLINKED_LIST_ *Clist, int data){
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
_CNODE_ *getCNode(const _CLINKED_LIST_ *Clist, int data){
    _CNODE_ *cnode = Clist->head;

    if(cnode !=NULL){
        if(cnode->data == data) return cnode;
        cnode = cnode->next;
        while(cnode != Clist->tail){
            if(cnode->data == data) return cnode;
            cnode = cnode->next;
        }
        if(cnode->data == data) return cnode;
    }
    return NULL;
}


/* display the circular linked list */
void displayCLinkedList(const _CLINKED_LIST_ *Clist){
    _CNODE_ *cnode = Clist->head;
    //printf("%s\n", "Clist: -head-TO-tail-" );
    /*if only one element*/
    printf("[HEAD]--> ");

    if(Clist->head == Clist->tail){
        printf("%d" , cnode->data);
    } else {
        if(cnode!=NULL){
            printf("%d--> ", cnode->data);
            cnode = cnode->next;
            while(cnode != Clist->tail){
                printf("%d--> " , cnode->data);
                cnode = cnode->next;
            }
            printf("%d" , cnode->data);
        }
    }

    printf("--> [TAIL]--> [HEAD]\n");
//    printf("\n");
}



/* returns 1 if the circular linked list is empty*/
int ClistEmpty(const _CLINKED_LIST_ *Clist){
    return (Clist->head == NULL);
}

/* free the linked list from the memory */
void freeCList(_CLINKED_LIST_ *Clist){
    if(!ClistEmpty(Clist)){
        _CNODE_ *cnode = Clist->head;
        Clist->tail->next = NULL;
        while(cnode != NULL){
            Clist->head  = Clist->head->next;
            free(cnode);
            cnode = Clist->head;
        }
        Clist->head = Clist->tail = NULL;
    }
}

/* merge the two circular linked list as required by the question */
void mergeClist( _CLINKED_LIST_ *Clist1 , _CLINKED_LIST_ *Clist2 ){
    if(Clist1->head == Clist1->tail){
        Clist1->head->next = Clist2->head;
        Clist1->tail = Clist2->head;
        Clist2->head->next = Clist1->head;
    }else if(Clist2->head != NULL){
        _CNODE_ *current1 = Clist1->head; _CNODE_ *current2 = Clist2->head;
        _CNODE_ *Clist1_NXT  , *Clist2_NXT;
        Clist1_NXT = Clist1->head->next;    Clist2_NXT = Clist2->head->next;
        while(current2!=Clist2->tail){
            current1->next = current2;
            current2->next = Clist1_NXT;
            current1 = Clist1_NXT;
            current2 = Clist2_NXT;
            Clist1_NXT = Clist1_NXT->next;
            Clist2_NXT = Clist2_NXT->next;
        }
        current1->next = current2 ;
        current2->next = Clist1_NXT;
        if(Clist1_NXT == Clist1->head) {
            Clist1->tail = current2;
        }
        printf("Clist1_NXT: %d\n", Clist1_NXT->data );
    }
    initializeCList(Clist2);
}


int main(){
    srand(time(NULL));  // seed for random number generation
    _CLINKED_LIST_ Clist1 , Clist2;
    initializeCList(&Clist1); initializeCList(&Clist2);
    int n1, n2 , data, temp;
    printf("Enter the size of both the lists (larger one first): \n");
    scanf("%d %d" , &n1 , &n2);
    if(n1==0|| n2==0){  printf("Can't be zero.\n"); exit(1);}
    if(n1<n2){
        printf("n1 < n2 : therefore swapping the size.\n");
        temp = n1; n1 = n2; n2 = temp;
    }
    printf("Enter the elements of larger list(n=%d): \n" , n1);
    for (int i=0; i<n1; i++){
        scanf(" %d" , &data);
        addCHead(&Clist1,  data);
    }
    printf("C-LIST1: \n");
    displayCLinkedList(&Clist1);
    printf("Enter the elements of larger list(n=%d): \n" , n2);
    for (int i=0; i<n2; i++){
        scanf(" %d" , &data);
        addCHead(&Clist2, data);
    }
    printf("C-LIST2: \n");
    displayCLinkedList(&Clist2);

    printf("merging Clist2 in Clist1: \n");
    mergeClist(&Clist1,  &Clist2);
    printf("merged-List: \n");
    displayCLinkedList(&Clist1);

    freeCList(&Clist1);
    //freeCList(&Clist2);
    return 0;
}
