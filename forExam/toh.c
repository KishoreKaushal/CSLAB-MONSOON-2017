// Kaushal Kishore
// 111601008
// Tower of Hanoi Recursive Solution

#include<stdio.h>

// Recursive Solution
void tohRecursive(int n, char from_rod , char to_rod , char aux_rod) {
    if(n==1){
        printf("Move disk 1 from rod %c to rod %c\n", from_rod, to_rod);
        return ;
    }
    tohRecursive(n-1 , from_rod, aux_rod, to_rod);
    printf("Move disk %d from rod %c to rod %c\n" , n, from_rod, to_rod);
    tohRecursive(n-1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    scanf(" %d", &n);
    tohRecursive(n , 'A' , 'C' , 'B');
    return 0;
}
