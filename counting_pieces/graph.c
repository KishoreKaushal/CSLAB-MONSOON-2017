/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"


char *colour[] = {
    "[color=red]",
    "[color=blue]",
    "[color=green]",
    "[color=cyan]",
    "[color=yellow]",
    "[color=black]",
};


// initializeGraph
void initializeGraph(_GRAPH_ *graph) {
    graph->vc = 0;
    graph->name = NULL;
    graph->AM = NULL;
    graph->node = NULL;
}

void freeGraph(_GRAPH_ *graph){
    // free graph
    for (int i=0; i<graph->vc; i++) {
        // free each node data
    //    printf("\nFreeing Node : %d\n", i);
        if(graph->node[i]->adjacent!=NULL) {
            free(graph->node[i]->adjacent);
        }
        free(graph->node[i]);
    }
    free(graph->node);
    for(int i=0; i<graph->vc; i++)
        if(graph->AM[i]!=NULL) free(graph->AM[i]);
    free(graph->AM);
    free(graph->name);
}

void createGraphFromAM(_GRAPH_ *graph) {
    graph->node = (_GNODE_ **)malloc(sizeof(_GNODE_) * graph->vc) ; // array of pointers to different nodes

    for (int i=0; i<graph->vc ; i++){
        graph->node[i] = (_GNODE_ *)malloc(sizeof(_GNODE_));
        graph->node[i]->adjNum=0;
        graph->node[i]->nodeNumber = i;     // node number
        graph->node[i]->adjacent = (_GNODE_ ***)malloc(sizeof(_GNODE_)) ; // because allocating 0 byte is tricky
    }

    for (int i=0; i<graph->vc ; i++){
        for (int j=0; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){     // check for adjacency between i and j
                graph->node[i]->adjNum++;   // if adjacent increment number of adjacent nodes number
                graph->node[i]->adjacent = (_GNODE_ ***)realloc( graph->node[i]->adjacent , sizeof(_GNODE_) * (graph->node[i]->adjNum+1));   // reallocate the memory to hold new adjacent member
                graph->node[i]->adjacent[graph->node[i]->adjNum-1] = &graph->node[j];    // points to another node
            }
        }
        graph->node[i]->adjacent[graph->node[i]->adjNum] = NULL; // set last adjacent node to NULL
    }
}

// read a file for the Adjacency matrix and returns the number of vertices.
// the user is responsible to manually freeing the memory allocated by this function
// Holds all the data in a structural format
int readGraphFromTxt(char *filename , _GRAPH_ *graph){
    FILE *fp;
    fp = fopen(filename, "r");
    int vc;
    int **AM;
    char *gname;
    if(fp != NULL){
        char graphName[100];
        fgets(graphName, 99, fp );
        gname = (char *)malloc(sizeof(char)*101);
        strncpy(gname , graphName, 99);
        fgets(graphName, 99, fp );
        fscanf(fp , "%d\n" , &vc);
        AM = (int **) malloc(sizeof(int*) * vc);
        for(int i=0; i<vc; i++){
            AM[i] = (int *)malloc(sizeof(int) * vc);
            if(fscanf(fp, "%s" , graphName) ==EOF)    break;
            for(int j=0; j<vc; j++){
                AM[i][j] = graphName[j] - '0';
            }
        }
    }
    if(AM != NULL) graph->AM = AM;
    if(gname != NULL )  graph->name = gname;
    graph->vc = vc;
    createGraphFromAM(graph);
    fclose(fp);
    return vc;
}


void print2Dint( int **arr, size_t rows , size_t cols){
    printf("\n");
    for (size_t i=0; i<rows; i++){
        for (size_t j =0; j<cols ; j++){
            printf("%d\t" , arr[i][j]);
        }
        printf("\n");
    }
}


void printGraph(_GRAPH_ *graph){
    printf("\nGRAPH NAME : %s" , graph->name);
    printf("VERTICES : %d\n" , graph->vc);
    print2Dint(graph->AM , graph->vc , graph->vc);
}

void printAllGraphNodeNumber(const _GRAPH_ *graph) {
    printf("NODES IN THE GRAPH: ");
    for (int i=0; i<graph->vc ; i++) {
        printf("\nNode Number : %d\n|----->  Adjacent Nodes \t\tAddr. Of Node\t\t\tAddr. Of NodeNumber",graph->node[i]->nodeNumber);
        for (int j=0; j<graph->node[i]->adjNum; j++){
            printf("\n|----->  %d \t\t\t\t%d\t\t\t%d, ", (*graph->node[i]->adjacent[j])->nodeNumber , graph->node[i]->adjacent[j] , &graph->node[i]->adjacent[j]);
        }
    }
}

static void displayNodeNumber(_GNODE_ **node){
    printf("%d ", node);
}

int * BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal){
    _LINKED_LIST_ visited;
    initializeList(&visited);
    _QUEUE_ q;
    initializeQueue(&q);
    int flag=0;
    int *prev = (int *)malloc(sizeof(int) * graph->vc);
    for (int i=0; i<graph->vc ; i++){
        prev[i] = -1;
    }
    addHead(&visited , root);
    enqueue(&q, root);
    printf("Start Node: %d , Addr: %d\n", (*root)->nodeNumber , root );
    printf("End Node: %d , Addr: %d\n", (*goal)->nodeNumber , goal );
    while (!queueEmpty(&q)){
        _GNODE_ **current = (_GNODE_ *) dequeue(&q);
        if(current==goal){
            freeList(&visited);
            freeQueue(&q);
            flag =1;
            break;
        }
        for (int i=0; i<(*current)->adjNum; i++){
            if(!searchList(&visited, (*current)->adjacent[i])){
                prev[ (*(*current)->adjacent[i])->nodeNumber ] = (*current)->nodeNumber;
                addHead(&visited , (*current)->adjacent[i]);
                enqueue(&q, (*current)->adjacent[i]);
            }
        }
    }
    freeList(&visited);
    freeQueue(&q);
    int *shortestPath = NULL;
    int cnt=0;
    if(flag){
        shortestPath = (int *)malloc(sizeof(int));
        int bktrace = (*goal)->nodeNumber;
        printf("\n%d ", bktrace);
        shortestPath[cnt++] = bktrace;
        while (bktrace != (*root)->nodeNumber) {
            bktrace = prev[bktrace];
            shortestPath = (int*)realloc(shortestPath , sizeof(int) * (cnt+1) );
            shortestPath[cnt++] = bktrace;
            if(bktrace==-1) break;
            printf("-->%d ", bktrace);
        }
    }
    free(prev);
    return shortestPath;
}

// making a dot file
void makeDotFile(_GRAPH_ *graph) {
    char outFileName[30];
    int isolation=0;
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fp = fopen( outFileName , "w+");
    fprintf(fp, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                fprintf(fp, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fp , "%d\n", i); }
    }
    fprintf(fp , "\n}" );
    fclose(fp);
}

int checkEdgeInPath(int *shortestPath , int pathLength , int vertex1 , int vertex2 ){
    for (size_t i=1; shortestPath[i]!=-1 && i<pathLength+1; i++ ){
        if(shortestPath[i-1]==vertex1 && shortestPath[i]==vertex2)
            return 1;
    }
    for (size_t i=1; shortestPath[i]!=-1 && i<pathLength+1; i++){
        if(shortestPath[i-1]==vertex2 && shortestPath[i]==vertex1)
            return 1;
    }
    return 0;
}


void publishShortestPathGraph( _GRAPH_ * graph ,int *shortestPath, int pathLength){
    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;
    fprintf(fout, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                if(checkEdgeInPath(shortestPath, pathLength, i ,j))
                    fprintf(fout, "%d -- %d  [color=red];\n", i , j);
                else fprintf(fout, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fout , "%d\n", i); }
    }
    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);
}


int checkNodeInPiece(int *pieceArr , int nodeNum){
    int *ptr = &pieceArr[0];
    while (ptr && (*ptr)!=-1){
        if((*ptr)==nodeNum)
            return 1;
        ptr++;
    }
    return 0;
}

int countPiecesAndPublish(_GRAPH_ * graph){
    int pieces = 0, ptrIdx;
    if(graph->vc>0) pieces++;
    int **ptr = (int **)malloc(sizeof(int ) * pieces);
    int flag=0;
    /*------BFS (modified) --- COUNTING PIECES------*/
    int iter=0;
    _GNODE_ **root = &graph->node[iter];
    _LINKED_LIST_ visited;
    _QUEUE_ q;
    initializeList(&visited);

    while(pieces&&iter<graph->vc){
        ptrIdx =0;
        initializeQueue(&q);
        root = &graph->node[iter];
        addHead(&visited , root);
        ptr[pieces-1] = (int *)malloc(sizeof(int)*(ptrIdx+2));  
        ptr[pieces-1][ptrIdx++] = (*root)->nodeNumber;
        enqueue(&q, root);
        while (!queueEmpty(&q)){
            _GNODE_ **current = (_GNODE_ *) dequeue(&q);
            for (int i=0; i<(*current)->adjNum; i++){
                if(!searchList(&visited, (*current)->adjacent[i])){

                    ptr[pieces-1] = (int *)realloc( ptr[pieces-1] , sizeof(int)*(ptrIdx+2));
                    ptr[pieces-1][ptrIdx++] =  (*(*current)->adjacent[i])->nodeNumber;

                    addHead(&visited , (*current)->adjacent[i]);
                    enqueue(&q, (*current)->adjacent[i]);
                }
            }
        }
        ptr[pieces-1][ptrIdx] = -1;
        // check for unvisited nodes
        for(int i=0; i<graph->vc; i++){
            if(!searchList(&visited, &graph->node[i])){
                iter =  i;
                pieces++;
                ptr = (int **)realloc( ptr , sizeof(int ) * pieces);
                flag=1;
                break;
             }
        }
        freeQueue(&q);
        if(flag==0){
            break;
        } else flag=0;
    }
    /*---------------COUNTING FINISHED------------------*/

    /*-------------PUBLISHING DOT FILE -----------------*/

    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;
    int pieceNum = 0;
    fprintf(fout, "graph %s { \n", graph->name);

    while(pieceNum<pieces){
        for (int i=0; i<graph->vc ; i++){
            isolation = 1;
            if(checkNodeInPiece(ptr[pieceNum], i)){
                for (int j=i; j<graph->vc ; j++){
                    if(graph->AM[i][j]==1){ // if j is connected to i : means j is also in that piece
                        fprintf(fout, "%d -- %d  %s;\n", i , j, colour[pieceNum%COLOR_NUM] );
                        isolation = 0;
                    }
                }
            }
            // IF A POINT IS ISOLATED
            if(isolation) { fprintf( fout , "%d\n", i); }
        }
        pieceNum++;
    }

    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);

    /*---------------PUBLISHED DOT FILE ----------------*/
    // print ptr
    for (int i=0; i<pieces; i++){
        printf("\nPiece: %d --> ", i+1);
        for (int j=0; ptr[i][j]!=-1; j++)
            printf("%d , ", ptr[i][j]);
        printf("\n");
    }

    for (int i=0; i<pieces; i++)
        free(ptr[i]);
    freeList(&visited);
    free(ptr);
    return pieces;
}


/*-----------------DATA STRUCTURES-------------------*/
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
        // printf("\nNode->data: %d  Data: %d\n", node->data , data);
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
