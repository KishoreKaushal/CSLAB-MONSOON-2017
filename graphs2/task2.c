#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataStructures.h"
#include "graph.h"


int main(){
    _GRAPH_ graph;
    char fileName[30];
    scanf("%s", fileName);
    readGraphFromTxt(fileName, &graph);
    printGraph(&graph);
    printAllGraphNodeNumber(&graph);

    for (int i=0; i<graph.vc; i++)
        printf("\nAddr of Node %d : %d", graph.node[i]->nodeNumber ,  &graph.node[i] );

    int nodeNum1, nodeNum2;
    printf("\nEnter Start node Number: ");
    scanf(" %d" , &nodeNum1);
    printf("Enter the ending node Number: ");
    scanf(" %d" , &nodeNum2);

    if(nodeNum1<0 || graph.vc<=nodeNum1)
        puts("Invalid Start Node Number. ");
    else if(nodeNum2<0 || graph.vc<=nodeNum2)
        puts("Invalid End Node Number. ");
    else if(BreadthFirstSearch(&graph , &graph.node[nodeNum1], &graph.node[nodeNum2])){
        puts("Nodes are connected.");
        //String *shortestPath = printShortestPathUsingBFS(&graph , &graph.node[nodeNum1], &graph.node[nodeNum2]));
    } else puts("Not Connected.");

    freeGraph(&graph);
    return 0;
}
