#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dob {
    int day, month, year;
};

struct student_info{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void assignValues(struct student_info *stud){
    stud->roll_no = 1234;
    strcpy(stud->name, "Hello World");
    stud->CGPA = 9.42;
    stud->age.day = 25;
    stud->age.month = 07;
    stud->age.year = 2023;
}

void display(struct student_info stud){
    printf("Student Details:\nRoll: %d\nName: %s\nCGPA: %.2f\nDOB: %d/%d/%d\n",
            stud.roll_no, stud.name, stud.CGPA,
            stud.age.day, stud.age.month, stud.age.year );
}

int main(){
    struct student_info stud;
    assignValues(&stud);
    display(stud);
}