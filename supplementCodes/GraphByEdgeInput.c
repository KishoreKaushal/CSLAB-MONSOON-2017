#include<stdio.h>
#include<stdlib.h>

typedef struct pairInt {
    int first;
    int second;
} pairInt ;

void inputPair(pairInt *pair) {
    scanf(" %d", &pair->first);
    scanf(" %d", &pair->second);
    return ;
}

pairInt makePair(int a, int b) {
    pairInt p ;
    p.first = a;
    p.second = b;
    return p;
}
// vertex numbering starts from 0
int main(){
    int E , vc;
    pairInt e;
    printf("Vertices: ");    scanf(" %d", &vc);
    printf("Edges: ");    scanf(" %d", &E);

    // declaring adjacency matrix
    int **adjMat;
    adjMat = (int **)malloc(sizeof(int*)*vc);
    for(size_t i=0; i<vc; i++) {
        adjMat[i] = (int *)malloc(sizeof(int )*vc);
    }

    // initializes all cells in adjacency list to 0
    for(size_t i=0; i<vc; i++)
        for(size_t j=0; j<vc; j++) {
            adjMat[i][j] = 0;
        }

    // creates adjacency matrix using edge informations
    for(int i=0; i< E; i++) {
        inputPair(&e);
        if(e.first <vc && e.second < vc){
            adjMat[e.first][e.second] = 1;
            adjMat[e.second][e.first] = 1;
        }
    }

    // printing the adjacency matrix
    printf("Adjacency Matrix\n");
    for (int i=0; i< vc; i++) {
        for(int j=0; j<vc; j++){
            printf("%d ", adjMat[i][j]);
        }
        printf("\n");
    }

    // free all memory
    for (int i = 0; i < vc; i++) {
        free(adjMat[i]);
    }
    free(adjMat);
    return 0;
}
