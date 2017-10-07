// Kaushal Kishore
// 111601008
// Ex4.c

// isSubstring() --> strstr()
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int m , n;
    printf("Length of string1: ");
    scanf(" %d", &m);

    printf("Length of string2: ");
    scanf(" %d", &n);

    char *str1 = (char *) malloc (sizeof(char) * (m+1));
    char *str2 = (char *) malloc (sizeof(char) * (n+1));

    printf("String1: ");
    scanf(" %[^\n]s" , str1 );

    printf("String2: ");
    scanf(" %[^\n]s" , str2 );
    
    // finding whether str1 is a rotation of str2
    char *str3 = (char*) malloc(sizeof(char)*(m+n+1));
    strcpy(str3 , str2);
    strcat(str3 , str2);

    // strstr is a method to find a substring
    if(strstr(str3 , str1)!=NULL) {
        printf(" | %s | is a rotation of | %s | .\n" , str1 , str2);
    } else
        printf(" | %s | is not a rotation of | %s | .\n" , str1 , str2);

    free(str1);
    free(str2);
    free(str3);
    return 0;
}
