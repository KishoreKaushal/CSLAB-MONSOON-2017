/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

// Eulerian Circuit

// Note: Variable and function names are self-explanatory
// hence I have reduced amount of comments to save my time for the quiz

// Please type the Input file name correctly or else There will a segmentation fault
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"  // for personal use only -- contains function prototypes and structure definition
// graph.c : contains function definition of corresponding function prototypes

void printInt(int *ptr){
    printf(" --> %d ", *ptr);
}

int compareInt(int *a, int *b){
    return (*a==*b);
}

int main(){
    _GRAPH_ graph;  // declaring graph data structure
    char fileName[30];  // file name
    printf(" Please type the Input file name correctly or else There will a segmentation fault : ");
    scanf("%s", fileName);  // input the filename
    if(!readGraphFromTxt(fileName, &graph)){
        freeGraph(&graph);
        exit(0);
    }
    // read the text file and create the graph data structure in the backend
    // for more detail on this function please check in graph.c
    //printGraph(&graph); // print the graph
    //printAllGraphNodeNumber(&graph);    // print the node numbers with their address
    //printGraph(&graph); // print the graph
    //printAllGraphNodeNumber(&graph);    // print the node numbers with their address

    // for (int i=0; i<graph.vc; i++)
    //     printf("\nAddr of Node %d : %d", graph.node[i]->nodeNumber ,  &graph.node[i] );
    //
    // printf("\n\n");

    int x=0, y=0;
    printf("Enter the nodes X and Y : ");
    scanf(" %d %d", &x , &y);
    int *path = dijkstra(&graph, &graph.node[y], &graph.node[x]);
    printf("The shortest Path Between them: ");
    for(int i=0; path[i]!=y; i++){
        printf("%d ", path[i] );
        for(int j=0; j<graph.AM[path[i]][path[i+1]] ; j++){
            printf("-");
        }
        printf("> ");
    }
    printf("%d ", y);
    publishShortestPathInWeightedGraph(&graph, path);
    // deallocating all the memory
    puts("\n\n....Deallocating all reserved memory....\n");
    free(path);
    freeGraph(&graph);
    return 0;
}
