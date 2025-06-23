#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./proc <timeout>\n");
        return 1;
    }

    int timeout = atoi(argv[1]);
    int counter = 0;

    while (1)
    {
        printf("%d: %d\n", getpid(), counter++);
        fflush(stdout);
        sleep(timeout);
    }

    return 0;
}