// Ex4
// Kaushal Kishore
// 111601008@smail.iitpkd.ac.in


#include<stdio.h>
#include<stdlib.h>


// UTILITY FUNCTION : Print the 2-D array
void print2Darray(int **a , int r, int c){
    printf("YOUR MATRIX: \n");
    for (int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%3d " , a[i][j]);
        }
        printf("\n");
    }
}


// Binary Search Algorithm for Ascending order
int binarySearchAsc(int *arr , int low , int high , int ele){
    while (low <= high)
    {
        int mid = low + (high-low)/2;
        if (arr[mid] == ele) 
            return mid;    
        if (arr[mid] < ele) 
            low = mid + 1;  
        else
            high = mid - 1; 
    }
    return -1; 
}

// Binary Search Algorithm for Descending Order
int binarySearchDesc(int *arr , int low , int high , int ele){
    while (low <= high)
    {
        int mid = low + (high-low)/2;
        if (arr[mid] == ele) 
            return mid;    
        if (arr[mid] > ele) 
            low = mid + 1;  
        else
            high = mid - 1; 
    }
    return -1; 
}


// complexity = O(n*log(n))
// order = 1 refers to ascending order
// this function uses Binary-Search algorithm as its part
void searchElementOrder(int **a , int r, int c, int order , int ele){
    int found = 0, index;
    if(order==1){
        for(int i=0 ; i < r; i++){
            index = binarySearchAsc(a[i] , 0 , c-1 , ele);
            if(index!=-1) {
                found =1;
                printf("Index: (row, col) : (%d, %d)\n", i , index);
            }
        }        
    } else {
        for(int i=0 ; i < r; i++){
            index = binarySearchDesc(a[i] , 0 , c-1 , ele);
            if(index!=-1) {
                found =1;
                printf("Index: (row, col) : (%d, %d)\n", i , index);
            }
        }        
    }
    if(!found) printf("Element Not Found..\n");
    return ;
}

int main(){
    // asc = 0 : means array is currently not initialized or not in ascending order
    // desc = 0 : similarly this means array is currently uninitialized or not in descending order
    // clearly asc = 1 and desc =1 can't be true at same time for our desired array therefore
    //                  if this situation arise then set err = 1 
    // err = 1 : error state i.e., desc and asc are both equal to 1 

    int i,j, k, asc=0 , desc=0 ;
    int err=0;
    int r, c;       // r = no. of rows and c=no. of cols
    printf("row: ");
    scanf(" %d" , &r);
    printf("col: ");
    scanf(" %d" , &c);

    // ptr = 2-D array
    int **ptr = (int **) malloc(sizeof(int*)*r);

    // taking input  the matrix and checking for the desired error state simultaneously
    ptr[0] = (int *) malloc(sizeof(int)*c);
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
        } else err=1;
    }
    
    if(!err){
        for (i=1; i<r; i++){
            ptr[i] = (int *)malloc(sizeof(int)*c);
            scanf(" %d" , &ptr[i][0]);
            if (    (asc && ( ptr[i-1][0]>ptr[i][0])) 
                    || (desc && ( ptr[i-1][0]<ptr[i][0] )) 
                    || (ptr[i-1][0] == ptr[i][0]) 
                ) {
                err = 1;
                break;
            }
            for (j=1; j<c; j++){
                scanf(" %d", &ptr[i][j]);
                if( (asc && ( (ptr[i][j-1] >= ptr[i][j]) 
                        || (ptr[i-1][j] >= ptr[i][j] ) ) ) 
                        ||  (desc && ( (ptr[i][j-1] <= ptr[i][j] ) 
                        || ( ptr[i-1][j] <= ptr[i][j])))
                    ) {
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
        scanf(" %d", &n);
        searchElementOrder(ptr , r, c, asc, n);
    }
    else puts("ERROR: Matrix is not in the correct order. Must be either decreasing or increasing.");

    // freeing the memory
    for (i=0; i<r ; i++){
            if(ptr[i]) free(ptr[i]);
    }
    free(ptr);
    return 0;
}
