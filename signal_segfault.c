/**************************************************************************************************************************************
* Filename: signal_alarm.c
* Class: CPE 2600 121
* Description: This program Demos SIGSEGV that catchs the segmentation fault. 
* Author: Jackie Herrick
* Date: 11/07/26
* gcc signal_segfault.c
* ./a.out
**************************************************************************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void segv_handler(int sig)
{
    printf("segmentation fault was received\n");
    exit(1);
}

int main (int argc, char* argv[]) 
{
    //Segmentation Violation(SIGSEGV).
    signal(SIGSEGV, segv_handler);


    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}