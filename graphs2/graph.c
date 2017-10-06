
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
        // free each node
        if(graph->node[i]->data!=NULL)
            free(graph->node[i]->data);
            // free each adjacent node
        for (int k=0; k<graph->node[i]->adjNum+1; k++){
            if(graph->node[i]->adjacent[k]!=NULL)
                free(graph->node[i]->adjacent[k]);
        }
        free(graph->node[i]->adjacent);
        free(graph->node[i]);
    }
    free(graph->node);

    for(int i=0; i<graph->vc; i++)
        if(graph->AM[i]!=NULL) free(graph->AM[i]);
    free(graph->AM);
    free(graph->name);
    free(graph);
}

void createGraphFromAM(_GRAPH_ *graph) {
    graph->node = (_GNODE_ **)malloc(sizeof(_GNODE_) * graph->vc) ;
    for (int i=0; i<graph->vc ; i++){
        graph->node[i] = (_GNODE_ *)malloc(sizeof(_GNODE_));
        graph->node[i]->adjNum=0;
        graph->node[i]->adjacent = (_GNODE_ **)malloc(sizeof(_GNODE_)) ;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                graph->node[i]->adjNum++;
                graph->node[i]->adjacent = (_GNODE_ **)realloc( graph->node[i]->adjacent , sizeof(_GNODE_) * (graph->node[i]->adjNum+1));
                graph->node[i]->adjacent[graph->node[i]->adjNum-1] = graph->node[j];
            }
        }
        graph->node[i]->adjacent[graph->node[i]->adjNum] = NULL;
    }
}

// read a file for the Adjacency matrix and returns the number of vertices.
// the user is responsible to manually freeing the memory allocated by this function
// Holds all the data in a structural format
int readGraphFromTxt(char *filename , _GRAPH_ *graph){
    FILE *fp;
    fp = fopen(filename, "r");
    //int success;
    int vc;
    int **AM;
    char *gname;
    if(fp != NULL){
        char graphName[100];
        fgets(graphName, 100, fp );
        gname = (char *)malloc(sizeof(char)*(strlen(graphName)+1));
        strncpy(gname , graphName, strlen(graphName));

        fgets(graphName, 100, fp );
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
    fclose(fp);
    return vc;
}
/*
Breadth-First-Search(Graph, Root, Goal):

    create empty set Checked
    create empty queue Queue

    add Root to Checked
    Queue.enqueue(Root)

    while Queue is not empty {
        Current = Queue.dequeue()
        if Current.has(Goal) {
            return Current
        }
        for each Node that is adjacent to Current {
            if Node is not in Checked {
                Checked.add(Node)
                Queue.enqueue(Node)
            }
        }
    }

int BreadthFirstSearch(_GRAPH_ , )
*/
