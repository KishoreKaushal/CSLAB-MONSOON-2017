// NAME  : Kaushal Kishore
//  EMAIL : 111601008@smail.iitpkd.ac.in
//  CCFLAGS: -std=c11


#include<stdio.h>
#include<stdlib.h>

// print array : utility function
void printArray(int A[], int size){
    printf("\n");
    for (int i=0; i<size; i++){
        printf("%d, ", A[i]);
    }
    printf("\n");
}

// bubble sort algorithm
void bubbleSort(int arr[] , int size){
    int temp , flag=0;
    for (int i=0; i<size; i++){
        flag=0;
        for(int j=1; j<size-i ; j++){
            if(arr[j]>arr[j-1]){		// swap function
                temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
                flag=1;
            }
        }
        printArray(arr, size);			// print each step
        if(flag==0) break;				// if there is no swapping
    }
}



int main(){
    int size =0;
    scanf("%d" , &size);			// input the size of the array
    int *ptr = (int*) malloc(sizeof(int)*size) ;	// array containing the data
	
    for (int i=0; i<size; i++){			// input the data
        scanf("%d " , &ptr[i]);
    }
    printf("Original Array: ");
	printArray(ptr , size);			// print the original array
	printf("\n");		 
	
    bubbleSort(ptr , size);			// using the bubble sort algorithm to sort the data
    printf("\nSORTED ARRAY: ");		
    printArray(ptr , size);			// print the sorted array	
    free(ptr);
    return 0;
}
