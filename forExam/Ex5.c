#include<stdio.h>
#include<stdlib.h>

void print2Darray(int **ptr , int r, int c){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            printf("%4d ", ptr[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int r , c, found=0;
    printf("Row: ");
    scanf(" %d" , &r);
    printf("Column: ");
    scanf(" %d" , &c);

    // input the array
    printf("\nInput the matrix: \n");
    int **ptr;
    ptr = (int**) malloc(sizeof(int)*r);
    for(int i=0; i<r; i++){
        ptr[i] = (int*)malloc(sizeof(int) * c);
        for(int j =0 ; j<c ; j++){
            scanf (" %d" , &ptr[i][j]);
        }
    }
    int m,n;
    for (int i=0; i< r; i++){
        for(int j=0; j<c; j++) {
            // if the required condition  satisfy
            if (ptr[i][j]== 0 ){
                m = i; n=j;
                found=1;
            }
        }
    }
    
    if(found){
        for(int i=0; i<r; i++)
            ptr[i][n]=0;
        for(int j=0; j<c; j++)
            ptr[m][j]=0;
    }

    // print the array
    print2Darray(ptr , r, c);

    // free the array after usage
    for(int i = 0; i<r; i++){
        free(ptr[i]);
    }
    free(ptr);
    return 0;
}
