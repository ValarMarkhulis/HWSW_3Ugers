#include <stdio.h>
//#include <assert.h>
#include "Logic.h"

#define LOG_FILE_NAME "test.log"

void printTilLog(char *string);
FILE *outStream;
int main() {
    //pthread_t thread;

    //pthread_create(&thread, NULL, func, NULL );

    outStream = NULL;        /* stream to output file battleship.log */
    /* Start of Program */
    outStream = fopen(LOG_FILE_NAME, "w");

    printTilLog("Start of logfile\n");


    setupGame(4, 4, outStream);
    printBoard(0);
    int winner = runGame(outStream);
    printf("Player %d is the WINNER!", winner);

    //pthread_join(thread , NULL);
    //printf("Hello");
    printTilLog("Game ended\n");
    fclose(outStream);
    return 0;
}

void printTilLog(char *string){
    fprintf(outStream, string);
    fflush(outStream);
}