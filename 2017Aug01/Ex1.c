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
    printf("Name: %s\tID: %d\n", s->name, s->id);
}

int main(){
    student stu1 ;
    strcpy(stu1.name , "Kaushal Kishore");
    stu1.id = 111601008;
    PrintStruc(&stu1);
    modify(&stu1);
    PrintStruc(&stu1);
    return 0;
}
