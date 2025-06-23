#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s command1 command2 [args...]\n", argv[0]);
        exit(1);
    }

    int p[2];
    if (pipe(p) < 0)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork1");
        exit(1);
    }

    if (pid1 == 0)
    {
        close(p[1]);
        if (dup2(p[0], STDIN_FILENO) < 0)
        {
            perror("dup2 read");
            exit(1);
        }
        close(p[0]);
        execvp(argv[2], &argv[2]);
        perror("execvp command2");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork2");
        exit(1);
    }

    if (pid2 == 0)
    {
        close(p[0]);
        if (dup2(p[1], STDOUT_FILENO) < 0)
        {
            perror("dup2 write");
            exit(1);
        }
        close(p[1]);
        execlp(argv[1], argv[1], NULL);
        perror("execlp command1");
        exit(1);
    }

    close(p[0]);
    close(p[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}