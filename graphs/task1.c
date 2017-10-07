// KAUSHAL KISHORE
// GRAPHS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

// making a dot file
void makeDotFile(_GRAPH_ *graph) {
    char name[100];
    int isolation=0;
    strcpy(name , graph->name );
    strcat(name , ".dot");

    FILE *fp = fopen( name , "w+");
    fprintf(fp, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                fprintf(fp, "%d -- %d\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fp , "%d\n", i); }
    }
    fprintf(fp , "\n}" );
    fclose(fp);
}

// to print adjacency matrix
void print2D(int **arr , int r, int c){
    for (int i =0 ; i < r; i++){
        for (int j=0; j<c;  j++)
            printf("%d\t" , arr[i][j]);
        printf("\n");
    }
}

// this function will print the graph
void printGraph(_GRAPH_ *graph){
    printf("\nGRAPH NAME : %s" , graph->name);
    printf("VERTICES : %d\n" , graph->vc);
    print2D(graph->AM , graph->vc , graph->vc);
}


int main(){
    char fname[40];
    _GRAPH_ graph;
    printf("Name of File: ");
    scanf("%[^\n]s" , fname);

    // initializing a graph
    initializeGraph(&graph);
    // read graph from the text file
    readGraphFromTxt(fname, &graph);
    // print the graph on the screen
    printGraph(&graph);

    // making the dot file
    makeDotFile(&graph);
    // freeing the memory allocated

    // free all the memory
    for(int i=0; i<graph.vc; i++)
        if(graph.AM[i]!=NULL) free(graph.AM[i]);
    free(graph.AM);
    free(graph.name);
    return 0;
}
