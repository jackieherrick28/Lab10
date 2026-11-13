/**************************************************************************************************************************************
* Filename: send_signal.c
* Class: CPE 2600 121
* Description: This program takes in the receiver's PID and generaters a random integer to send
* Author: Jackie Herrick
* Date: 11/07/26
* gcc send_signal.c -o send_signal
* ./send_signal
**************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // typing in PID number
    if (argc != 2)
    {
        printf("Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    // Convert PID from string to integer
    pid_t receiver_pid = atoi(argv[1]);

    // Seed random number generator
    srand(time(NULL));

    // Generate random integer
    int random_number = rand();

    // Print number before sending
    printf("Sending integer: %d ...\n", random_number);

    // Prepare signal data
    union sigval value;
    value.sival_int = random_number;

    // Send SIGUSR1 with integer data
    if (sigqueue(receiver_pid, SIGUSR1, value) == -1)
    {
        perror("sigqueue");
        return 1;
    }

    printf("Signal sent successfully!\n");

    return 0;
}