/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

// Note: Variable and function names are self-explanatory
// hence I have reduced amount of comments to save my time for the quiz

// Please type the Input file name correctly or else There will a segmentation fault

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"  // for personal use only -- contains function prototypes and structure definition
// graph.c : contains function definition of corresponding function prototypes

int main(){
    _GRAPH_ graph;  // declaring graph data structure
    char fileName[30];  // file name
    printf(" Please type the Input file name correctly or else There will a segmentation fault : ");
    
    scanf("%s", fileName);  // input the filename
    readGraphFromTxt(fileName, &graph);
    // read the text file and create the graph data structure in the backend
    // for more detail on this function please check in graph.c
    printGraph(&graph); // print the graph
    printAllGraphNodeNumber(&graph);    // print the node numbers with their address

    for (int i=0; i<graph.vc; i++)
        printf("\nAddr of Node %d : %d", graph.node[i]->nodeNumber ,  &graph.node[i] );

    // Traversal : just for cheking the BreadthFirstSearch
    // task 2 : this is task 2 : path finder
    int nodeNum1, nodeNum2, *Path;
    printf("\nEnter Start node Number: ");
    scanf(" %d" , &nodeNum1);
    printf("Enter the ending node Number: ");
    scanf(" %d" , &nodeNum2);

    if(nodeNum1<0 || graph.vc<=nodeNum1)
        puts("Invalid Start Node Number. ");
    else if(nodeNum2<0 || graph.vc<=nodeNum2)
        puts("Invalid End Node Number. ");
    else if((Path=BreadthFirstSearch(&graph , &graph.node[nodeNum2], &graph.node[nodeNum1])) !=NULL){
        puts("Nodes are connected.");
        size_t i=0;
        while(1){
            printf("\n%d ", Path[i]);
            if(Path[i]==nodeNum2)   break;
            i++;
        }
        int lengthOfShortestPath = i;
        printf("\nLength of shortest Path: %d\n", lengthOfShortestPath);
        // this function publish a file with desired path trace
        publishShortestPathGraph(&graph, Path, lengthOfShortestPath);
    } else puts("Not Connected.");

    // task 3 starts from here
    // counting the pieces of the graph
    puts("\nCounting Pieces...");

    // countPiecesAndPublish : returns the number of pieces in the graph and publishes the dot file with edges of different pieces with different color
    printf("Pieces: %d\n", countPiecesAndPublish(&graph));

    // at last deallocate all the memory
    puts("\n....Deallocating all reserved memory....\n");
    free(Path);
    freeGraph(&graph);
    return 0;
}
