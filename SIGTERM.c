/**************************************************************************************************************************************
* Filename: SIGNTERM.c
* Class: CPE 2600 121
* Description: This program shows SIGTERM which terminates a request for a process.
* Author: Jackie Herrick
* Date: 11/05/26
* gcc SIGTERM.c
* ./a.out
**************************************************************************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//int kill(pid_t pid, int sig);
//pid = Process ID of the target process
//sig = Signal to send


int main() 
{
    pid_t pid = 1234;  // Target process PID is set to 1234
    //checks the kill was success
    if (kill(pid, SIGTERM) == 0) 
    {
        printf("SIGTERM sent successfully.\n");
    } else 
    {
        perror("kill");
    }

    return 0;
}