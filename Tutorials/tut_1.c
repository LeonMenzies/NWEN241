#include <stdio.h>

float *nums;
int a_size = 2000000;
int idx;

int main(void)
{
    printf("Read how many numbers:");
    scanf("%d", &a_size);
    nums = (float *)calloc(a_size, sizeof(float));

    return 0;
}