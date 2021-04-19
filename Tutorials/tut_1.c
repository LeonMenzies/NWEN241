#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int a, b;

        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &b);

        printf("Sum: %d\n", a + b);
    }
    else
    {
        printf("Requires 2 nums\n");
    }

    return 0;
}