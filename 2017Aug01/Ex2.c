#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct student {
    char name[32];
    int ID;
}   student;

void PrintStruc(student *s){
    printf("Name: %s\tID: %d\n", s->name, s->ID);
}

int compareStu(student *s1, student *s2){
    return (s1->ID > s2->ID);
}

int main(int argc, char const *argv[]) {
    int N;
    scanf("%d " ,&N );
    student *list =  (student*)malloc(sizeof(student)*N);
    student *maxID;
    for (int i=0; i<N; i++){
        scanf("%s %d",list[i].name, &list[i].ID);
    }
/*
    for (int i=0; i<N; i++){
        PrintStruc(&list[i]);
    }
*/
    maxID = &list[0];
    for (int i=1; i<N; i++){
        if(compareStu(&list[i] , maxID)) maxID = &list[i];
    }
    printf("%s" , maxID->name);

    free(list);
    return 0;
}
