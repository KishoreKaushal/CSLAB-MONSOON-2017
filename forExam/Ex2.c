#include<stdio.h>
#include<stdlib.h>



// print 2D array : row-major form
void print2D(int *ptr , int r , int c){
    for (int i=0; i <r; i++){
        for (int j=0; j<c; j++){
            printf("%4d ", ptr[i*c+j]);
        }
        printf("\n");
    }
}

void print1D(int *ptr , int size ){
    for (int i=0; i<size; i++){
        printf("%d " , ptr[i]);
    }
    printf("\n");
}

// merge sort : complexity (O(n*log(n)))

void merge(int A[], int p, int q, int r ){
    int n1 = q-p+1 , n2 = r-q;
    int B[n1], C[n2];
    for (int i=0; i<n1 ; i++){
        B[i] = A[i+p];
    }
    for (int  j=0; j<n2; j++){
        C[j] = A[q+1+j];
    }
    int i, j,k;
    i=j=0;
    k=p;
    while(i<n1 && j<n2){
        if(B[i]<=C[j])
            A[k++] = B[i++];
		else 
            A[k++] = C[j++];
    }
    while(i<n1){
        A[k++] = B[i++] ;
    }
    
    while(j<n2){
        A[k++] = C[j++];
    }
}


// A : input array
// p,r : starting and ending indices of a subarray of A.

void mergeSort(int A[], int p, int r){
    if(p<r){
        int q = p+ (r-p)/2;
        mergeSort(A, p, q);				// recursive call to the function
        mergeSort(A, q+1, r);
        merge(A, p, q, r);    			// merging the two part
    }
}




int main(){
    int r, c;
    printf("Row: ");
    scanf(" %d" , &r);
    printf("Col: ");
    scanf(" %d" , &c);
    
    int *arr = (int *)malloc(sizeof(int)*r*c);
    // input array
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            scanf(" %d" , &arr[i*c + j]);
        }
    }
    printf("\nYour Matrix: \n");
    print2D(arr , r, c);
    
    // merge sort the array
    mergeSort(arr , 0 , r*c-1);

    printf("\nSorted 1D array: \n");
    print1D(arr , r*c);
    free(arr);
    return 0;
}
