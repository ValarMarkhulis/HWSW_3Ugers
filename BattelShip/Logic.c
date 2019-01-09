#include <stdio.h>
#include <ctype.h>
#include <mem.h>
#include "Logic.h"
#include "Boards/Boards.h"
#define DEBUG
char ships[2][BOARD_HIGHT][BOARD_WIDTH];
char shots[2][BOARD_HIGHT][BOARD_WIDTH];
enum GAMESTATUS GAME;
FILE *outStream;

/**
 * setups 2 standard boards and all zeros for shots.
 * @param b1 Player one's board choice
 * @param b2 Player two's board choice
 */
void setupGame(int b1, int b2, FILE *outStream2) {

    playerInfo.p1Board = -1;
    playerInfo.p2Board = -1;
    playerInfo.p1Turns = 0;
    playerInfo.p2Turns = 0;
    playerInfo.p1Shots = 0;
    playerInfo.p2Shots = 0;

    shipsLeft[0] = 17;
    shipsLeft[1] = 17;

    cursorP1.x = 0;
    cursorP1.y = 0;
    cursorP2.x = 0;
    cursorP2.y = 0;

    outStream = outStream2;

    memcpy(shots, zeros, BOARD_WIDTH * BOARD_WIDTH);
    memcpy(shots + 1, zeros, BOARD_WIDTH * BOARD_WIDTH);
    memcpy(ships, boards + b1, BOARD_WIDTH * BOARD_WIDTH);
    memcpy(ships + 1, boards + b2, BOARD_WIDTH * BOARD_WIDTH);
    fprintf(outStream, "Player 1 uses board %d\n"
                       "Player 2 uses board %d\n", b1, b2);
    fflush(outStream);

    /*
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HIGHT; ++j) {
            ships[0][i][j] = boards[b1][i][j];
            ships[1][i][j] = boards[b2][i][j];
            shots[0][i][j] = zeros[i][j];
            shots[1][i][j] = zeros[i][j];
        }
    }
    */

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
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(ships[0][i][j]);

            }
            printf("   ");
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(ships[1][i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WIDTH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
        printf("\n\nShot boards\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(shots[0][i][j]);
            }
            printf("   ");
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(shots[1][i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WIDTH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
        printf("\n");
    } else if( choice == 1) {

        printf("Player one's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(ships[0][i][j]);
            }
            printf("\n");
         }
        printf("   ");
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            printf("%c ",alfa[i]);
        }

        printf("\n\nPlayer one's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(shots[0][i][j]);
            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            printf("%c ",alfa[i]);
        }
        printf("\n");


    } else if(choice == 2) {
        printf("Player two's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(ships[1][i][j]);
            }
            printf("\n");
        }
        printf("   ");
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            printf("%c ",alfa[i]);
        }
        printf("\n\nPlayer two's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                printField(shots[1][i][j]);            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WIDTH; ++i) {
            printf("%c ",alfa[i]);
        }
    }
    printf("\n");
}

/**
 * Prints a single charecter for the playingfield..
 * @param c
 */
void printField(char c) {
    if(c < '7') {
        printf("%c ",c);
    } else if(c == '7') {
        printf("@ ");
    } else {
        printf("X ");
    }
}

/**
 * This function starts the game, and when it exits the game is over.
 */
 /*
int runGame() {
    GAME = RUNNING;
    printTilLog("Game is setup\n");


    while(GAME == RUNNING) {
        if(GAME == RUNNING) {
            printTilLog( "It is Player 1's turn\n");


            while(playerTurn(shipsLeft[1], NULL, 0) == 1) {
                fprintf(outStream, "\tPlayer 1 hit a ship and there is %d ships remaining\n", shipsLeft[1]);
                fflush(outStream);
                shipsLeft[1]--;
                if (shipsLeft[1] == 0) {
                    printTilLog( "\tPlayer 1 hit player 2's last ship and won!\n");
                    GAME = OVER;
                    return 1;
                }
            }
        }
        if(GAME == RUNNING) {
            printTilLog( "It is Player 2's turn\n");

            while(playerTurn(shipsLeft[0], NULL, 0) == 1) {
                fprintf(outStream, "\tPlayer 2 hit a ship and there is %d ships remaining\n", shipsLeft[0]);
                fflush(outStream);
                shipsLeft[0]--;
                if (shipsLeft[0] == 0) {
                    printTilLog( "\tPlayer 2 hit player 1's last ship and won!\n");
                    GAME = OVER;
                    return 2;
                }
            }
        }
    }

}
  */

/**
 * Handels shots from This player
 * @return 1 if the player hits a ship else 0.
 */
int playerTurn(char *shot, int player) {
    printf("\n\nPlayer %d: ------------------------------------\n",player);
    printf("The enemy have %d ship parts left.\n", shipsLeft[1]);
    printBoard(player);
    do {
        getCoordinates(shot);
        //getCoordinatesCursor(shot,player);
    } while (shotLegal(player, shot) != 1);
    if(shootAt(player, shot) == 1) {
        // Boat have been hit
        printf("HIT!\n");
        if(player == 1) {
            shipsLeft[1]--;
        } else {
            shipsLeft[0]--;
        }

        return 1;
    } else {
        // Splash
        printf("SPLASH!\n");
        return 0;
    }
}

/**
 * Handels shots from Other player
 * @return 1 if the player hits a ship else 0.
 */
int OtherplayerTurn(char *shot, int player) {
    printf("\nPlayer %d: ------------------------------------\n\n\n",player);

    if (shotLegal(player, shot) == 1) {
        if(shootAt(player, shot) == 1) {
            // Boat have been hit
            printf("HIT!\n");
            if(player == 1) {
                shipsLeft[1]--;
            } else {
                shipsLeft[0]--;
            }
            return 1;
        } else {
            // Splash
            printf("SPLASH!\n");
            return 0;
        }
    } else {
        printf("!!!!!! OtherPlayerTurn Not legeal turn recived..\n");
        printTilLog("!!!!!! OtherPlayerTurn Not legeal turn recived..\n");
        return -1;
    }

}

char checkWinner(int player) {
    if(player == 1) {
        if(shipsLeft[1] == 0) {
            return 'T';
        } else {
            return 'F';
        }
    } else {
        if(shipsLeft[0] == 0) {
            return 'T';
        } else {
            return 'F';
        }
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
 * Move the correct cursor with the information from them two strings
 * @param pStruct The cursor of current player which want to move his cursor
 */
void CursorMove(struct cursor_struct *pStruct, const char xstring[3], const char ystring[3]) {

    //Look at x-coordinat
    if (xstring[0] == '-' && xstring[1] == '1') {
        if (pStruct->x == 0) {
            //do nothing because it would result in out of bounce
        } else {
            pStruct->x -= 1;
        }
    } else if (xstring[0] == '0') {
        //Do nothing
    } else if (xstring[0] == '1') {
        if (pStruct->x >= BOARD_HIGHT - 1) {
            //do nothing because it would result in out of bounce
        } else {
            pStruct->x += 1;
        }

    } else
        printf("X coordinat is wrong %s\n", xstring);

    //Look at y-coordinat
    if (ystring[0] == '-' && ystring[1] == '1') {
        if (pStruct->y == 0) {
            //do nothing because it would result in out of bounce
        } else {
            pStruct->y -= 1;
        }
    } else if (ystring[0] == '0') {
        //Do nothing
    } else if (ystring[0] == '1') {
        if (pStruct->y >= BOARD_WIDTH - 1) {
            //do nothing because it would result in out of bounce
        } else {
            pStruct->y += 1;
        }

    } else
        printf("Y coordinat is wrong %s\n", ystring);

    printf("The cursor is updated: "
           "x->%d , y->%d\n", pStruct->x, pStruct->y);

}


/**
 * Get coordinate input from the keyboard from the user and move the cursor.
 * @param shot pointer to the shot array.
 */
void getCoordinatesCursor(char *shot, int player) {
    struct cursor_struct *playerCursor;
    if (player == 1) {
        //Player 1
        playerCursor = &cursorP1;
    } else {
        //player 2
        playerCursor = &cursorP2;
    }
    while (1) {
        char x_movement[3] = "-1";
        char y_movement[3] = "-1";
        char wantToShot[2] = "0";
        printf("Move the cursor in the x axis (-1,0 or 1): ");

        do {
            scanf("%2s", x_movement);
        } while (strspn(x_movement, "-01") == 0 && strspn(y_movement, "-01") < 3);
        //strspn returns the amount of occurences of each of the chars passed as the second parameter in x_movement
#ifndef DEBUG
        printf("x_movement= %s\n",x_movement);
#endif

        printf("Move the cursor in the y axis (-1,0 or 1): ");
        do {
            scanf("%2s", y_movement);
        } while (strspn(y_movement, "-01") == 0 && strspn(y_movement, "-01") < 3);
        //strspn returns the amount of occurences of each of the chars passed as the second parameter in x_movement

#ifndef DEBUG
        printf("y_movement= %s\n",y_movement);
#endif

        CursorMove(playerCursor, x_movement, y_movement);
        printf("You want to shot? (0/1)?");
        do {
            scanf("%2s", wantToShot);
        } while (strspn(wantToShot, "01") == 0 || strspn(wantToShot, "-") > 0);

        if (wantToShot[0] == '1') {
            //Convert x and y cursor coordinate to chars and check if they are valid
            shot[0] = (char) (playerCursor->x + 65);
            shot[1] = (char) (playerCursor->y + 48);
            printf("\nReceived input was : %c %c\n", shot[0], shot[1]);
            if (shot[0] >= 'A' && shot[0] <= 'J' && shot[1] >= '0' && shot[1] <= '9') {
                return;
            } else {
                printf("\nNot a valid input.. \n\n");
                //The cursor must have glitched out, so resetting them should fix it
                playerCursor->x = 0;
                playerCursor->y = 0;
            }
        }//else reloop the for loop and move the cursor again

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

    shots[player][shot_y][shot_x] = '7';

    if (ships[enemy][shot_y][shot_x] >= '1' &&  ships[enemy][shot_y][shot_x] <= '6') {
        ships[enemy][shot_y][shot_x] +=7;
        shots[player][shot_y][shot_x] = 'X';
        return 1;
    } else {
        ships[enemy][shot_y][shot_x] = '7';
        shots[player][shot_y][shot_x] = '7';
        return 0;
    }

}

void printTilLog(char *string){
    fprintf(outStream, string);
    fflush(outStream);
}

int randomStart() {
    //FIXME lav mig random..
    return 1;
}