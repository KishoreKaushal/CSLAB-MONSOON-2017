#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataStructures.h"

#ifndef GRAPH_H
#define GRAPH_H


// structure of the graph using adjacency matrix
typedef struct _GNODE_ {
    int nodeNumber;             // vertex/node number
    int adjNum;                 // number of adjacent nodes
    struct _GNODE_ ***adjacent;  // array of pointers to adjacent nodes
} _GNODE_ ;

typedef struct _GRAPH_ {
    int vc;         // number of vertices
    char *name;     // graph name
    int **AM;       // adjacency matrix
    _GNODE_ **node; // array of pointer to each vertices
} _GRAPH_ ;

#define NAME_LENGTH (2)
#define INITIAL_LINE_LENGTH (2)

char *getLine(void);

typedef struct String {
    char *str;
} String;

// deallocating memory allocated for the graph
void freeGraph(_GRAPH_ *graph);

void initializeGraph(_GRAPH_ *graph);
void createGraphFromAM(_GRAPH_ *graph);
int readGraphFromTxt(char *filename , _GRAPH_ *graph);
void printGraph(_GRAPH_ *graph);
int hasGnode(_GNODE_ *current , _GNODE_ *goal);
int * BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal);
static void displayNodeNumber(_GNODE_ **node);
void makeDotFile(_GRAPH_ *graph);
void publishShortestPathGraph( _GRAPH_ * graph ,int *shortestPath, int pathLength);
int checkEdgeInPath(int *shortestPath , int pathLength , int vertex1 , int vertex2);

#endif // GRAPH_H
