/*
	NAME: Kaushal Kishore
	EMAIL: 111601008@smail.iitpkd.ac.in
	TOPIC: Merge SORT
    CCFLAGS: -std=c11
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>


//A: an array
//p,q,r : indices into A. 
//Each of the subarray A[p...q] and A[q+1..r] is assumed to be already sorted.


typedef struct string  {
     char data[30];
} string;




string toLower( string data){
	string str;
	int len = strlen(data.data);
	int i=0;
	for ( i=0; i<len ; i++){
		str.data[i] = tolower(data.data[i]);
	}
	str.data[i] = '\0';
	return str;
}


void merge(string A[], long long int p, long long int q, long long int r ){
    long long int n1 = q-p+1 , n2 = r-q;
    string B[n1], C[n2];
    for (long long int i=0; i<n1 ; i++){
        strcpy(B[i].data , A[i+p].data); //B[i] = A[i+p];
    }
    for (long long int  j=0; j<n2; j++){
        strcpy(C[j].data , A[q+1+j].data); //C[j] = A[q+1+j];
    }
    long long int i, j,k;
    i=j=0;
    k=p;
    string dataC, dataB;
    while(i<n1 && j<n2){
    	dataB = toLower(B[i]);
    	dataC = toLower(C[j]);
        if(strcmp(dataB.data , dataC.data) <= 0)		//B[i]<=C[j
        //if(strcmp(toLower(B[i].data) , toLower(C[i].data)) <= 0)		//B[i]<=C[j]
            strcpy(A[k++].data, B[i++].data);//A[k++] = B[i++];
		else 
            strcpy(A[k++].data, C[j++].data); //A[k++] = C[j++];
    }
    while(i<n1){
		strcpy(A[k++].data, B[i++].data); //        A[k++] = B[i++] ;
    }
    
    while(j<n2){
        strcpy(A[k++].data, C[j++].data); //A[k++] = C[j++];
    }
}


// A : input array
// p,r : starting and ending indices of a subarray of A.

void mergeSort(string A[], long long int p, long long int r){
    if(p<r){
        long long int q = p+ (r-p)/2;
        mergeSort(A, p, q);				// recursive call to the function
        mergeSort(A, q+1, r);
        merge(A, p, q, r);    			// merging the two part
    }
}


// UTILITY FUNCTION
// PRINTING THE ARRAY
void printArray(string a[], long long int size){
    for(size_t i=0; i<size; i++){
        printf("\n%s " , a[i].data);
    }
    printf("\n");
}

// MAIN FUNCTION
int main(){


	printf("\nPlease Enter strings with characters only [a-zA-Z] ");
	printf("\nLength of the each string is limited to 25.\n");
	


    int n;	// ARRAY SIZE
    printf("Number of words : ");
    scanf("%d" , &n);	// INPUT THE ARRAY SIZE
   // long long int *A = (long long int *) malloc(sizeof(long long int)*n); 	// ALLOCATING THE ARRAY SIZE
    printf("Enter the names: \n");
    string *A = (string *) malloc(sizeof(string)*n); 
    for(int i=0; i<n; i++){
        scanf(" %[A-Za-z]" , A[i].data);	// INPUT THE ARRAY
    }
    
    

//    printArray(A,n);	// PRINT THA ARRAY
    puts("Sorted array");
    mergeSort(A , 0 , n-1);	// MERGE SORT THE ARRAY
    printArray(A, n);	// PRINT THE SORTED ARRAY
    free(A);
    return 0;		// RETURN TO THE SYSTEM
}
