#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

struct sig_map
{
    char *name;
    int num;
};

struct sig_map sigs[] = {
    {"HUP", SIGHUP}, {"INT", SIGINT}, {"QUIT", SIGQUIT}, {"ILL", SIGILL}, {"TRAP", SIGTRAP}, {"ABRT", SIGABRT}, {"BUS", SIGBUS}, {"FPE", SIGFPE}, {"KILL", SIGKILL}, {"USR1", SIGUSR1}, {"SEGV", SIGSEGV}, {"USR2", SIGUSR2}, {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"CHLD", SIGCHLD}, {"CONT", SIGCONT}, {"STOP", SIGSTOP}, {"TSTP", SIGTSTP}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU}, {NULL, 0}};

int get_sig_num(char *name)
{
    for (int i = 0; sigs[i].name != NULL; i++)
    {
        if (strcmp(sigs[i].name, name) == 0)
        {
            return sigs[i].num;
        }
    }
    return -1;
}

void handler(int s)
{
    printf("[Caught: %s]", strsignal(s));
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: ./catchsig <timeout> [SIGNAL_NAME...]\n");
        return 1;
    }

    for (int i = 2; i < argc; i++)
    {
        int sig_num = get_sig_num(argv[i]);
        if (sig_num != -1)
        {
            signal(sig_num, handler);
        }
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