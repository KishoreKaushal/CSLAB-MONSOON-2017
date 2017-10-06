#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"
#include "dataStructures.h"

int main(){
    _GRAPH_ graph;
    char fileName[30];
    scanf("%s\n", fileName);
    readGraphFromTxt(fileName, &graph);
    printAllGraphNodeNumber(&graph);
    freeGraph(&graph);
    return 0;
}
