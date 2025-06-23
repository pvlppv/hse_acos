#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s command infile outfile\n", argv[0]);
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
        int in_fd = open(argv[2], O_RDONLY);
        if (in_fd < 0)
        {
            perror("open infile");
            exit(1);
        }
        if (dup2(in_fd, STDIN_FILENO) < 0)
        {
            perror("dup2 stdin");
            exit(1);
        }
        close(in_fd);

        int out_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd < 0)
        {
            perror("open outfile");
            exit(1);
        }
        if (dup2(out_fd, STDOUT_FILENO) < 0)
        {
            perror("dup2 stdout");
            exit(1);
        }
        close(out_fd);

        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(127);
    }
    else
    {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus))
        {
            printf("Child exited with status %d\n", WEXITSTATUS(wstatus));
        }
    }

    return 0;
}