/**************************************************************************************************************************************
* Filename: tennis2.c
* Class: CPE 2600 121
* Description: Player1 process. Waits for Player2 and returns the ball.
* Author: Jackie Herrick
* Date: 11/10/26
* make
* gcc tennis2.c -o tennis2
* ./tennis2
* make clean
**************************************************************************************************************************************/

#include "tennis.h"

int main(void)
{
    int Player2 = 0;//tracks index to points for current game
    int Player1 = 0;//tracks index to points for current game
    int message = 0;
    pid_t sender = 0;

    int over = 0;
    int type = 0;

    const char *points[] = {"0","Love", "15", "30", "40"};
    // char *score_player1[10];
    // char *score_player2[10];

    srand((unsigned int)time(NULL) ^ (unsigned int)getpid());

    setup_signal();

    printf("=================================\n");
    printf("           Tennis Game\n");
    printf("=================================\n");
    printf("Player1 PID: %d\n", getpid());
    printf("Waiting for the Player2...\n\n");
    fflush(stdout);

    int first_contact = 1;

    while (1)
    {
        message = wait_for_message();

        /* IMPORTANT */
        sender = sender_pid;

        if (first_contact)
        {
            printf("\nPlayer1: Signal received from PID %d\n", sender);
            printf("Player2 has joined!!!\n\n");
            first_contact = 0;
        }

        type = MSG_TYPE(message);

        if (type == MSG_SCORE)
        {
            Player2 = Player2_SCORE(message);
            Player1 = Player1_SCORE(message);
            over = GAME_OVER(message);

            display_score(Player2, Player1);

            if (over)
            {
                printf("\n=================================\n");
                printf("         GAME FINISHED\n");
                printf("=================================\n");
                printf("Score for Player1: %s\n", points[Player2]);
                printf("Score for Player2: %s\n",points[Player1]);
                if (Player1 > Player2)
                {
                    printf("\n\nWinner: Player2\n");
                    break;
                }
                else if (Player2 > Player1)
                {
                    printf("\n\nWinner: Player1\n");
                    break;
                }
                else
                {
                    printf("\n\nMatch ended in a tie.\n");
                    continue;
                }

            }

            printf("Waiting for the next serve...\n");
            fflush(stdout);
            send_message(sender, MESSAGE(MSG_MISS, 0, 0, 0));
            continue;
        }

        if (type != MSG_BALL)
            continue;

        printf("\nPlayer1: Ball received!\n");
        printf("Player1: Preparing to return the ball...\n");
        fflush(stdout);

        random_delay();

        if (successful_return())
        {
            printf("Player1: Successfully returned the ball!\n");
            printf("Player1: Hitting the ball!\a\n");
            fflush(stdout);

            send_message(sender, MESSAGE(MSG_BALL, 0, 0, 0));
        }
        else
        {
            printf("Player1: MISSED THE BALL!\n");
            printf("Player1: Sending miss notification.\n");
            fflush(stdout);

            send_message(sender, MESSAGE(MSG_MISS, 0, 0, 0));
        }
    }

    return EXIT_SUCCESS;
}
