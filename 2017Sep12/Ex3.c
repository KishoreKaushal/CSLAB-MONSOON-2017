//              Ex3               //
//      Kaushal Kishore           //
// Objective: QuickSort Algorithm //
// 111601008@smail.iitpkd.ac.in   //
//      CFLAGS : -std=c11         //

#include<stdio.h>
#include<stdlib.h>

// UTILITY FUNCTION : SWAP TWO INT
void swap(int *x , int *y){
    int temp=*x;
    *x = *y;
    *y = temp;
}

// PARTITION THE ARRAY
int partition(int *A, int p, int r){
    int q = p;
    for (int u=p; u<r; u++){
        if(A[u]<=A[r]) {
            swap(&A[q] , &A[u]);
            q++;
        }
    }
    swap(&A[q] , &A[r]);
    return q;
}

// QUICK-SORT ALGORITHM
void quickSort(int *A, int p, int r) {
    int q;
    if(p<r) {
        q = partition(A, p , r);
        quickSort(A, p, q-1);
        quickSort(A, q+1, r);
    }
}



// UTILITY FUNCTION : PRINTING THE ARRAY
void printArray(int *a, int size){
    for(size_t i=0; i<size; i++){
        printf("%d, " , a[i]);
    }
    printf("\n");
}

// MAIN FUNCTION
int main(){
    int n;	// ARRAY SIZE
    printf("Enter the size of the array: ");
    scanf(" %d" , &n);	// INPUT THE ARRAY SIZE
    int *A = (int *) malloc(sizeof(int)*n); 	// ALLOCATING THE ARRAY SIZE
    printf("Enter the elements of the array: \n");
    for(int i=0; i<n; i++){
        scanf(" %d" , &A[i]);	// INPUT THE ARRAY
    }
    printf("Before Sorting: ");
    printArray(A,n);	// PRINT THAT ARRAY
    printf("After Sorting: ");
    quickSort(A , 0 , n-1);	// QUICKSORT THE ARRAY
    printArray(A, n);	// PRINT THE SORTED ARRAY
    free(A);
    return 0;		// RETURN TO THE SYSTEM
}
