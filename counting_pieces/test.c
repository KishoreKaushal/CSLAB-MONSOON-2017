#include<stdio.h>
#include<stdlib.h>

typedef struct intArr {
    int data[10];
} intArr;

intArr returnStructType( int arr[], int size) {
    intArr s;

    for (int i=0; i<size; i++ ){
        s.data[i] = arr[i];
    } 
    return s;
}

int main(){
    int a[10];
    for (int i=0; i<5; i++) 
        scanf(" %d", &a[i]);

    intArr b = returnStructType(a , 5);
    for (int i=0; i<5; i++)
        printf("\n %d", b.data[i]);

    return 0;
}
