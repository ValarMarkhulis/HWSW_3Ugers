#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "Logic.h"


int main() {
    //pthread_t thread;

    //pthread_create(&thread, NULL, func, NULL );

    setupGame(0, 0);
    printBoard(0);
    int winner = runGame();
    printf("Player %d is the WINNER!", winner);

    //pthread_join(thread , NULL);
    //printf("Hello");
    
    return 0;
}

