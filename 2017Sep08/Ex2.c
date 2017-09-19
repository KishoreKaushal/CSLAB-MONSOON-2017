#include<stdio.h>
#include<stdlib.h>

// this function will check whether the given array is in ascending order or not
int checkAscending(float *a , int size){
    for (size_t i=1; i<size; i++){
        if(a[i-1]>a[i]) return 0;    
    }
    return 1;
}


int main(){
    int n;
    float *a, t, epsilon = 1e-6;
    scanf("%d" , &n);   // n : size of the array
    a = (float*)malloc(sizeof(float)*n);    // allocating the space for the data
    for (size_t i=0; i<n ; i++)             // loop for taking the iinput
        scanf(" %f" , &a[i]);   
    printf("Target Value: " );              // the target value
    scanf(" %f" , &t );                     // input the target value

    if(!checkAscending(a , n)){             // if not in the ascending order return from the program
        puts("Array Not in Ascending order.....");
        free(a);
        return 0;
    }
    // binary search
    int beg=0, end=n-1;
    int mid = (beg+end)/2;
    int found_index=-1;
    while(beg<=end){
        mid = (beg+end)/2;
        if(a[mid] < t+epsilon && a[mid] > t-epsilon){
            found_index = mid;
            break;
        } else if(t-a[mid]>epsilon ) {
            beg = mid+1;
        } else {
            end = mid-1;
        }
    }
    if(found_index!=-1){
        printf("Target Found at index: %d\n" , found_index);
    } 
    else {
        puts("Target Not Found..");
    }
    free(a);
    return 0;
}
