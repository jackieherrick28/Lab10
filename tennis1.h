/**************************************************************************************************************************************
* Filename: tennis1.h
* Class: CPE 2600 121
* Description: This program defines the methods used in player2's game
* Author: Jackie Herrick
* Date: 11/10/26
**************************************************************************************************************************************/

static int game_won(int Player2, int Player1)
{
    return (Player2 >= 4 || Player1 >= 4) && abs(Player2 - Player1) >= 2;
}

static void serve(pid_t Player1_pid)
{
    printf("\nPlayer2: Serving the ball!\a\n");
    fflush(stdout);
    send_message(Player1_pid,(MESSAGE(MSG_BALL, 0, 0, 0)));
}
