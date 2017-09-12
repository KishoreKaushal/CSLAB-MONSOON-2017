#include<stdio.h>
#include<stdlib.h>



int main(){
    
    int asc=0 , desc=0 ;

    int r, c;
    printf("row: ");
    scanf("%d\n" , &r);
    printf("col: ");
    scanf("%d\n" , &c);

    int **ptr = (int *) malloc(sizeof(int)*r);


    for (int i=0; i<r; i++){
        ptr[i] = (int *)malloc(sizeof(int)*c);
        for (int j=0; j<c; j++){
            scanf(" %d", &ptr[i][j]);
        }
    }

    for (int j=0; j<c ; j++){
            free(ptr[j]);
    }
    free(ptr);
    return 0;
}
