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

int quit_sig_num = 0;
int quit_count = 0;

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
    if (s == quit_sig_num)
    {
        quit_count++;
        printf("[Got quit signal, %d to go]\n", 3 - quit_count);
        if (quit_count >= 3)
        {
            exit(0);
        }
    }
    else
    {
        printf("[Caught: %s]\n", strsignal(s));
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./childctl <timeout> <QUIT_SIGNAL> [OTHER_SIGNALS...]\n");
        return 1;
    }

    int timeout = atoi(argv[1]);
    char *quit_sig_name = argv[2];

    quit_sig_num = get_sig_num(quit_sig_name);
    if (quit_sig_num == -1)
    {
        fprintf(stderr, "Invalid quit signal name\n");
        return 1;
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;

    if (sigaction(quit_sig_num, &sa, NULL) == -1)
    {
        perror("sigaction quit");
        return 1;
    }

    for (int i = 3; i < argc; i++)
    {
        int s_num = get_sig_num(argv[i]);
        if (s_num != -1 && s_num != quit_sig_num)
        {
            if (sigaction(s_num, &sa, NULL) == -1)
            {
                perror("sigaction other");
            }
        }
    }

    int c = 0;
    while (1)
    {
        printf("Message %d\n", c++);
        sleep(timeout);
    }

    return 0;
}