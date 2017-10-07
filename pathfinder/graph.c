
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"
#include "dataStructures.h"

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
    printf("%d ", (*node)->nodeNumber);
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
        // print queue in each step
        printf("queue : ");
        displayQueue(&q, (DISPLAY)displayNodeNumber);
        _GNODE_ **current = (_GNODE_ *) dequeue(&q);
        printf("Current Node: %d , Addr: %d AdjNum: %d\n", (*current)->nodeNumber , current, (*current)->adjNum );
        if(current==goal){
            displayLinkedList(&visited, (DISPLAY)displayNodeNumber);
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

    displayLinkedList(&visited, (DISPLAY)displayNodeNumber);
    freeList(&visited);
    freeQueue(&q);

    int *shortestPath = NULL;
    int cnt=0;
    // print path
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
    char name[100];
    int isolation=0;
    strcpy(name , graph->name );
    strcat(name , ".dot");

    FILE *fp = fopen( name , "w+");
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
    for (size_t i=1; i<pathLength+1; i++ ){
        if(shortestPath[i-1]==vertex1 && shortestPath[i]==vertex2)
            return 1;
    }
    for (size_t i=1; i<pathLength+1; i++){
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
}
