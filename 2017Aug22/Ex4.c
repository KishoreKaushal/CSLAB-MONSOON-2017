///////// Ex3.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex2.c      //
//////////////////////////////////

#include<stdio.h>
#include<string.h>

/* returns 1 if the string is palindrome otherwise 0*/
int palindromeCheck(char s[] , int prev , int next , int size){
    if(prev==0){
        return (s[prev]==s[next]);
    } else {
        if(!palindromeCheck(s , prev-1, next+1, size))
            return 0;
        else
            return (s[prev]==s[next]);
    }
}

/* entry point */
int main(){
    char s[1000];
    printf("Enter a string(size<999): ");
    scanf("%s", s);
    int p,n,size;
    size= strlen(s);
    if(size%2!=0){
        p=n=size/2;
    } else {
        n = size/2;
        p = n-1;
    }
    printf("Palindrome : %d\n", palindromeCheck(s , p, n, size) );
    return 0;
}
