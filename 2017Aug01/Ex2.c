/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex2.c                */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Defining the student structure */
typedef struct student {
    char name[32];
    int ID;
}   student;

/* To print the student INFO */
void PrintStruc(student *s){
    printf("Name: %s\tID: %d\n", s->name, s->ID);
}

/* Return 1 if s1->ID is greater than s2->ID */
int compareStu(student *s1, student *s2){
    return (s1->ID > s2->ID);
}

/* Entry point */
int main(int argc, char const *argv[]) {
    /* N: no. of the students */
    int N;
    scanf("%d " ,&N );

    /* Declaring the student dunamic array */
    student *list =  (student*)malloc(sizeof(student)*N);

    /* maxID structure pointer will point to the student with max ID */
    student *maxID;


    /* Initializing the maxID structure pointer */
    maxID = &list[0];

    scanf("%30[a-zA-Z ]  ",list[0].name);
    scanf(" %d" , &list[0].ID);

    for (int i=1; i<N; i++){
        scanf(" %30[a-zA-Z ]  ",list[i].name);
        scanf(" %d" , &list[i].ID);
        if(compareStu(&list[i] , maxID)) maxID = &list[i];
    }

/* Uncomment the following code to print all the structural information */

    for (int i=0; i<N; i++){
        PrintStruc(&list[i]);
    }

    printf("%s\n" , maxID->name);

    free(list);
    return 0;
}
