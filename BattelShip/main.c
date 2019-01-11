#include <stdio.h>
#include "Logic.h"
#include "Statemachines/Master/Master.h"
#include "Statemachines/Slave/Slave.h"


#define LOG_FILE_NAME "test.log"

//void printTilLog(char *string);
FILE *outStream;
int main() {

    outStream = NULL;        /* stream to output file battleship.log */
    outStream = fopen(LOG_FILE_NAME, "w");
    printTilLog("Start of logfile\n");

    //master(outStream);
    slave(outStream);




    //setupGame(4, 4, outStream);
    //printBoard(0);
    //int winner = runGame();
    //printf("Player %d is the WINNER!", winner);

    printTilLog("Game ended\n");
    fclose(outStream);
    return 0;
}
/*
void printTilLog(char *string){
    fprintf(outStream, string);
    fflush(outStream);
}
 */