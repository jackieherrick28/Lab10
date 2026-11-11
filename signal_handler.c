/**************************************************************************************************************************************
* Filename: signal_handler.c
* Class: CPE 2600 121
* Description: This program shows SIGTERM and Ctr+C to kill to a process.
* Author: Jackie Herrick
* Date: 11/07/26
* gcc signal_handler.c
* ./a.out
* Ctr+C
**************************************************************************************************************************************/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message and exits
 * @param signum Signal number received
 */
void handle_signal(int signum) {
    printf("\nReceived signal %d (SIGINT)\n", signum);
    //exit(1);
}

int main() {

    // Register the signal handler
    signal(SIGINT, handle_signal);
    int i = 0;
    // Wait until a signal is received
    while (1) {
        printf("%d Sleeping\n", (i+1));
        sleep(1);

                
        if(i > 8)
        {
            if (kill(getpid(), SIGTERM) == 0) 
            {
                printf("SIGTERM sent successfully.\n");
            } else 
            {
                perror("kill");
            }
        }
        i++;
    }

    return 0;
}