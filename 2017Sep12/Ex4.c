#include<stdio.h>
#include<stdlib.h>



int main(){
    
    int i,j, k, asc=0 , desc=0 ;
    int err=0;
    int r, c;
    printf("row: ");
    scanf("%d\n" , &r);
    printf("col: ");
    scanf("%d\n" , &c);

    int **ptr = (int **) malloc(sizeof(int)*r);

    ptr[0] = (int*) malloc(sizeof(int)*c);
    scanf(" %d", &ptr[0][0]);
    for (int j=1; j<c; j++){
        scanf(" %d" , &ptr[0][j]);
        if((ptr[0][j-1]<ptr[0][j] && desc==1) || (ptr[0][j-1]>ptr[0][j] && asc==1)){
            err= 1;
        } else if(ptr[0][j-1]<ptr[0][j]) {
            asc=1;
        } else if(ptr[0][j-1]>ptr[0][j]) {
            desc=1;
        }
    }
    
    if(err != 1){

        for (i=1; i<r; i++){
            ptr[i] = (int *)malloc(sizeof(int)*c);
            for (j=0; j<c; j++){
                scanf(" %d", &ptr[i][j]);
            }
        }   
    }
    if(err==1) {
        // pass //
        return 2;
    }

    for (j=0; j<c ; j++){
            free(ptr[j]);
    }
    free(ptr);
    return 0;
}
