/**************************************************************************************************************************************
* Filename: signal_sigaction.c
* Class: CPE 2600 121
* Description: Demonstrates using sigaction() with SA_SIGINFO to obtain information about the sender of SIGUSR1.
* Author: Jackie Herrick
* Date: 11/07/26
* gcc signal_sigaction.c
* ./a.out
* kill -SIGUSR1 PID_Number
**************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int sig, siginfo_t *info, void *context)
{
    (void)context;  /* Unused parameter */
    printf("Received signal %d from process %d\n", sig, info->si_pid);
    exit(1);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while (1)
    {
        pause();   /* Sleep until a signal arrives */
    }

    return EXIT_SUCCESS;
}