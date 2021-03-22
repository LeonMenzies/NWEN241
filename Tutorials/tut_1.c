#include <stdio.h>
#include "stud.h"

void print_student(StudentInfo *s)
{
    printf("Name: %s\n", s->name);
    printf("Student ID: %d\n", s->student_id);
    printf("Age: %d\n", s->age);
}

int main(void)
{
    for (int i = 0; i < 9999999999; i++)
    {
        printf("THIS IS BORING\n");
    }
    StudentInfo s1 = {"John", 12345, 20};
    print_student(&s1);
}
