
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

int BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal){
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
        // if any adjacent neighbour is same as goal
        // for(int i=0; i<(*current)->adjNum; i++){
        //     if( ((*current)->adjacent[i]) == goal){
        //         displayLinkedList(&visited, (DISPLAY)displayNodeNumber);
        //         freeList(&visited);
        //         freeQueue(&q);
        //         return 1;
        //     }
        // }

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

    // print path
    if(flag){
        int bktrace = (*goal)->nodeNumber;
        printf("\n%d ", bktrace);
        while (bktrace != (*root)->nodeNumber) {
            if(bktrace==-1) break;
            bktrace = prev[bktrace];
            printf(" <-%d ", bktrace);
        }
    }
    return flag;
}


// int BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal){
//     _LINKED_LIST_ visited;
//     initializeList(&visited);
//     _QUEUE_ q;
//     initializeQueue(&q);
//     addHead(&visited , root);
//     enqueue(&q, root);
//     printf("Start Node: %d , Addr: %d\n", (*root)->nodeNumber , root );
//     printf("End Node: %d , Addr: %d\n", (*goal)->nodeNumber , goal );
//
//     while (!queueEmpty(&q)){
//         _GNODE_ **current = (_GNODE_ *) dequeue(&q);
//         printf("Current Node: %d , Addr: %d AdjNum: %d\n", (*current)->nodeNumber , current, (*current)->adjNum );
//
//         if(current==goal){
//             freeList(&visited);
//             freeQueue(&q);
//             return 1;
//         }
//
//         // if any adjacent neighbour is same as goal
//         for(int i=0; i<(*current)->adjNum; i++){
//             if( ((*current)->adjacent[i]) == goal){
//             freeList(&visited);
//             freeQueue(&q);
//             return 1;
//         }
//         }
//
//
//         for (int i=0; i<(*current)->adjNum; i++){
//             if(!searchList(&visited, (*current)->adjacent[i])){
//                 addHead(&visited , (*current)->adjacent[i]);
//                 enqueue(&q, (*current)->adjacent[i]);
//             }
//         }
//     }
//
//     freeList(&visited);
//     freeQueue(&q);
//     printf("Returning 0\n");
//     return 0;
// }

//
// char *getLine(void){
//     char *line;
//     int size;   /* how much space do I have in the line? */
//     int length; /* how many characters have i used ?*/
//     int c;
//     size = INITIAL_LINE_LENGTH;
//     line = malloc(size);
//     if(line == 0) {
//         /* malloc failed */
//         printf("getLine() : failed to allocate memory for the input.");
//         return 0;
//     }
//     length = 0;
//     while ((c = getchar()) != EOF && c != '\n') {
//         /* code */
//         if(length >= size-1){
//             /* need more space */
//             size*=2;
//             /* make length equal to new size*/
//             /* copy contents if necessary */
//             line = realloc(line , size);
//         }
//         line[length++] = c;
//     }
//     line[length] = '\0';
//     return line;
// }
