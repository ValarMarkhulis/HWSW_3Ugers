#include <stdio.h>
//#include <assert.h>
#include "Logic.h"

#define LOG_FILE_NAME "test.log"

int main() {
    //pthread_t thread;

    //pthread_create(&thread, NULL, func, NULL );

    FILE *outStream = NULL;        /* stream to output file battleship.log */

    /* Start of Program */
    outStream = fopen(LOG_FILE_NAME, "w");

    fprintf(outStream, "Start of logfile\n");
    setupGame(4, 4, outStream);
    printBoard(0);
    int winner = runGame(outStream);
    printf("Player %d is the WINNER!", winner);

    //pthread_join(thread , NULL);
    //printf("Hello");
    fclose(outStream);
    return 0;
}

