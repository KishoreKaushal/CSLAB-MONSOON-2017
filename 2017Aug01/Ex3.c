/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex3.c                */

#include<stdio.h>
#include<stdlib.h>
#define FAILED (0)
#define SUCCESS (1)

typedef struct _NODE_ {
    int data;
    struct _NODE_ *next;
} _NODE_ ;

typedef _NODE_ node;

typedef struct _SINGLY_LINKED_LIST_ {
    _NODE_ *head;
    _NODE_ *tail;
} _LINKED_LIST_;

void initializeList(_LINKED_LIST_ *list){
    list->head = list->tail = NULL;
}

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



void displayLinkedList(_NODE_ *head){
    _NODE_ *node = head;
    while(node!=NULL){
        printf("%d-> " ,node->data );
        node = node->next;
    }
    printf("END\n");
}

_NODE_ * reverseLinkedList(_LINKED_LIST_  *list){
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

_NODE_ * getNode(_LINKED_LIST_ *list, int data){
    printf("%s\n", "in func getNode");
    _NODE_ *node = list->head;
    while(node!=NULL){
        if(node->data == data)
            return node;
        node = node->next;
    }
    return NULL;
}

int addNode(_LINKED_LIST_ *list ,_NODE_ *node,  int  data){
    _NODE_ *afterThis = getNode(list , data);
    printf("%s\n", "in func addNode");
    if(afterThis == NULL ) return FAILED;

    else {
        node->next = afterThis->next;
        afterThis->next = node;
    }
    return SUCCESS;
}

int deleteNode(_LINKED_LIST_ *list , _NODE_ *n ){
    _NODE_ *node = list->head;
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
    return FAILED;
}

void freeList(_LINKED_LIST_ *list){
    _NODE_ *node = list->head;
    while(node!=NULL){
        list->head = list->head->next;
        free(node);
        node = list->head;
    }
}

int main(){
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

    printf("\ndeleting a node with data-value = your input\n");
    scanf(" %d" , &val);
    deleteNode(list , getNode(list , val));
    displayLinkedList(list->head);


    printf("\nReversing the list..\n");
    displayLinkedList(reverseLinkedList(list));
    freeList(list);
    return 0;
}
