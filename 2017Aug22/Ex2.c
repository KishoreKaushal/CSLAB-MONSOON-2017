///////// Ex2.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex2.c      //
//////////////////////////////////

#include<stdio.h>
typedef double flt;

static flt a[100];

// recursive implementation of finding min_element of the array
flt min_element(flt *this, flt *this_next , int size){
    flt N;
    if(this_next != &a[size-1]){    // if this_next == &a[size-1] then we are at the end of the array, therefore return the last  element
        N = min_element(this_next, (this_next+1) , size);
    }
    else return *this_next;
    return (N-*this)>0?*this:N;
}

// entry point
int main(){
    int n=10;
    //scanf(" %d" , &n);
    for (int i=0; i<n; i++) scanf(" %lf" , &a[i]);     // input n=10 elements
    printf("%.10lf\n" , min_element(&a[0], &a[1], n));   //sending first two elements as input to the function
    return 0;
}
