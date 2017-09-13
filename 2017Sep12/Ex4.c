#include<stdio.h>
#include<stdlib.h>

void print2Darray(int **a , int r, int c){
    printf("YOUR MATRIX: \n");
    for (int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%3d " , a[i][j]);
        }
        printf("\n");
    }
}

int main(){
    
    int i,j, k, asc=0 , desc=0 ;
    int err=0;
    int r, c;
    printf("row: ");
    scanf(" %d" , &r);
    printf("col: ");
    scanf(" %d" , &c);

    int **ptr = (int **) malloc(sizeof(int*)*r);

    ptr[0] = (int *) malloc(sizeof(int)*c);
    // ptr[1] = (int *) malloc(sizeof(int)*c);

    printf("Enter the matrix: \n");
    scanf(" %d", &ptr[0][0]);
    for (int j=1; j<c; j++){
        scanf(" %d" , &ptr[0][j]);
        if((ptr[0][j-1]<ptr[0][j] && desc==1) || (ptr[0][j-1]>ptr[0][j] && asc==1)){
            err= 1;
            break;
        } else if(ptr[0][j-1]<ptr[0][j]) {
            asc=1;
        } else if(ptr[0][j-1]>ptr[0][j]) {
            desc=1;
        }
    }
    
    if(!err){
  
        for (i=1; i<r; i++){
            ptr[i] = (int *)malloc(sizeof(int)*c);
            scanf(" %d" , &ptr[i][0]);
            if ((asc && ( ptr[i-1][0]>ptr[i][0])) || (desc && ( ptr[i-1][0]<ptr[i][0] ))) {
                err = 1;
                break;
            }

            for (j=1; j<c; j++){
                scanf(" %d", &ptr[i][j]);
                if( (asc && ( (ptr[i][j-1] > ptr[i][j]) || (ptr[i-1][j] > ptr[i][j] ) ) ) 
                        ||  (desc && ( (ptr[i][j-1] < ptr[i][j] ) || ( ptr[i-1][j] < ptr[i][j])))) {
                    err = 1;
                    break;
                }
            }
            if(err==1) break;
        }   
    }
    
    /* priniting the matrix if the order is correct */ 
    if(!err) {
        print2Darray(ptr , r, c);   
        int n;
        /* required operation will take place */ 
        printf("Enter a number you want to search for: ");
        scanf("%d", &n);
        searchElement(ptr , r, c, n);
    }
    else puts("ERROR: Matrix is not in the correct order. Must be either decreasing or increasing.");

    for (i=0; i<r ; i++){
            if(ptr[i]) free(ptr[i]);
    }
    free(ptr);
    return 0;
}
