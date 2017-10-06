#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataStructures.h"

#ifndef GRAPH_H
#define GRAPH_H


// structure of the graph using adjacency matrix
typedef struct _GNODE_ {
    int nodeNumber;
    void *data;
    int adjNum;
    struct _GNODE_ **adjacent;
} _GNODE_ ;

typedef struct _GRAPH_ {
    int vc;
    char *name;
    int **AM;
    _GNODE_ **node;
} _GRAPH_ ;

// deallocating memory allocated for the graph
void deleteGraph(_GRAPH_ *graph);

void initializeGraph(_GRAPH_ *graph);
void createGraphFromAM(_GRAPH_ *graph);
int readGraphFromTxt(char *filename , _GRAPH_ *graph);


#endif // GRAPH_H
