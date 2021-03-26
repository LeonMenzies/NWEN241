#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;
    int *array;

    printf("Enter number of items: ");
    scanf("%d", &size);

    array = (int *)malloc(size * sizeof(int));

    if (array == NULL)
    {
        printf("You fucked up\n");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d: ", i);
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d: ", array[i]);
    }

    return 0;
}