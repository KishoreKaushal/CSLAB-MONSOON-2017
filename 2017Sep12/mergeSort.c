/*
	NAME: Kaushal Kishore
	EMAIL: 111601008@smail.iitpkd.ac.in
	TOPIC: Merge SORT
    CCFLAGS: -std=c11
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//A: an array
//p,q,r : indices into A. 
//Each of the subarray A[p...q] and A[q+1..r] is assumed to be already sorted.

void merge(long long int A[], long long int p, long long int q, long long int r ){
    long long int n1 = q-p+1 , n2 = r-q;
    long long int B[n1], C[n2];
    for (long long int i=0; i<n1 ; i++){
        B[i] = A[i+p];
    }
    for (long long int  j=0; j<n2; j++){
        C[j] = A[q+1+j];
    }
    long long int i, j,k;
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

void mergeSort(long long int A[], long long int p, long long int r){
    if(p<r){
        long long int q = p+ (r-p)/2;
        mergeSort(A, p, q);				// recursive call to the function
        mergeSort(A, q+1, r);
        merge(A, p, q, r);    			// merging the two part
    }
}


// UTILITY FUNCTION
// PRINTING THE ARRAY
void printArray(long long int a[], long long int size){
    for(size_t i=0; i<size; i++){
        printf("\n%lld " , a[i]);
    }
    printf("\n");
}

// MAIN FUNCTION
int main(){
    int n;	// ARRAY SIZE
    scanf("%d" , &n);	// INPUT THE ARRAY SIZE
    long long int *A = (long long int *) malloc(sizeof(long long int)*n); 	// ALLOCATING THE ARRAY SIZE
    for(int i=0; i<n; i++){
        scanf(" %lld" , &A[i]);	// INPUT THE ARRAY
    }

//    printArray(A,n);	// PRINT THA ARRAY
    puts("Sorted array");
    mergeSort(A , 0 , n-1);	// MERGE SORT THE ARRAY
    printArray(A, n);	// PRINT THE SORTED ARRAY
    free(A);
    return 0;		// RETURN TO THE SYSTEM
}
