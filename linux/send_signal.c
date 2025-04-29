#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char input[10];
    printf("Enter process number: ");
    int processNo = atoi(fgets(input, 10, stdin));
    printf("Sending signal signal to process %d.\n", processNo);
    kill(processNo, SIGUSR1);
    return EXIT_SUCCESS;
}
