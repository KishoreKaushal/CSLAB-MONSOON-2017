//              Ex5                  //
//      Name : Kaushal Kishore       //
//      111601008@smail.iitpkd.ac.in //

/* Objective :finding element in a rotated ascending array
 *  by an algoritm having O(log(n)) complexity. */

#include<stdio.h>
#include<stdlib.h>

// complexity: O(log(n))
// this function will find the rotation index
int findBreak(int *a , int n){
    int low = 0, high = n-1;
    int mid = low + (high-low)/2;
    
    while(low != high-1 && low != high){
        mid = (low+high)/2;
        if(a[mid] > a[high]){
            low = mid;
        } else if(a[mid] < a[high]) {
            high = mid;
        }
    }
    if(a[low] > a[high]){
        return low;
    } else return -1;
}

// complexity : O(log(n))
// Binary search Algorithm
// returns index if element is present otherwise -1
int binarySearch(int *arr , int low , int high , int ele){
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

// complexity: O(2*log(n)) ==> O(log(n))
// given that original array(without rotation ) is in ascending order (i.e., strictly increasing)
// returns index (zero-based-indexing) if element is found otherwise -1
int FindRotate(int *a, int size, int ele) {
    int low = 0, high = size-1;
    int mid = low + (high-low)/2;      
    
    int breakAt = findBreak(a, size);   // find where the array breaks the order
                                        // -1 if not a rotated array
    if(breakAt==-1){
        return binarySearch(a,low , high, ele);
    } else if( a[high] < ele && a[low]<=ele && ele <= a[breakAt] ) {
        return binarySearch(a,low,breakAt, ele);
    } else if (  a[breakAt+1]<=ele && ele <= a[high]){
        return binarySearch(a,breakAt , high , ele);
    } else {
        return -1;
    }
}

int main(){
    int n, ele;
    printf("Size of The list: ");
    scanf(" %d" , &n);
    int *a = (int *)malloc(sizeof(int)*n);
    printf("Elements of the List:\n ");
    for(int i=0; i<n ; i++ ){
        scanf(" %d", &a[i]);
    }
    printf("Enter the element to find: ");
    scanf(" %d", &ele);
    printf("Index : %d\n" , FindRotate(a , n, ele));
    return 0;
}
