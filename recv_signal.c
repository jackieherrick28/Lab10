/**************************************************************************************************************************************
* Filename: rev_signal.c
* Class: CPE 2600 121
* Description: This program takes the random integer that was send from them through their PID
* Author: Jackie Herrick
* Date: 11/07/26
* make
* gcc rev_signal.c -o rev_signal
* ./rev_signal
* make clean
**************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//Signal Handler
void handle_signal(int sig, siginfo_t*info, void * context)
{
    printf("Integer Received: %d\n", info->si_value.sival_int);
    exit(1);
}

int main()
{
    struct sigaction sa;

    //for additional signal info
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    //SIGUSR1
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

    return 0;
}
