#include <stdio.h>

// Define structure record
typedef struct record
{
    char name[40];
    short int age;
    float height;
} student_record;

// Implement print_record() function
void print_record(student_record r)
{
    printf("Name  : %s\n", r.name);
    printf("Age   : %d\n", r.age);
    printf("Height: %.2f\n", r.height);
}

int main(void)
{
    struct record rec;

    scanf("%s %d %f", &rec.name, &rec.age, &rec.height);
    print_record(rec);
    return 0;
}
