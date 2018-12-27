#include <stdio.h>
#include "Logic.h"


int main() {


    setupGame(0, 1);
    printBoard(0);
    int winner = runGame();
    printf("Player %d is the WINNER!", winner);

    return 0;
}

