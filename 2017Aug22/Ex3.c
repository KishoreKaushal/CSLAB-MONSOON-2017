///////// Ex3.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex2.c      //
//////////////////////////////////

#include<stdio.h>

typedef long long int lli;
void print_recursively(lli n){
    if(n<=0){
        printf("0 ");   //if at the end point
    } else {
        printf("%lld " , n);
        print_recursively(n-1);
    }
}

int main(){
    lli n;
    scanf(" %lld" , &n);
    print_recursively(n);
    return 0;
}
