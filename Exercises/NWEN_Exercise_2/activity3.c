#include <stdio.h>

// Define structure record
typedef struct record
{
    char name[40];
    short int age;
    float height;
} student_record;

// Implement print_record_ptr() function
void print_record_ptr(struct record *s)
{
    printf("Name  : %s\n", s->name);
    printf("Age   : %d\n", s->age);
    printf("Height: %.2f", s->height);
}

int main(void)
{
    struct record rec;

    scanf("%s %d %f", rec.name, &rec.age, &rec.height);
    print_record_ptr(&rec);
    return 0;
}
