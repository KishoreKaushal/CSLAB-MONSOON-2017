///////// Ex1.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex1.c      //
//////////////////////////////////

#include<stdio.h>

typedef long long int lli;

// recursive implementation to get fibonacci number
lli fib( lli n){
    lli N;
    if(n<=1){
        return n;   // end condition
    }   else {
        N = fib(n-2) + fib(n-1);    // based on the principle that fibonacci of a number is he sum of the fibonnaci of the previous two numbers with the condition that n=0 fibonnaci is 0 while for n=1 fibonacci is 1
        //printf("%lld\n", N);
        return N;
    }
}

// entry point
int main(){
    lli n;
    scanf(" %lld" , &n);
    //fib(n);
    for (int i=0; i<n; i++){
        printf("%lld\n" , fib(i));
    }
    return 0;
}
