/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

// LABTEST
// 1 ==> red
// 2 ==> green
// 3 ==> blue

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
    printGraph(&graph); // print the graph
    printAllGraphNodeNumber(&graph);    // print the node numbers with their address

	int x=0, y=0;
	printf("\nEnter the start node and end node respectively : ");
	scanf(" %d %d", &x, &y);


// 	Assigning all the levels from start node : x
	int *levels = (int*)malloc(sizeof(int) * graph.vc);
	int *shortB=NULL, lvl;

	for (int i=0; i<graph.vc ; i++){
		if(i==x) continue;
		else {
			lvl =0 ;
			shortB = BreadthFirstSearch(&graph , &graph.node[x] , &graph.node[i]);
			// finding the level of that node: i
			for (int i=0; shortB[i]!=graph.node[x]->nodeNumber; i++){
//				printf(" %d " , shortB[i]);
				lvl++;
			}
			levels[i] = lvl;
			// deallocating all the memory
			free(shortB);
			shortB = NULL;
		}
	}
	levels[x] = 0;
	// print all levels
	printf("\nLEVELS FOR ALL NODES: \n");
	for(int j=0; j<graph.vc ; j++){
		printf("NODE %d --- LEVEL %d \n" ,j,  levels[j]);
	}

	printf("\nLEVEL OF  y : %d\n" , levels[y]);
	// select a path which is shortest and has minimum number of blue
	int *shortBluePath = (int *)malloc(sizeof(int) * levels[y]);
	shortBluePath[0] = y;
	int flag=0 , t=0, numBlue=0;
	for (int j=levels[y]; j>0; j--){
		flag=0;
		for(int i=0; i<graph.vc ; i++){
			if((graph.AM[shortBluePath[levels[y]-j]][i]!=3 || graph.AM[i][shortBluePath[levels[y]-j]]!=3) && levels[i]==(j-1)){
				flag=1;
				t = i;
				break;
			}
			t = i;
		}
		if(!flag) numBlue++;
		shortBluePath[levels[y]-j+1] = t;
	}

	// print final path
	printf("Final Path: ");
	for(int i=0; i<levels[y] ; i++){
		printf(" %d ", shortBluePath[i]);
	}
    printf(" %d\n" , x);

	free(shortBluePath);
	printf("\n");
	printf("Number of Blue Edges : %d ", numBlue);
	puts("\n....Deallocating all reserved memory....\n");
	freeGraph(&graph);
	free(shortB);
    return 0;
}
