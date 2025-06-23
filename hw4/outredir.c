#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s command output_filename\n", argv[0]);
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }

        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        close(fd);

        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}