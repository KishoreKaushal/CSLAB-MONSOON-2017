#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student {
    char name[32];
    int id;
}   student;

void modify(student *s){
    strcpy(s->name , "abc"  );
    s->id = 123;
}

void PrintStruc(student *s){
    printf("Name: %s\tID: %d\n", s->name, s->id);
}

int main(){
    student *stu1 = (student*)malloc(sizeof(student*));
    strcpy(stu1->name , "Kaushal Kishore");
    stu1->id = 111601008;
    PrintStruc(stu1);
    modify(stu1);
    PrintStruc(stu1);
    
    free(stu1);
    return 0;
}
