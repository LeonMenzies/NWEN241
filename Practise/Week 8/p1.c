#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int p;

    p = fork();

    if (p < 0)
    {
        printf("Error forking\n");
    }
    if (p == 0)
    {
        execl("/bin/ls", "ls", NULL);
        printf("Completed with exec\n");
    }
    if (p > 0)
    {
        printf("In parent. Process ID: %d, MY Child ID: %d\n", getpid(), p);
    }
    return 0;
}