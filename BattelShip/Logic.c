#include <stdio.h>
#include "Logic.h"
#include "Boards.h"

#define DEBUG

char player1Ships[BOARD_WITH][BOARD_HIGHT];
char player1Shots[BOARD_WITH][BOARD_HIGHT];

char player2Ships[BOARD_WITH][BOARD_HIGHT];
char player2Shots[BOARD_WITH][BOARD_HIGHT];

/**
 * setups 2 standard boards and all zeros for shots.
 * @param b1 Player one's board choice
 * @param b2 Player two's board choice
 */
void setupGame(int b1, int b2) {

    for (int i = 0; i < BOARD_WITH; ++i) {
        for (int j = 0; j < BOARD_HIGHT; ++j) {
            player1Ships[i][j] = boards[b1][i][j];
            player2Ships[i][j] = boards[b2][i][j];
            player1Shots[i][j] = zeros[i][j];
            player2Shots[i][j] = zeros[i][j];
        }
    }
#ifdef DEBUG
    printf("Boards er lavet \n");
#endif
}
/**
 *
 * @param choice 0 for all boards, 1 for player one, 2 for player two.
 */
void printBoard(int choice) {
    char alfa[10] = {'A','B','C','D','E','F','G','H','I','J'};
    if(choice == 0) {
        printf("Ship boards\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player1Ships[i][j]);
            }
            printf("   ");
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player2Ships[i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WITH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
        printf("\n\n\nShot boards\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player1Shots[i][j]);
            }
            printf("   ");
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player2Shots[i][j]);
            }
            printf(" %d\n",i);
        }
        for (int k = 0; k < 2; ++k) {
            printf("   ");
            for (int i = 0; i < BOARD_WITH; ++i) {
                printf("%c ",alfa[i]);
            }
        }
    } else if( choice == 1) {

        printf("Player one's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player1Ships[i][j]);
            }
            printf("\n");
         }
        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }




        printf("\n\n\nPlayer one's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", player1Shots[i][j]);
            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }
    } else if(choice == 2) {
        printf("Player two's Ship board\n");
        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ",player2Ships[i][j]);
            }
            printf("\n");
        }
        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }




        printf("\n\n\nPlayer two's shot boards\n");

        for (int i = 0; i < BOARD_HIGHT; ++i) {
            printf("%d  ",i);
            for (int j = 0; j < BOARD_WITH; ++j) {
                printf("%c ", player2Shots[i][j]);
            }
            printf("\n");
        }

        printf("   ");
        for (int i = 0; i < BOARD_WITH; ++i) {
            printf("%c ",alfa[i]);
        }
    }
}
