#include <stdio.h>
#include <ctype.h>
#include "Logic.h"
#include "Boards.h"
#define DEBUG
char ships[2][BOARD_WITH][BOARD_HIGHT];
char shots[2][BOARD_WITH][BOARD_HIGHT];
enum GAMESTATUS GAME;

/**
 * setups 2 standard boards and all zeros for shots.
 * @param b1 Player one's board choice
 * @param b2 Player two's board choice
 */
void setupGame(int b1, int b2) {



    for (int i = 0; i < BOARD_WITH; ++i) {
        for (int j = 0; j < BOARD_HIGHT; ++j) {
            ships[0][i][j] = boards[b1][i][j];
            ships[1][i][j] = boards[b2][i][j];
            shots[0][i][j] = zeros[i][j];
            shots[1][i][j] = zeros[i][j];
        }
    }

    GAME = READY;

#ifdef DEBUG
    printf("Boards er lavet \n");
#endif
}

/**
 * Prints the playing boards.
 * @param choice 0 for all boards, 1 for player one, 2 for player two.
 */
void printBoard(int choice) {
    char alfa[10] = {'A','B','C','D','E','F','G','H','I','J'};
    if(choice == 0) {
        printf("Ship boards\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", ships[0][i][j]);
            }
            printf("   ");
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",ships[1][i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WITH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
        printf("\n\nShot boards\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",shots[0][i][j]);
            }
            printf("   ");
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",shots[1][i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WITH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
        printf("\n");
    } else if( choice == 1) {

        printf("Player one's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",ships[0][i][j]);
            }
            printf("\n");
         }
        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }

        printf("\n\nPlayer one's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", shots[0][i][j]);
            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }
        printf("\n");


    } else if(choice == 2) {
        printf("Player two's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", ships[1][i][j]);
            }
            printf("\n");
        }
        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }
        printf("\n\nPlayer two's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", shots[1][i][j]);
            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }
    }
    printf("\n");
}

/**
 * This function starts the game, and when it exits the game is over.
 */
int runGame() {
    GAME = RUNNING;
    int shipsLeft[2] = {17,17};
    while(GAME == RUNNING) {
        if(GAME == RUNNING) {
            printf("\n\nPlayer 1: ------------------------------------\n");
            printf("The enemy have %d ship parts left.\n", shipsLeft[1]);
            if(playerTurn(1) == 1) {
                shipsLeft[1]--;
                if (shipsLeft[1] == 0) {
                    GAME = OVER;
                    return 1;
                }
            }
        }
        if(GAME == RUNNING) {
            printf("\n\nPlayer 2: ------------------------------------\n");
            printf("The enemy have %d ship parts left.\n", shipsLeft[0]);
            if (playerTurn(2) == 1) {
                shipsLeft[0]--;
                if (shipsLeft[0] == 0) {
                    GAME = OVER;
                    return 2;
                }
            }
        }
    }

}

/**
 * Handels everything that takes a player turn
 * @param player Who is playing? 1 or 2.
 * @return 1 if the player hits a ship else 0.
 */
int playerTurn(int player){
    char shot[2] = {'0','0'};
    printBoard(player);
    do {
        getCoordinates(shot);
    } while (shotLegal(player, shot) != 1);
    if(shootAt(player, shot) == 1) {
        // Boat have been hit
        printf("HIT!\n");
        return 1;
    } else {
        // Splash
        printf("SPLASH!\n");
        return 0;
    }


}

/**
 * Get coordinate input from the user. (input must be [0-9][A-J] with no space
 * @param shot pointer to the shot array.
 */
void getCoordinates(char * shot) {
    char input[2];
    while(1) {
        printf("input a coordinate set to shoot. (A-J 0-9): ");
        scanf("%2s", input);
//        if (input[1] != ' ') {
        shot[0] = input[0];
        shot[1] = input[1];

//        } else {
//            shot[0] = input[0];
//            shot[1] = input[2];
//
//        }

        shot[0] = (char) toupper( shot[0]);
        printf("\nReceived input was : %c %c\n",shot[0],shot[1]);
        if (shot[0] >= 'A' && shot[0] <= 'J' && shot[1] >= '0' && shot[1] <= '9') {
            return;
        } else {
            printf("\nNot a valid input.. \n\n");
        }
    }
}


/**
 * Looks up if shot is legal or have been used.
 * @param player who's turn is it?
 * @param shot Pointer to shots
 * @return 1 if legal 0 if not.
 */
int shotLegal(int player, char * shot) {
    player--;
    // From char to int..
    int shot_x = (int)shot[0] - 65;
    int shot_y = (int)shot[1] - 48;
#ifdef DEBUG
    printf("Shot tried: (%d,%d) / (%c,%c)\n",shot_x,shot_y,shot[0],shot[1]);
#endif
    if(shots[player][shot_y][shot_x] == '0') {
#ifdef DEBUG
        printf("Shot evaluated to legal.\n");
#endif
        return 1;
    } else {
#ifdef DEBUG
        printf("Shot evaluated to illegal.\n");
#endif
        return 0;
    }
}

/**
 * Makes the shot at a set of coordinates,
 * @param shot
 * @return 1 if hit 0 if mis.
 */
int shootAt(int player, char *shot) {
    player--;
    int enemy = -1;
    // From char to int.
    int shot_x = (int)shot[0] - 65;
    int shot_y = (int)shot[1] - 48;
    if(player == 0) { // Player 1-2 skal være 0-1 i arrayet.
        enemy = 1;
    } else {
        enemy = 0;
    }

    shots[player][shot_y][shot_x] = '1';

    if (ships[enemy][shot_y][shot_x] == '1') {
        ships[enemy][shot_y][shot_x] = 'X';
        return 1;
    } else {
        return 0;
    }

}
