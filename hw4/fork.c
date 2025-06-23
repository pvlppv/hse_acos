#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2;

    p1 = fork();

    if (p1 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (p1 == 0)
    {
        p2 = fork();
        if (p2 < 0)
        {
            perror("fork");
            exit(1);
        }
        if (p2 == 0)
        {
            printf("Hello from Grandchild (PID: %d)\n", getpid());
        }
        else
        {
            wait(NULL);
            printf("Hello from Child (PID: %d)\n", getpid());
        }
    }
    else
    {
        wait(NULL);
        printf("Hello from Parent (PID: %d)\n", getpid());
    }

    return 0;
}