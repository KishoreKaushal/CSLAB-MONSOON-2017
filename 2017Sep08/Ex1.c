// CCFLAGS: -std=c11
// kaushal kishore
// 111601008@smail.iitpkd.ac.in

#include <stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
    float *a, t;
    //declaring the epsilon value
    float eps = 1e-6;
    int n; // size of the array
    int status=0;   //status will store whether the number found or not
    scanf("%d", &n);
    a = (float*)malloc(sizeof(float)*n);    //allocating the space
    for (size_t i=0; i<n ; i++)
        scanf(" %f", &a[i]);        // scanning the array input
    printf("\nEnter the target Value: ");   // the target value
    scanf(" %f" , &t );                     // the target value input
    for(int i =0; i<n;i++){                 
        if(a[i]<t+eps && a[i]>t-eps){       // checking approximate equality
            printf("Target found at index : %d\n" , i );    // print if the target is found
            status=1;
        }
    }
    if(!status) puts("Target Not Found");   // if target is not in the array
    free(a);                                // free the allocated array
    return 0;
}
