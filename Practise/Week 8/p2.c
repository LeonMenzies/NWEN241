#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int p;

    p = fork() && fork();

    printf("p: %d\n", p);

    return 0;
}