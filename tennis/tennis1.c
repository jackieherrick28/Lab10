/**************************************************************************************************************************************
* Filename: tennis1.c
* Class: CPE 2600 121
* Description: Player2 process. Starts the game and tracks exchanges.
* Author: Jackie Herrick
* Date: 11/10/26
* gcc tennis1.c -o tennis1
* ./tennis1 PID_Number
* make clean
**************************************************************************************************************************************/

#include "tennis.h"
#include "tennis1.h"

#define MAX_EXCHANGES 10

int main(int argc, char *argv[])
{
    int Player2 = 0;//tracks index to points for current game
    int Player1 = 0;//tracks index to points for current game
    int message = 0;
    pid_t sender = 0;
    int type = 0;
    int exchanges = 0;
    int serve_count = 0;

    const char *points[] = {"0","Love", "15", "30", "40"};//score rules according to google
    // char *score_player1[10];//holds score for each game 
    // char *score_player2[10];//holds score for each game 

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <Player1_pid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t Player1_pid = (pid_t)atoi(argv[1]);

    if (Player1_pid <= 0)
    {
        fprintf(stderr, "Invalid Player1 PID.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL) ^ (unsigned int)getpid());

    setup_signal();

    printf("=================================\n");
    printf("           Tennis Game\n");
    printf("=================================\n");
    printf("Player2 PID: %d\n", getpid());
    printf("Player1 PID: %d\n", Player1_pid);

    sleep(1);
    printf("=========== Game 1 ==============\n");
    serve(Player1_pid);

    while (1)
    {
        message = wait_for_message();
        sender = sender_pid;

        if (sender != Player1_pid)
        {
            fprintf(stderr, "Unexpected signal sender: %d\n", sender);
            continue;
        }

        type = MSG_TYPE(message);

        if (type == MSG_MISS)
        {
            printf("Player2: Player1 missed the ball!\n");
            printf("Player2: Point awarded to Player2.\n");

            Player2++;
        }
        else if (type == MSG_BALL)
        {
            exchanges++;
            printf("\n_________________________________\n\n");
            printf("Exchanges out %d of %d", exchanges, MAX_EXCHANGES);
            printf("\n_________________________________\n");

            if (exchanges >= MAX_EXCHANGES)
            {
                printf("\nMaximum exchanges reached.\n");
                if (Player1 > Player2)
                {
                    printf("Ending match.\n");
                    send_message( Player1_pid, MESSAGE( MSG_SCORE, Player2, Player1, 1));
                    printf("\n=================================\n");
                    printf("         GAME FINISHED\n");
                    printf("=================================\n");
                    printf("Score for Player1: %s\n", points[Player2]);
                    printf("Score for Player2: %s\n",points[Player1]);
                    printf("\n\nWinner: Player2\n");
                    break;
                }
                else if (Player2 > Player1)
                {
                    printf("Ending match.\n");
                    send_message( Player1_pid, MESSAGE( MSG_SCORE, Player2, Player1, 1));
                    printf("\n=================================\n");
                    printf("         GAME FINISHED\n");
                    printf("=================================\n");
                    printf("Score for Player1: %s\n", points[Player2]);
                    printf("Score for Player2: %s\n",points[Player1]);
                    printf("\n\nWinner: Player1\n");
                    break;
                }
                else if(serve_count == 0)
                {
                     printf("\n\nBut match ended in a tie.\n");
                     printf("\nPlayer2 is starting a new game..\n");
                     printf("waiting for the next serve...\n\n");
                     serve(Player1_pid);
                     serve_count++;
                     continue;
                } 
                else
                {

                }
                
            }

            printf("\nPlayer2: Received the returned ball!\n");
            printf("Player2: Preparing to return it...\n");
            fflush(stdout);

            random_delay();

            if (successful_return())
            {
                printf("Player2: Successfully returned the ball!\n");
                printf("Player2: Hitting the ball!\a\n");
                fflush(stdout);

                send_message(
                    Player1_pid,
                    MESSAGE(MSG_BALL, 0, 0, 0));

                continue;
            }
            else
            {
                printf("Player2: MISSED THE BALL!\n");
                printf("Player2: Point awarded to Player1.\n");
                fflush(stdout);

                Player1++;
            }
        }
        else
        {
            continue;
        }

        int over = game_won(Player2, Player1);

        if (over)
        {
            send_message( Player1_pid, MESSAGE( MSG_SCORE, Player2, Player1, over));
            printf("\n=================================\n");
            printf("         GAME FINISHED\n");
            printf("=================================\n");
            printf("Score for Player1: %s\n", points[Player1]);
            printf("Score for Player2: %s\n",points[Player2]);
            printf("Winner: %s\n", Player2 > Player1 ? "Player2" : "Player1");
            break;
        }
        else
        {
            display_score(Player1, Player2);
            printf("Player2: Sending score update...\n");
            send_message( Player1_pid, MESSAGE( MSG_SCORE, Player2, Player1, over));
            random_delay();
            serve(Player1_pid);
        }
    }

    return EXIT_SUCCESS;
}