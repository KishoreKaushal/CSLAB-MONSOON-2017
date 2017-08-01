/*                              */
/*    @kaushal_kishore          */
/* 111601008@smail.iitpkd.ac.in */
/*                              */
/*         Ex1.c                */

#include<stdio.h>
#include<string.h>


/* defining the structure for the student */
typedef struct student {
    char name[32];
    int id;
}   student;


/* this function will modify the data of the student structure */
void modify(student *srtptr){
    strcpy(srtptr->name , "abc"  );
    srtptr->id = 123;
}

/* this function will print the student info */
void PrintStruc(student *s){
    printf("%s\t%d\n", s->name, s->id);
}

int main(){
    /* declaring the student structure */
    student stu1 ;
    /* initializing the structure */
    strcpy(stu1.name , "Kaushal Kishore");    stu1.id = 111601008;
    /* priniting the structure */
    PrintStruc(&stu1);
    /* modifying the data */
    modify(&stu1);
    /* Again priniting the structure*/
    PrintStruc(&stu1);
    return 0;
}
