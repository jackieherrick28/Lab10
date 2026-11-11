/**************************************************************************************************************************************
* Filename: signal_alarm.c
* Class: CPE 2600 121
* Description: This program schedules an alarm to be sent to after 5 seconds and a signal handler that prints out the signal was received
* Author: Jackie Herrick
* Date: 11/07/26
* gcc signal_alarm.c
* ./a.out
**************************************************************************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
    printf("Alarm received!\n");
    exit(1);
}

int main(void)
{
    int seconds = 5;
    signal(SIGALRM, handler);

    alarm(seconds);      // Schedule SIGALRM after 5 seconds
    while (seconds > 0)
    {
        printf("Countdown: %d seconds\n", seconds);
        fflush(stdout);
        sleep(1);
        seconds--;
    }
    while (1)
        pause();   // Wait for signals

    return 0;
}