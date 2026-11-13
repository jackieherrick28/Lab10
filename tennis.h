/**************************************************************************************************************************************
* Filename: tennis.h
* Class: CPE 2600 121
* Description: This program defines the methods used in both players tennis games
* Author: Jackie Herrick
* Date: 11/10/26
**************************************************************************************************************************************/

#ifndef TENNIS_H
#define TENNIS_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define BALL_SIGNAL (SIGRTMIN)

#define MSG_BALL  1
#define MSG_SCORE 2
#define MSG_MISS  3

#define WIN_CHANCE 80

#define MESSAGE(type, player1, player2, over) \
    (((type) << 24) | ((player1) << 16) | ((player2) << 8) | (over))


#define MSG_TYPE(value) (((value) >> 24) & 0xFF)
#define Player1_SCORE(value) (((value) >> 16) & 0xFF)
#define Player2_SCORE(value) (((value) >> 8) & 0xFF)
#define GAME_OVER(value) ((value) & 0xFF)

static volatile sig_atomic_t received = 0;
static volatile sig_atomic_t sender_pid = 0;
static volatile sig_atomic_t message_value = 0;



static void ball_handler(int signo, siginfo_t *info, void *context)
{
    (void)signo;
    (void)context;

    sender_pid = info->si_pid;
    message_value = info->si_value.sival_int;
    received = 1;
}

static void setup_signal(void)
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_sigaction = ball_handler;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);

    if (sigaction(BALL_SIGNAL, &action, NULL) == -1) 
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

static int wait_for_message(void)
{
    sigset_t block_set, old_set;

    sigemptyset(&block_set);
    sigaddset(&block_set, BALL_SIGNAL);

    if (sigprocmask(SIG_BLOCK, &block_set, &old_set) == -1) 
    {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    while (!received) 
    {
        sigset_t wait_set = old_set;
        sigdelset(&wait_set, BALL_SIGNAL);

        sigsuspend(&wait_set);
    }

    received = 0;

    int result = message_value;

    if (sigprocmask(SIG_SETMASK, &old_set, NULL) == -1) 
    {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    return result;
}

static void send_message(pid_t target, int value)
{
    union sigval data;
    data.sival_int = value;

    if (sigqueue(target, BALL_SIGNAL, data) == -1) 
    {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }
}

static void random_delay(void)
{
    sleep(1 + rand() % 2);
}

static int successful_return(void)
{
    return rand() % 100 < WIN_CHANCE;
}

static void display_score(int Player1, int Player2)
{
        printf("\n*********************************\n");
        printf("       \t  Score\n");
        printf("*********************************\n");
    const char *points[] = {"0","Love", "15", "30", "40"};

        if (Player1 == Player2)
        {
            printf("Score for both players is %s\n\n", points[Player1]);
        }
        else if (Player1 > Player2)
        {
            printf("score for player1: %s\n", points[Player1]);
            printf("score for player2: %s\n", points[Player2]);
            printf("\nPlayer1 has the Advantage!!!\n");
        }
        else
        {
            printf("score for player1: %s\n", points[Player1]);
            printf("score for player2: %s\n", points[Player2]);
            printf("\nPlayer2 has the Advantage!!!\n");
        }
} 

#endif

