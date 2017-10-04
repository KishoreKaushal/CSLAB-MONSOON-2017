#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// structure of the graph
typedef struct _GRAPH_ {
    int vc;
    char *name;
    int **AM;
} _GRAPH_ ;

// initializeGraph
void initializeGraph(_GRAPH_ *graph) {
    graph->vc = 0;
    graph->name = NULL;
    graph->AM = NULL;
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
    graph->AM = AM;
    graph->name = gname;
    graph->vc = vc;
    fclose(fp);
    return vc;
}
