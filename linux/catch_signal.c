#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void catch_function(int signo)
{
    printf("Caught signal number %d.\n", signo);
}

int main(void)
{
    printf("My process ID is %d.\n", getpid());
    if (signal(SIGINT, catch_function) == SIG_ERR ||
        signal(SIGTERM, catch_function) == SIG_ERR ||
        signal(SIGUSR1, catch_function) == SIG_ERR ||
        signal(SIGUSR2, catch_function) == SIG_ERR)
    {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Signal handler set.\n");
    while (1)
        ;
}
