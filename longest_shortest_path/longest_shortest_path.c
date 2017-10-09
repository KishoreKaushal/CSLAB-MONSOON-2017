/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

// Note: Variable and function names are self-explanatory
// hence I have reduced amount of comments to save my time for the quiz

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"  // for personal use only -- contains function prototypes and structure definition
// graph.c : contains function definition of corresponding function prototypes

int main(){
    _GRAPH_ graph;  // declaring graph data structure
    char fileName[30];  // file name
    scanf("%s", fileName);  // input the filename
    readGraphFromTxt(fileName, &graph);
    // read the text file and create the graph data structure in the backend
    // for more detail on this function please check in graph.c
    printGraph(&graph); // print the graph
    printAllGraphNodeNumber(&graph);    // print the node numbers with their address

    for (int i=0; i<graph.vc; i++)
        printf("\nAddr of Node %d : %d", graph.node[i]->nodeNumber ,  &graph.node[i] );

    int  *Path;

    // task 4 starts here
    int *nodeLongestShortestPath = findLongestShortestPath(&graph);
    printf("Longest Shortest Path Between Node %d and Node %d \n", nodeLongestShortestPath[0], nodeLongestShortestPath[1]);

    printf("Tracing the longest shortest Path on the graph....\n");

    if((Path=BreadthFirstSearch(&graph , &graph.node[nodeLongestShortestPath[0]], &graph.node[nodeLongestShortestPath[1]])) !=NULL){
        puts("Nodes are connected.");
        int lengthOfShortestPath = shortestPathLength(Path, nodeLongestShortestPath[0]);
        printf("\nLength of Longest Shortest Path: %d\n", lengthOfShortestPath);
        // this function publish a file with desired path trace
        publishShortestPathGraph(&graph, Path, lengthOfShortestPath);
    }

    // at last deallocate all the memory
    puts("\n....Deallocating all reserved memory....\n");
    free(nodeLongestShortestPath) ;
    free(Path);
    freeGraph(&graph);
    return 0;
}
