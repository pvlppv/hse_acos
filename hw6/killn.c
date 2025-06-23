#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./killn <PID> <SIGNAL_NAME>\n");
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    char *sig_name = argv[2];

    int sig_num = get_sig_num(sig_name);

    if (sig_num == -1)
    {
        fprintf(stderr, "No such signal\n");
        return 1;
    }

    if (kill(pid, sig_num) == -1)
    {
        perror("kill");
        return 1;
    }

    return 0;
}