#include <stdio.h>

typedef struct student_info
{
    char name[40];
    int student_id;
    int age;
} StudentInfo;
void print_student(StudentInfo *s)
{
    printf("Name: %s\n", s->name);
    printf("Student ID: %d\n", s->student_id);
    printf("Age: %d\n", s->age);
}

int main(voiud)
{
    StudentInfo s1 = {"John", 12345, 20};
    print_student(&s1);
}
