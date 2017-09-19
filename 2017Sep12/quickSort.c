/*
    *Name       : Kuldeep Singh Bhandari
    *Roll No.   : 111601009
    *Aim        : Program to sort an array using quick sort (Recursion)
*/
#include<stdio.h>

int a[100];             //array pointer to store the input list of integers

//just a utility function to swap two elements in the array 'a'
void swap (int i, int j) {

	int temp;			//just a temporary variable
	temp = a[j];
	a[j] = a[i];
	a[i] = temp;

}

//function to find out partition index to split array into two parts : (1) array smaller than pivot (2) array greater than pivot
int partitionArray (int low, int high) {

	int pivot = a[low];						//just making first element in the array to be pivot
	int j;									//loop-counter variable
	int i = low;							//counter variable to modify array in increasing order
	int index = low;						//to store the index of the pivot element

	for (j = low + 1; j <= high; j++){

		if (a[j] <= pivot) {

			if (a[i] == pivot) {
				index = j;					//storing the position of pivot element
			}
			swap(i,j);						//to swap a[i] and a[j]
			i++;							//to increment i to i+1
			
		}

	}

	swap(i,index);							//to swap a[i] and a[index]

	return i;								//return partition position

}

//function to sort the array
void quickSort (int low, int high) {

	if (low < high) {

		int partitionIndex = partitionArray (low, high);			//to find out partition index
		quickSort (low, partitionIndex - 1);						//left-partition of the array
		quickSort (partitionIndex + 1, high);						//right-partition of the array

	}

}

//MAIN FUNCTION BEGINS HERE
int main () {

	int n;              	//to store number of elements in the array
    int i;              //loop counter
    printf("Enter the number of elements in the list : (Max. 100)\n");     //asking user to enter the number of elements in the array
    scanf("%d", &n);            //entering number of elements in the array

    if (n <= 0 || n >= 100) {
        printf("ERROR IN INPUT : Number of elements in the array should be greater than 0 and less than 100. \n");
        return 1;               //program didn't work properly
    }

    printf("Enter the elements in the list (to be sorted) : (INTEGERS ONLY)\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);         //entering the elements in the array
    }

    quickSort(0, n - 1);            //function to sort the given array

    printf("LIST AFTER SORTING IS : \n");

    //printing list after sorting
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;       //returning 0 for successful program

}
//MAIN FUNCTION ENDS HERE
