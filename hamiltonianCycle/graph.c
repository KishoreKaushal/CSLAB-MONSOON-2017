
/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"
<<<<<<< HEAD

=======
#include"graph.h"
>>>>>>> master

char *colour[] = {
    "color=red",
    "color=blue",
    "color=green",
    "color=cyan",
    "color=yellow",
    "color=black",
};


// initializeGraph
void initializeGraph(_GRAPH_ *graph) {
    graph->vc = 0;
    graph->name = NULL;
    graph->AM = NULL;
    graph->node = NULL;
}

void freeGraph(_GRAPH_ *graph){
    // free graph
    for (int i=0; i<graph->vc; i++) {
        // free each node data
    //    printf("\nFreeing Node : %d\n", i);
        if(graph->node[i]->adjacent!=NULL) {
            free(graph->node[i]->adjacent);
        }
        free(graph->node[i]);
    }
    free(graph->node);
    for(int i=0; i<graph->vc; i++)
        if(graph->AM[i]!=NULL) free(graph->AM[i]);
    free(graph->AM);
    free(graph->name);
}

void createGraphFromAM(_GRAPH_ *graph) {
    graph->node = (_GNODE_ **)malloc(sizeof(_GNODE_) * graph->vc) ; // array of pointers to different nodes

    for (int i=0; i<graph->vc ; i++){
        graph->node[i] = (_GNODE_ *)malloc(sizeof(_GNODE_));
        graph->node[i]->adjNum=0;
        graph->node[i]->nodeNumber = i;     // node number
        graph->node[i]->adjacent = (_GNODE_ ***)malloc(sizeof(_GNODE_)) ; // because allocating 0 byte is tricky
    }

    for (int i=0; i<graph->vc ; i++){
        for (int j=0; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){     // check for adjacency between i and j
                graph->node[i]->adjNum++;   // if adjacent increment number of adjacent nodes number
                graph->node[i]->adjacent = (_GNODE_ ***)realloc( graph->node[i]->adjacent , sizeof(_GNODE_) * (graph->node[i]->adjNum+1));   // reallocate the memory to hold new adjacent member
                graph->node[i]->adjacent[graph->node[i]->adjNum-1] = &graph->node[j];    // points to another node
            }
        }
        graph->node[i]->adjacent[graph->node[i]->adjNum] = NULL; // set last adjacent node to NULL
    }
}

// read a file for the Adjacency matrix and returns the number of vertices.
// the user is responsible to manually freeing the memory allocated by this function
// Holds all the data in a structural format
int readGraphFromTxt(char *filename , _GRAPH_ *graph){
    FILE *fp;
    fp = fopen(filename, "r");
    int vc;
    int **AM;
    char *gname;
    if(fp != NULL){
        char graphName[100];
        fgets(graphName, 99, fp );
        gname = (char *)malloc(sizeof(char)*101);
        strncpy(gname , graphName, 99);
        fgets(graphName, 99, fp );
        fscanf(fp , "%d\n" , &vc);
        AM = (int **) malloc(sizeof(int*) * vc);
        for(int i=0; i<vc; i++){
            AM[i] = (int *)malloc(sizeof(int) * vc);
            if(fscanf(fp, "%s" , graphName) ==EOF)    break;
            for(int j=0; j<vc; j++){
                AM[i][j] = graphName[j] - '0';
            }
        }

        if(AM != NULL) graph->AM = AM;
        if(gname != NULL )  graph->name = gname;
        graph->vc = vc;
        createGraphFromAM(graph);
        fclose(fp);
        return vc;
    }
    return 0;
}


void print2Dint( int **arr, size_t rows , size_t cols){
    printf("\n");
    for (size_t i=0; i<rows; i++){
        for (size_t j =0; j<cols ; j++){
            printf("%d\t" , arr[i][j]);
        }
        printf("\n");
    }
}


void printGraph(_GRAPH_ *graph){
    printf("\nGRAPH NAME : %s" , graph->name);
    printf("VERTICES : %d\n" , graph->vc);
    print2Dint(graph->AM , graph->vc , graph->vc);
}

void printAllGraphNodeNumber(const _GRAPH_ *graph) {
    printf("NODES IN THE GRAPH: ");
    for (int i=0; i<graph->vc ; i++) {
        printf("\nNode Number : %d\n|----->  Adjacent Nodes \t\tAddr. Of Node\t\t\tAddr. Of NodeNumber",graph->node[i]->nodeNumber);
        for (int j=0; j<graph->node[i]->adjNum; j++){
            printf("\n|----->  %d \t\t\t\t%d\t\t\t%d, ", (*graph->node[i]->adjacent[j])->nodeNumber , graph->node[i]->adjacent[j] , &graph->node[i]->adjacent[j]);
        }
    }
}

static void displayNodeNumber(_GNODE_ **node){
    printf("%d ", node);
}

<<<<<<< HEAD

=======
>>>>>>> master
int * BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal){
    _LINKED_LIST_ visited;
    initializeList(&visited);
    _QUEUE_ q;
    initializeQueue(&q);
    int flag=0;
    int *prev = (int *)malloc(sizeof(int) * graph->vc);
    for (int i=0; i<graph->vc ; i++){
        prev[i] = -1;
    }
    addHead(&visited , root);
    enqueue(&q, root);
    //printf("Start Node: %d , Addr: %d\n", (*root)->nodeNumber , root );
    //printf("End Node: %d , Addr: %d\n", (*goal)->nodeNumber , goal );
    while (!queueEmpty(&q)){
        _GNODE_ **current = (_GNODE_ *) dequeue(&q);
        if(current==goal){
            freeList(&visited);
            freeQueue(&q);
            flag =1;
            break;
        }
        for (int i=0; i<(*current)->adjNum; i++){
            if(!searchList(&visited, (*current)->adjacent[i])){
                prev[ (*(*current)->adjacent[i])->nodeNumber ] = (*current)->nodeNumber;
                addHead(&visited , (*current)->adjacent[i]);
                enqueue(&q, (*current)->adjacent[i]);
            }
        }
    }
    freeList(&visited);
    freeQueue(&q);
    int *shortestPath = NULL;
    int cnt=0;
    if(flag){
        shortestPath = (int *)malloc(sizeof(int));
        int bktrace = (*goal)->nodeNumber;
        printf("\n%d ", bktrace);
        shortestPath[cnt++] = bktrace;
        while (bktrace != (*root)->nodeNumber) {
            bktrace = prev[bktrace];
            shortestPath = (int*)realloc(shortestPath , sizeof(int) * (cnt+1) );
            shortestPath[cnt++] = bktrace;
            if(bktrace==-1) break;
            printf("-->%d ", bktrace);
        }
    }
    free(prev);
    return shortestPath;
}

// making a dot file
void makeDotFile(_GRAPH_ *graph) {
    char outFileName[30];
    int isolation=0;
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fp = fopen( outFileName , "w+");
    fprintf(fp, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                fprintf(fp, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fp , "%d\n", i); }
    }
    fprintf(fp , "\n}" );
    fclose(fp);
}

int checkEdgeInPath(int *shortestPath , int pathLength , int vertex1 , int vertex2 ){
    for (size_t i=1; shortestPath[i]!=-1 && i<pathLength+1; i++ ){
        if(shortestPath[i-1]==vertex1 && shortestPath[i]==vertex2)
            return 1;
    }
    for (size_t i=1; shortestPath[i]!=-1 && i<pathLength+1; i++){
        if(shortestPath[i-1]==vertex2 && shortestPath[i]==vertex1)
            return 1;
    }
    return 0;
}

<<<<<<< HEAD
=======
void publishHamiltonianPathGraph( _GRAPH_ * graph ,int *shortestPath, int pathLength){
    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;
    fprintf(fout, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                if(checkEdgeInPath(shortestPath, pathLength, i ,j))
                    fprintf(fout, "%d -- %d  ;\n", i , j);
                else fprintf(fout, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fout , "%d\n", i); }
    }
    for (int i=1; i<pathLength ; i++){
        fprintf(fout, "%d -- %d  [color=red];\n", shortestPath[i-1] , shortestPath[i]);
    }

    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);
}


>>>>>>> master

void publishShortestPathGraph( _GRAPH_ * graph ,int *shortestPath, int pathLength){
    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;
    fprintf(fout, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                if(checkEdgeInPath(shortestPath, pathLength, i ,j))
                    fprintf(fout, "%d -- %d  [color=red];\n", i , j);
                else fprintf(fout, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        if(isolation) { fprintf( fout , "%d\n", i); }
    }
    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);
}


int checkNodeInPiece(int *pieceArr , int nodeNum){
    int *ptr = &pieceArr[0];
    while (ptr && (*ptr)!=-1){
        if((*ptr)==nodeNum)
            return 1;
        ptr++;
    }
    return 0;
}

int countPiecesAndPublish(_GRAPH_ * graph){
    int pieces = 0, ptrIdx;
    if(graph->vc>0) pieces++;
    int **ptr = (int **)malloc(sizeof(int ) * pieces);
    int flag=0;
    /*------BFS (modified) --- COUNTING PIECES------*/
    int iter=0;
    _GNODE_ **root = &graph->node[iter];
    _LINKED_LIST_ visited;
    _QUEUE_ q;
    initializeList(&visited);

    while(pieces&&iter<graph->vc){
        ptrIdx =0;
        initializeQueue(&q);
        root = &graph->node[iter];
        addHead(&visited , root);
        ptr[pieces-1] = (int *)malloc(sizeof(int *) * (ptrIdx+2));
        ptr[pieces-1][ptrIdx++] = (*root)->nodeNumber;
        enqueue(&q, root);
        while (!queueEmpty(&q)){
            _GNODE_ **current = (_GNODE_ *) dequeue(&q);
            for (int i=0; i<(*current)->adjNum; i++){
                if(!searchList(&visited, (*current)->adjacent[i])){

                    ptr[pieces-1] = (int *)realloc( ptr[pieces-1] , sizeof(int)*(ptrIdx+2));
                    ptr[pieces-1][ptrIdx++] =  (*(*current)->adjacent[i])->nodeNumber;

                    addHead(&visited , (*current)->adjacent[i]);
                    enqueue(&q, (*current)->adjacent[i]);
                }
            }
        }
        ptr[pieces-1][ptrIdx] = -1;
        // check for unvisited nodes
        for(int i=0; i<graph->vc; i++){
            if(!searchList(&visited, &graph->node[i])){
                iter =  i;
                pieces++;
                ptr = (int **)realloc( ptr , sizeof(int ) * pieces);
                flag=1;
                break;
             }
        }
        freeQueue(&q);
        if(flag==0){
            break;
        } else flag=0;
    }
    /*---------------COUNTING FINISHED------------------*/

    /*-------------PUBLISHING DOT FILE -----------------*/

    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;
    int pieceNum = 0;
    fprintf(fout, "graph %s { \n", graph->name);

    while(pieceNum<pieces){
        for (int i=0; i<graph->vc ; i++){
            isolation = 1;
            if(checkNodeInPiece(ptr[pieceNum], i)){
                for (int j=i; j<graph->vc ; j++){
                    if(graph->AM[i][j]==1){ // if j is connected to i : means j is also in that piece
                        fprintf(fout, "%d -- %d  [%s];\n", i , j, colour[pieceNum%COLOR_NUM] );
                        isolation = 0;
                    }
                }
            }
            // IF A POINT IS ISOLATED
            if(isolation) { fprintf( fout , "%d\n", i); }
        }
        pieceNum++;
    }

    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);

    /*---------------PUBLISHED DOT FILE ----------------*/
    // print ptr
    for (int i=0; i<pieces; i++){
        printf("\nPiece: %d --> ", i+1);
        for (int j=0; ptr[i][j]!=-1; j++)
            printf("%d , ", ptr[i][j]);
        printf("\n");
    }

    for (int i=0; i<pieces; i++)
        free(ptr[i]);
    freeList(&visited);
    free(ptr);
    return pieces;
}

int shortestPathLength(int *Path, int endNode) {
    if(Path!=NULL) {
        int i=0;
        while(1){
            //printf("\n%d ", Path[i]);
            if(Path[i]==endNode)   break;
            i++;
        }
        return i;
    }
    return 0;
}

int * findLongestShortestPath(_GRAPH_ * graph) {
    int LongestShortestPath = 0;
    int currentPathLength = 0;
    int *node = (int *)malloc(sizeof(int )*2);
    node[0] = 0 ; node[1] = 0;
    int *Path;
    for (int i=0; i < graph->vc ; i++ ){
        for (int j=0; j<graph->vc ; j++ ){
            Path = BreadthFirstSearch(graph , &graph->node[i], &graph->node[j]);
            currentPathLength = shortestPathLength(Path, i);
            if(currentPathLength > LongestShortestPath){
                // longest shortest Path between node i and node j
                printf("Path Length Between %d and %d : %d\n",i,j, currentPathLength);
                node[0] = i;
                node[1] = j;
                LongestShortestPath = currentPathLength;
            }
            free(Path);
            Path=NULL;
        }
    }
    if(Path!=NULL) free(Path);
    return node;
}

int existEulerianCircuit(_GRAPH_ *graph){
    for (int i=0; i<graph->vc; i++) {
        if(graph->node[i]->adjNum %2 !=0){
            return 0;
        }
    }
    return 1;
}

void markEdgeLeft(int **edgeLeft, int edgeIdx, int vertex1, int vertex2) {
    for (int i=0; i<edgeIdx ; i++) {
        if((edgeLeft[0][i]==vertex1 && edgeLeft[1][i] == vertex2) ||(edgeLeft[0][i]==vertex2 && edgeLeft[1][i] == vertex1)){
            edgeLeft[0][i] = -1 ; edgeLeft[1][i] = -1;
        }
    }
}

int findNextIdx(int **edgeLeft, int edgeIdx, int cVertex) {
    for(int i=0; i<edgeIdx; i++ ){
        if(edgeLeft[0][i] == cVertex)
            return i;
    }
    return -1;
}

<<<<<<< HEAD
/* A utility function to check if the vertex v can be added at
   index 'pos' in the Hamiltonian Cycle constructed so far (stored
   in 'path[]') */
int isSafe(int v, _GRAPH_ * graph, int path[], int pos){
    /* Check if this vertex is an adjacent vertex of the previously
       added vertex. */
    if (graph->AM[ path[pos-1] ][ v ] == 0)
        return 0;

    /* Check if the vertex has already been included.
      This step can be optimized by creating an array of size V */
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

/* A recursive utility function to solve hamiltonian cycle problem */
int hamCycleUtil(_GRAPH_ *graph, int path[], int pos)
{
    /* base case: If all vertices are included in Hamiltonian Cycle */
    if (pos == graph->vc)
    {
        // And if there is an edge from the last included vertex to the
        // first vertex
        if ( graph->AM[ path[pos-1] ][ path[0] ] == 1 )
           return 1;
        else
          return 0;
    }

    // Try different vertices as a next candidate in Hamiltonian Cycle.
    // We don't try for 0 as we included 0 as starting point in in hamCycle()
    for (int v = 1; v < graph->vc; v++)
    {
        /* Check if this vertex can be added to Hamiltonian Cycle */
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;

            /* recur to construct rest of the path */
            if (hamCycleUtil (graph, path, pos+1) == 1)
                return 1;

            /* If adding vertex v doesn't lead to a solution,
               then remove it */
            path[pos] = -1;
        }
    }

    /* If no vertex can be added to Hamiltonian Cycle constructed so far,
       then return false */
    return 0;
}

void printSolution(int path[], int V)
{
    printf ("Solution Exists:"
            " Following is one Hamiltonian Cycle \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", path[i]);

    // Let us print the first vertex again to show the complete cycle
    printf(" %d ", path[0]);
    printf("\n");
}

/* This function solves the Hamiltonian Cycle problem using Backtracking.
  It mainly uses hamCycleUtil() to solve the problem. It returns false
  if there is no Hamiltonian Cycle possible, otherwise return true and
  prints the path. Please note that there may be more than one solutions,
  this function prints one of the feasible solutions. */
int *hamCycle(_GRAPH_ * graph)
{
    int *path = (int *)malloc(sizeof(int)*graph->vc);
    for (int i = 0; i < graph->vc; i++)
        path[i] = -1;

    /* Let us put vertex 0 as the first vertex in the path. If there is
       a Hamiltonian Cycle, then the path can be started from any point
       of the cycle as the graph is undirected */
    path[0] = 0;
    if ( hamCycleUtil(graph, path, 1) == 0 )
    {
        printf("\nSolution does not exist");
        return NULL;
    }

    printSolution(path, graph->vc);
    path = (int *) realloc(path, sizeof(int)*(graph->vc+1));
    path[graph->vc] = path[0];
    return path;
}

// int * HamiltonianCycle(_GRAPH_ *graph){
//     int found=0;
//     int *visited = (int *)malloc(sizeof(int)* graph->vc);
//     for (int i=0; i<graph->vc ; i++) {
//         visited[i] = 0;
//     }
//     int *path = (int *)malloc(sizeof(int )*2);
//     path[0] = path[1] = 0;  // add node 0 to path
//     visited[0] = 1;
//
//     for (int i=1; i<graph->vc; i++) {
//         path = (int *) realloc(path, sizeof(int )*(i+2));
//         path[i+1]=0;
//         found = 0;
//         // find a vertex which is adjacent to previous vertex in path and has not been visited yet.
//         for (int j=1; j<graph->vc; j++) {
//             if(!visited[j] && (graph->AM[j][path[i-1]] || graph->AM[path[i-1]][j])) {
//                 path[i] = j;
//                 visited[j] = 1;
//                 found = 1;
//                 break;
//             }
//         }
//         printf("Loop %d: \n", i);
//         printIntArr(path, i+2);
//         printIntArr(visited, graph->vc);
//
//         // if no such vertex exist then return NULL
//         if(!found) {
//             free(path);
//             free(visited);
//             return NULL;
//         }
//     }
//     printIntArr(path, graph->vc+1);
//
//     // if final vertex in the path is not adjacent to the initial vertex then
//     // hamiltonian cycle doesn't exist and hence return NULL
//     if(!graph->AM[graph->vc -1][0]) {
//         free(path);
//         free(visited);
//         return NULL;
//     }
//     free(visited);
//     return path;
// }

=======
>>>>>>> master
int findEulerianCircuit(_GRAPH_ *graph , _CLINKED_LIST_ * eulerianPath) {
    _LINKED_LIST_ visited;
    initializeList(&visited);
    int edges = 0, edgeIdx=0;
    int **edgeLeft = (int **)malloc(sizeof(int )*(2));
    edgeLeft[0] = edgeLeft[1] = NULL;
    edgeLeft[0] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[1] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[0][0] = edgeLeft[1][0] = -1;
    for(int i=0; i<graph->vc ; i++) {
        for (int j=0; j<graph->node[i]->adjNum; j++){
            edges++;
            edgeLeft[0] = (int *)realloc( edgeLeft[0] , sizeof(int )*(edges+1));
            edgeLeft[1] = (int *)realloc( edgeLeft[1] , sizeof(int )*(edges+1));
            edgeLeft[0][edgeIdx] = i;
            edgeLeft[1][edgeIdx] = (*graph->node[i]->adjacent[j])->nodeNumber;
            edgeIdx++;
        }
    }
    edgeLeft[0][edgeIdx] = -1 ;
    edgeLeft[1][edgeIdx] = -1 ;
    printf("...Showing All Edges: ...\n");

    for (int i=0; i<edgeIdx; i++){
        printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    }
    // start from node 0
    int found=0, startIdx= 0 , nextIdx=0, eulerianCircuitPathLength=0;
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[0][startIdx];
    addCTail(eulerianPath , ptr);
    ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[1][startIdx];
    addCTail(eulerianPath , ptr);
    markEdgeLeft(edgeLeft, edgeIdx,edgeLeft[0][startIdx] ,edgeLeft[1][startIdx] );
    nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
    printf("NextIdx: %d\n", nextIdx);
    eulerianCircuitPathLength++;
/*
    printf("...Showing All Edges: ...\n");

    for (int i=0; i<edgeIdx; i++){
        printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    }
*/

    do {
        found=0;
        if(nextIdx == -1)   break;
        if((edgeLeft[0][nextIdx] != -1) && (edgeLeft[0][nextIdx] != -1)) {
            found = 1;
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[0][nextIdx];
            //addCTail(eulerianPath , ptr);
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[1][nextIdx];
            markEdgeLeft(edgeLeft, edgeIdx,edgeLeft[0][nextIdx] ,edgeLeft[1][nextIdx] );
            nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
            if(nextIdx!=-1) addCTail(eulerianPath , ptr);
            eulerianCircuitPathLength++;
        }
    } while (found);

    // free all allocated memory
    for (int i=0; i<2; i++)
        free(edgeLeft[i]);
    free(edgeLeft);
    freeList(&visited);
    return eulerianCircuitPathLength;
}

int publishOptimalColorPlanarGraph(_GRAPH_ *graph) {
    // little check to check whether the graph is planar or not
    for(int i=0; i<graph->vc ; i++) {
        if(graph->node[i]->adjNum > 5)  {
            puts("\nNode with degree more than 5 exists. Hence its not planar.");
            return 0;
        }
    }

    int *vertexColor = (int *)malloc(sizeof(int)*graph->vc);
    for (int i=0; i<graph->vc ; i++) {
        vertexColor[i] = -1;
    }
    int exist=0;
    _LINKED_LIST_ visited;
    initializeList(&visited);
    _QUEUE_ q;
    initializeQueue(&q);
    _GNODE_ **root = &graph->node[0];
    addHead(&visited , root);
    enqueue(&q, root);
    while (!queueEmpty(&q)){
        _GNODE_ **current = (_GNODE_ *) dequeue(&q);
        for (int i=0; i<(*current)->adjNum; i++){
            if(!searchList(&visited, (*current)->adjacent[i])){
                addHead(&visited , (*current)->adjacent[i]);
                enqueue(&q, (*current)->adjacent[i]);
            }
            for (int colorNum = 0; colorNum<6 ; colorNum++){
                exist = 0;
                for (int i=0; i<(*current)->adjNum; i++) {
                    if(colorNum == vertexColor[(*(*current)->adjacent[i])->nodeNumber]){
                        exist=1;
                        break;
                    }
                }
                if(!exist){
                    vertexColor[(*current)->nodeNumber] = colorNum;
                    break;
                }
            }
            if(exist == 1) {
                puts("\nSome problem with graph.. Probable reason: Non-Planar Graph.");
                freeQueue(&q);
                break;
            }
        }
    }
    freeList(&visited);
    freeQueue(&q);

    for (size_t i = 0; i < graph->vc; i++) {
        /* code */
        printf("\nNode Num %d Vertex color : %d\n", i,vertexColor[i]);
        if(vertexColor[i]==-1){
            puts("Not Able to vertex Color using 6 color ..");
            return 1;
        }
    }

    /*------------ PUBLISHING THE VERTEX COLORED GRAPH --------------- */
    char outFileName[30];
    printf("\nEnter the output \".dot\" file name (without any spaces) : ");
    scanf(" %s" , outFileName);
    FILE *fout = fopen(outFileName, "w+");
    int isolation=0;

    fprintf(fout, "graph %s { \n", graph->name);
    for (int i=0; i<graph->vc ; i++){
        isolation = 1;
        for (int j=i; j<graph->vc ; j++){
            if(graph->AM[i][j]==1){
                fprintf(fout, "%d -- %d ;\n", i , j);
                isolation = 0;
            }
        }
        // IF A POINT IS ISOLATED
        fprintf(fout, "%d [%s , style=filled]\n", i , colour[vertexColor[graph->node[i]->nodeNumber]]);
    }

    fprintf(fout , "\n}" );
    fclose(fout);
    char command[40] = "xdot ";
    strcat(command, outFileName);
    system(command);
}

<<<<<<< HEAD
=======
int notInVisited(int *visited , int visitIdx, int ele) {
    for (int i=0; i<visitIdx ; i++){
        if(ele == visited[i]) return 0;
    }
    return 1;
}

void markEdgeLeftHamiltonian(int **edgeLeft, int edgeIdx, int *visited , int visitIdx, int vertex1, int vertex2) {
    for (int i=0; i<edgeIdx ; i++) {
        if( (edgeLeft[0][i]==vertex1 || edgeLeft[1][i] == vertex1 || edgeLeft[0][i]==vertex1 || edgeLeft[1][i] == vertex1 ) && notInVisited(visited, visitIdx , vertex1) ){
            edgeLeft[0][i] = -1 ; edgeLeft[1][i] = -1;
        }
    }
}

int existHamiltonianCircuit(_GRAPH_ *graph){
    for (int i=0; i<graph->vc; i++) {
        if(graph->node[i]->adjNum < (graph->vc/2)){
            return 0;
        }
    }
    return 1;
}

int publishHamiltonianCycle(_GRAPH_ *graph, _CLINKED_LIST_ * hamiltonianPath) {
    if(!existHamiltonianCircuit(graph)) {
        printf("Hamiltonian path doesn't exists.\n");
        return 0;
    }
    _LINKED_LIST_ visited;
    initializeList(&visited);
    int edges = 0, edgeIdx=0;
    int **edgeLeft = (int **)malloc(sizeof(int )*(2));
    edgeLeft[0] = edgeLeft[1] = NULL;
    edgeLeft[0] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[1] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[0][0] = edgeLeft[1][0] = -1;
    for(int i=0; i<graph->vc ; i++) {
        for (int j=0; j<graph->node[i]->adjNum; j++){
            edges++;
            edgeLeft[0] = (int *)realloc( edgeLeft[0] , sizeof(int )*(edges+1));
            edgeLeft[1] = (int *)realloc( edgeLeft[1] , sizeof(int )*(edges+1));
            edgeLeft[0][edgeIdx] = i;
            edgeLeft[1][edgeIdx] = (*graph->node[i]->adjacent[j])->nodeNumber;
            edgeIdx++;
        }
    }
    edgeLeft[0][edgeIdx] = -1 ;
    edgeLeft[1][edgeIdx] = -1 ;
    printf("...Showing All Edges: ...\n");

    int *visited = (int *)malloc(graph->vc*sizeof(int));
    for (int i=0; i<edgeIdx; i++){
        printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    }
    // start from node 0
    int found=0, startIdx= 0 ,visitIdx=0, nextIdx=0, hamiltonianCircuitPathLength=0;

    int *ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[0][startIdx];
    visited[visitIdx++] = edgeLeft[0][nextIdx];
    addCTail(hamiltonianPath , ptr);
    ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[1][startIdx];
    addCTail(hamiltonianPath , ptr);
    markEdgeLeftHamiltonian(edgeLeft, edgeIdx,edgeLeft[0][startIdx] ,edgeLeft[1][startIdx] );
    nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
    printf("NextIdx: %d\n", nextIdx);
    hamiltonianCircuitPathLength++;

    do {
        found=0;
        if(nextIdx == -1)   break;
        if((edgeLeft[0][nextIdx] != -1) && (edgeLeft[0][nextIdx] != -1)) {
            found = 1;
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[0][nextIdx];
            visited[visitIdx++] = edgeLeft[0][nextIdx];
            //addCTail(eulerianPath , ptr);
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[1][nextIdx];
            printf("...Showing All Edges Left: ...\n Next Idx: %d , Current Node Number: %d" , nextIdx ,  edgeLeft[0][nextIdx]);
            markEdgeLeftHamiltonian(edgeLeft, edgeIdx, visited , visitIdx , geLeft[0][nextIdx] ,edgeLeft[1][nextIdx] );
            nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
            if(nextIdx!=-1) addCTail(hamiltonianPath , ptr);
            hamiltonianCircuitPathLength++;
        }
        for (int i=0; i<edgeIdx; i++){
            if(edgeLeft[0][i]!=-1)printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
        }
    } while (found);
    //
    // printf("...Showing All Edges: ...\n");
    //
    // for (int i=0; i<edgeIdx; i++){
    //     printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    // }


    /*------------------PUBLISH THE HAMILTIONIAN PATH---------------------*/
    //printf("Hamiltonian Path: \n");
    int *hPath = (int*)malloc(sizeof(int)*(hamiltonianCircuitPathLength+1)) ;
    _CNODE_ *cnode = hamiltonianPath->head;
    for(int i=0; i<hamiltonianCircuitPathLength+1 ; i++){
        hPath[i] = *((int *)(cnode->data));
    //    printf(" %d ", hPath[i]);
        cnode = cnode->next;
    }

    //
    // printf("%s\n", "Clist: -head-TO-tail-" );
    // if(cnode!=NULL){
    //     display(cnode->data);
    //     cnode = cnode->next;
    //     while(cnode != hamiltonianPath->tail){
    //         display(cnode->data);
    //         cnode = cnode->next;
    //     }
    //     display(cnode->data);
    // }
    // display(hamiltonianPath->head->data);

    publishHamiltonianPathGraph(graph , hPath , hamiltonianCircuitPathLength+1);

    /*--------------------------------------------------------------------*/

    // free all allocated memory
    for (int i=0; i<2; i++)
        free(edgeLeft[i]);
    free(edgeLeft);
    freeList(&visited);
    return hamiltonianCircuitPathLength;
}






int printHPath(_GRAPH_ *graph, _CLINKED_LIST_ * hamiltonianPath) {
    if(!existHamiltonianCircuit(graph)) {
        printf("Hamiltonian path doesn't exists.\n");
        return 0;
    }
    _LINKED_LIST_ visited;
    initializeList(&visited);
    int edges = 0, edgeIdx=0;
    int **edgeLeft = (int **)malloc(sizeof(int )*(2));
    edgeLeft[0] = edgeLeft[1] = NULL;
    edgeLeft[0] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[1] = (int *)malloc(sizeof(int)*(edges+1));
    edgeLeft[0][0] = edgeLeft[1][0] = -1;
    for(int i=0; i<graph->vc ; i++) {
        for (int j=0; j<graph->node[i]->adjNum; j++){
            edges++;
            edgeLeft[0] = (int *)realloc( edgeLeft[0] , sizeof(int )*(edges+1));
            edgeLeft[1] = (int *)realloc( edgeLeft[1] , sizeof(int )*(edges+1));
            edgeLeft[0][edgeIdx] = i;
            edgeLeft[1][edgeIdx] = (*graph->node[i]->adjacent[j])->nodeNumber;
            edgeIdx++;
        }
    }
    edgeLeft[0][edgeIdx] = -1 ;
    edgeLeft[1][edgeIdx] = -1 ;
    printf("...Showing All Edges: ...\n");

    int *visited = (int *)malloc(graph->vc*sizeof(int));
    for (int i=0; i<edgeIdx; i++){
        printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    }
    // start from node 0
    int found=0, startIdx= 0 ,visitIdx=0, nextIdx=0, hamiltonianCircuitPathLength=0;

    int *ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[0][startIdx];
    visited[visitIdx++] = edgeLeft[0][nextIdx];
    addCTail(hamiltonianPath , ptr);
    ptr = (int *)malloc(sizeof(int));
    *ptr = edgeLeft[1][startIdx];
    addCTail(hamiltonianPath , ptr);
    markEdgeLeftHamiltonian(edgeLeft, edgeIdx,edgeLeft[0][startIdx] ,edgeLeft[1][startIdx] );
    nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
    printf("NextIdx: %d\n", nextIdx);
    hamiltonianCircuitPathLength++;

    do {
        found=0;
        if(nextIdx == -1)   break;
        if((edgeLeft[0][nextIdx] != -1) && (edgeLeft[0][nextIdx] != -1)) {
            found = 1;
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[0][nextIdx];
            visited[visitIdx++] = edgeLeft[0][nextIdx];
            //addCTail(eulerianPath , ptr);
            ptr = (int *)malloc(sizeof(int));
            *ptr = edgeLeft[1][nextIdx];
            printf("...Showing All Edges Left: ...\n Next Idx: %d , Current Node Number: %d" , nextIdx ,  edgeLeft[0][nextIdx]);
            markEdgeLeftHamiltonian(edgeLeft, edgeIdx, visited , visitIdx , geLeft[0][nextIdx] ,edgeLeft[1][nextIdx] );
            nextIdx =findNextIdx(edgeLeft, edgeIdx, *ptr);
            if(nextIdx!=-1) addCTail(hamiltonianPath , ptr);
            hamiltonianCircuitPathLength++;
        }
        for (int i=0; i<edgeIdx; i++){
            if(edgeLeft[0][i]!=-1)printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
        }
    } while (found);
    //
    // printf("...Showing All Edges: ...\n");
    //
    // for (int i=0; i<edgeIdx; i++){
    //     printf("\t(%d , %d)\n",edgeLeft[0][i] , edgeLeft[1][i] );
    // }


    /*------------------PUBLISH THE HAMILTIONIAN PATH---------------------*/
    //printf("Hamiltonian Path: \n");
    int *hPath = (int*)malloc(sizeof(int)*(hamiltonianCircuitPathLength+1)) ;
    _CNODE_ *cnode = hamiltonianPath->head;
    for(int i=0; i<hamiltonianCircuitPathLength+1 ; i++){
        hPath[i] = *((int *)(cnode->data));
    //    printf(" %d ", hPath[i]);
        cnode = cnode->next;
    }

    //
    // printf("%s\n", "Clist: -head-TO-tail-" );
    // if(cnode!=NULL){
    //     display(cnode->data);
    //     cnode = cnode->next;
    //     while(cnode != hamiltonianPath->tail){
    //         display(cnode->data);
    //         cnode = cnode->next;
    //     }
    //     display(cnode->data);
    // }
    // display(hamiltonianPath->head->data);

    publishHamiltonianPathGraph(graph , hPath , hamiltonianCircuitPathLength+1);

    /*--------------------------------------------------------------------*/

    // free all allocated memory
    for (int i=0; i<2; i++)
        free(edgeLeft[i]);
    free(edgeLeft);
    freeList(&visited);
    return hamiltonianCircuitPathLength;
}









>>>>>>> master

/*-----------------DATA STRUCTURES-------------------*/
void initializeList(_LINKED_LIST_ *list){
    list->head = NULL;
    list->current = NULL;
    list->tail = NULL;
}

int addHead(_LINKED_LIST_* list, void* data){
    _NODE_ *node = (_NODE_*)malloc(sizeof(_NODE_));
    if(node == NULL) return 0;
    node->data = data;
    if(list->head == NULL){
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;
    return 1;
}

int addTail(_LINKED_LIST_* list, void* data){
    _NODE_ *node = (_NODE_*)malloc(sizeof(_NODE_));
    if(node == NULL) return 0;
    node->data = data;
    node->next = NULL;
    if(list->head == NULL ){
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int searchList(const _LINKED_LIST_ *list, void *data){
    _NODE_ * node = list->head ;
    while(node != NULL) {
        // printf("\nNode->data: %d  Data: %d\n", node->data , data);
        if(node->data == data){
            return 1;
        }
        node = node->next;
    }
    return 0;
}

_NODE_ *getNode(const _LINKED_LIST_ *list, COMPARE compare, void *data){
    _NODE_ *node = list->head;
    while(node != NULL ){
        if(compare(node->data, data) == 0){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void displayLinkedList(const _LINKED_LIST_ *list , DISPLAY display){
    //printf("Linked List\n");
    _NODE_ *current = list->head;
    while(current != NULL){
        display(current->data);
        current = current->next;
    }
}


void removeNode(_LINKED_LIST_ *list, _NODE_ *node) {
    if (node == list->head) {
        if (list->head->next == NULL) {
            list->head = list->tail = NULL;
        } else {
            list->head = list->head->next;
        }
    } else {
        _NODE_ *tmp = list->head;
        while (tmp != NULL && tmp->next != node) {
            tmp = tmp->next;
        }
        if (tmp != NULL) {
            tmp->next = node->next;
        }
    }
    free(node);
}

int listEmpty(const _LINKED_LIST_ *list) {
    return (list->head == NULL);
}

void freeList(_LINKED_LIST_ *list) {
    while(!listEmpty(list)){
        removeNode(list, list->head);
    }
}

/* Initializes Queue */
void initializeQueue(_QUEUE_ * queue) {
    queue->head = NULL ;
    queue->current = NULL ;
    queue->tail = NULL ;
}

/* Adds an element to the Queue(FIFO)  */
int enqueue(_QUEUE_ *queue, void *data ) {
    _NODE_ *newNode = (_NODE_*) malloc(sizeof(_NODE_));
    if (newNode == NULL ) return FAILED;
    newNode->data = data ;
    newNode->next = NULL;
    if(queue->head == NULL) {
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    return SUCCESS;
}

/* Removes an element from the queue at head position*/
void *dequeue(_QUEUE_ * queue){
    if( queueEmpty(queue) ) {
        return NULL;
    }
    _NODE_ *tmp = queue->head;
    void *data = queue->head->data;
    if(queue->head == queue->tail ){
        queue->head = queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    free(tmp);
    return data;
}

/* Displays the whole queue */
void displayQueue(_QUEUE_ * queue, DISPLAY display){
    _NODE_ *node = queue->head;
    printf("%s\n", "Queue: -head-TO-tail-" );
    while(node != NULL) {
        display(node->data);
        node = node->next;
    }
    printf("\n");
}

/* Destroy the whole Queue */
void freeQueue(_QUEUE_ *queue) {
    _NODE_ *tmp = queue->head;
    while (queue->head != NULL ){
        queue->head = queue->head->next;
        free(tmp);
        tmp = queue->head;
    }
    queue->head = queue->tail = NULL;
}

/* returns 1 if the queue is empty */
int queueEmpty(const _QUEUE_ * queue ){
    return (queue->head == NULL);
}

/*----------------CIRCULAR LINKED LIST ---------------------------------*/

void initializeCList(_CLINKED_LIST_ *Clist){
    Clist->head = NULL;
    Clist->tail = NULL;
    Clist->current = NULL;
}

int addCHead(_CLINKED_LIST_ *Clist, void *data){
    _CNODE_ *newCnode = (_CNODE_ *)malloc(sizeof(_CNODE_));
    if(newCnode == NULL) return FAILED;
    newCnode->next= NULL;   newCnode->data = data;

    if(Clist->head == NULL ){
        Clist->head = Clist->tail = newCnode;
    } else {
        Clist->tail->next = newCnode;
        newCnode->next = Clist->head;
        Clist->head = newCnode;
    }
    return SUCCESS;
}

int addCTail(_CLINKED_LIST_ *Clist, void *data){
    _CNODE_ *newCnode = (_CNODE_ *)malloc(sizeof(_CNODE_));
    if(newCnode == NULL) return FAILED;
    newCnode->next = NULL;  newCnode->data = data;

    if(Clist->head == NULL ){
        Clist->tail = Clist->head = newCnode;
    } else {
        Clist->tail->next = newCnode;
        newCnode->next = Clist->head;
        Clist->tail = newCnode;
    }
    return SUCCESS;
}

int removeCNode(_CLINKED_LIST_ *Clist, _CNODE_ *cnode){
    if(cnode == Clist->head){
        Clist->tail->next = Clist->head = Clist->head->next;
        free(cnode);
        return SUCCESS;
    } else if (cnode == Clist->tail){
        _CNODE_ *tmp = Clist->head;
        while(tmp->next!=Clist->tail){
            tmp = tmp->next;
        }
        tmp->next = Clist->tail->next;
        Clist->tail = tmp;
        free(cnode);
    } else {
        _CNODE_ *tmp = Clist->head;
        while(tmp->next != cnode){
            tmp = tmp->next;
        }
        tmp->next = cnode->next;
        free(cnode);
        return SUCCESS;
    }
    return FAILED;
}

_CNODE_ *getCNode(const _CLINKED_LIST_ *Clist, COMPARE compare ,  void *data){
    _CNODE_ *cnode = Clist->head;
    while(cnode != Clist->head){
        if(compare(cnode->data, data))  return cnode;
        cnode = cnode->next;
    }
    return NULL;
}


_CNODE_ *getCNodeIntData(const _CLINKED_LIST_ *Clist, int nodeData){
    _CNODE_ *cnode = Clist->head;
    if(cnode!=NULL){
        if( *((int *)cnode->data) == nodeData)  return cnode;
        cnode = cnode->next;
        while(cnode != Clist->tail){
            if(*((int *)cnode->data) == nodeData) return cnode;
            cnode = cnode->next;
        }
        if(*((int *)cnode->data) == nodeData) return cnode;
    }
    return NULL;
}

void displayCLinkedList(const _CLINKED_LIST_ *Clist, DISPLAY display){
    _CNODE_ *cnode = Clist->head;
    printf("%s\n", "Clist: -head-TO-tail-" );
    if(cnode!=NULL){
        display(cnode->data);
        cnode = cnode->next;
        while(cnode != Clist->tail){
            display(cnode->data);
            cnode = cnode->next;
        }
        display(cnode->data);
    }
    display(Clist->head->data);
    printf("\n");
}

<<<<<<< HEAD
=======

>>>>>>> master
void displayIntCLinkedListFromGivenNode(const _CLINKED_LIST_ *Clist, DISPLAY display, int nodeData) {
    _CNODE_ *cnode = Clist->head;
    int found=0;
    if(cnode!=NULL){
    //    printf("In graph.c : %d\n",__LINE__ );
        if(*((int *)cnode->data) == nodeData){
            found = 1;
        }else cnode = cnode->next;
        while((cnode != Clist->tail) && found!=1) {
            if(*((int *)cnode->data) == nodeData){
                found =1;
                break;
            }
            //printf("In graph.c : %d\n",__LINE__ );
            cnode = cnode->next;
        }
        if(*((int *)cnode->data)==nodeData){
            found=1;
            //printf("In graph.c : %d\n",__LINE__ );
        }
    }
    //printf("In graph.c : %d\n",__LINE__ );
    if(!found) {
    //    printf("...Invalid Node Number...\n");
    } else {
        _CNODE_ *temp = cnode ;
    //    printf("%s\n", "Clist: -head-TO-tail-" );
        if(cnode!=NULL){
            display(temp->data);
            temp = temp->next;
            while(temp != cnode){
    //            printf("In graph.c : %d\n",__LINE__ );
                display(temp->data);
                temp = temp->next;
            }
            display(temp->data);
        }
        printf("\n");
    }
}

int ClistEmpty(const _CLINKED_LIST_ *Clist){
    return (Clist->head == NULL);
}
/*
void freeCList(_CLINKED_LIST_ *Clist){
    _CNODE_ *cnode = Clist->head;
    Clist->tail->next = NULL;
    while(cnode != NULL){
        Clist->head  = Clist->head->next;
        free(cnode);
        cnode = Clist->head;
    }
    Clist->head = Clist->tail = NULL;
}
*/
void freeCListIntData(_CLINKED_LIST_ *Clist){
    if(!ClistEmpty(Clist)){
        _CNODE_ *cnode = Clist->head;
        Clist->tail->next = NULL;
        while(cnode != NULL){
            Clist->head  = Clist->head->next;
            free(cnode->data);
            free(cnode);
            cnode = Clist->head;
        }
        Clist->head = Clist->tail = NULL;
    }
}
<<<<<<< HEAD


void printIntArr(int *arr , size_t n){
    printf("\n");
    for (size_t i = 0; i < n; i++) {
        printf("%d " ,  arr[i]);
    }
    printf("\n");
}
=======
>>>>>>> master
