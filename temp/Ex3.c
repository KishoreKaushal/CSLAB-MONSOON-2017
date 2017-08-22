/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex3.c                */

#include<stdio.h>
#include<stdlib.h>
#define FAILED (0)
#define SUCCESS (1)
#define B_YELLOW "\033[1;33m"

/* DECALARING THE NODE STRUCTURE */
typedef struct _NODE_ {
    int data;
    struct _NODE_ *next;
} _NODE_ ;

typedef _NODE_ node;

/* DECLARING THE SINGLY LINKED LIST STRUCTURE */
typedef struct _SINGLY_LINKED_LIST_ {
    _NODE_ *head;
    _NODE_ *tail;
} _LINKED_LIST_;

/* FUNCTION TO INITIALIZE THE LIST */
void initializeList(_LINKED_LIST_ *list){
    list->head = list->tail = NULL;
}

/* THIS FUNCTION ADDS A NODE AT THE HEAD OF THE LIST */
int addHead(_LINKED_LIST_ *list, int val ){
    _NODE_ *newNode = (_NODE_*)malloc(sizeof(_NODE_));
    if(newNode == NULL) return FAILED;
    newNode->next = NULL ; newNode->data = val;
    if(list->head == NULL){
       list->tail = newNode ;
    } else {
        newNode->next = list->head;
    }
    list->head = newNode;
    return SUCCESS;
}

/* THIS WILL PRINT THE WHOLE LINKED LIST */
void displayLinkedList(_NODE_ *head){
    _NODE_ *node = head;
    while(node!=NULL){
        printf("%d-> " ,node->data );
        node = node->next;
    }
    printf("END\n");
}

/* REVERSE  THE DESIRED LINKED LIST */
_NODE_ * reverseLinkedList(_LINKED_LIST_  *list){
    if(list->head!=NULL){
        _NODE_ *cur = list->head ;
        _NODE_ *nt  = cur->next;
        _NODE_ *prev = NULL;

        if(list->head == NULL ) return NULL;
        while(cur!=NULL){
           nt = cur->next;
           cur->next = prev;
           prev = cur;
           cur = nt;
        }
        list->head = prev;
        return prev;
    }
    return NULL;
}

/* RETURNS THE DESIRED NODE ON THE BASIS OF SOME DATA COMPARISON */
_NODE_ * getNode(_LINKED_LIST_ *list, int data){
    //printf("%s\n", "in func getNode");
    _NODE_ *node = list->head;
    while(node!=NULL){
        if(node->data == data)
            return node;
        node = node->next;
    }
    return NULL;
}

/* THIS FUNCTION ADD A NODE CONINING THE PROVIDED VALUE IN THE DESIRED LINKED LIST AFTER A CERTAIN GIVEN NODE */
int addNode(_LINKED_LIST_ *list ,_NODE_ *node,  int  data){
    _NODE_ *afterThis = getNode(list , data);
    //printf("%s\n", "in func addNode");
    if(afterThis == NULL ) return FAILED;

    else {
        node->next = afterThis->next;
        afterThis->next = node;
    }
    return SUCCESS;
}

/*  THIS FUNCTION DELETES A DESIRED NODE "SAFELY" FROM THE LIST */
int deleteNode(_LINKED_LIST_ *list , _NODE_ *n ){
    _NODE_ *node = list->head;
    if(n==list->head && n==list->tail){
        freeList(list);
    } else {
        if(n==list->head){
            _NODE_ *tmp = list->head;
            list->head = list->head->next;
            free(tmp);
        } else{
            while(node->next!=n && node!=NULL ){
                node = node->next;
            }
            if(node->next == n){
                _NODE_ *tmp = node->next;
                node->next = node->next->next;
                free(tmp);
                return SUCCESS;
            }
        }
    }
    return FAILED;
}

/* THIS FUNCTION FREE THE MEMORY ALLOCATED TO THE LIST SAFELY */
void freeList(_LINKED_LIST_ *list){
    _NODE_ *node = list->head;
    while(node!=NULL){
        list->head = list->head->next;
        free(node);
        node = list->head;
    }
}

/* ENTRY POINT */
/* REST OF THE COMMENTED INSTRUCTIONS ARE PROVIDED INSIDE A PRINTF STATEMENT */
int main(){
    printf(B_YELLOW);
    _LINKED_LIST_ *list;
    initializeList(list);
    int n, data;
    scanf(" %d" , &n);
    for(int i=0; i<n; i++){
        scanf(" %d" , &data);
        addHead(list , data);
    }
    printf("\n");
    displayLinkedList(list->head);
    /* JUST FOR DEMONSTRATION I'LL ASSUME THAT THE ADDED NODE VALUE WILL BE 56 ,.... DEFINITELY ONE CAN USER OTHER VALUES TOO. OR ONE TAKE INPUT FROM USERS DIRECTLY */
    printf("adding node with val 56 after a node containing data= your input\n");
    _NODE_ *newNode = (_NODE_*)malloc(sizeof(_NODE_));
    newNode->data = 56;
    int val;
    scanf(" %d" , &val);

    if(addNode(list , newNode , val)==0){
        printf("Failed To add Node\n");
    } else {
        printf("Node Added\n");
        displayLinkedList(list->head);
    }

    printf("\ndeleting all nodes with data-value = your input\n");
    scanf(" %d" , &val);
    _NODE_ *temp = getNode(list , val);
    do{
        deleteNode(list , temp);
        temp = getNode(list , val);
    } while(temp!=NULL);
    displayLinkedList(list->head);


    printf("\nReversing the list..\n");
    displayLinkedList(reverseLinkedList(list));
    freeList(list);
    return 0;
}
