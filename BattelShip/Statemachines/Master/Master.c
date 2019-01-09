//
// Created by Jonas on 09-01-2019.
//

#include "Master.h"

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include "../messeages.h"
#include "../../Logic.h"


void master(FILE *outStream2) {
    outStream = outStream2;
    int mode = 0;
    int turn;


    //Shots
    char shot[2] = {'a','2'};

    while(1) {
        //Initialise struct to zeros
        CMD_struct.sender = '0';
        CMD_struct.msgID = 0;
        strcpy( CMD_struct.cmd, "000" );
        CMD_struct.boardID = 0;
        strcpy( CMD_struct.shot, "00" );
        CMD_struct.turn_char = '0';
        CMD_struct.winner = '0';
        CMD_struct.shot_number = 0;

        switch (mode) {
            case 0: //Start (input)
                printf("DEBUG: MODE(0) START (INPUT)\n");
                do {
                    printf("Input a board ID:");
                    scanf("%1d", &playerInfo.p1Board);
                } while (playerInfo.p1Board == -1);
                mode++;
                break;
            case 1: //Start besked
                printf("DEBUG: MODE(1) START MSG \n");
                STAmsg('M',playerInfo.p1Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd, "STA") == 0) {
                    playerInfo.p2Board = CMD_struct.boardID;
                    mode++;
                } else {
                    printf("!!!!!START MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 2://BRÆT BESKED
                printf("DEBUG: MODE(2) BOARD MSG\n");
                BRTmsg('M',playerInfo.p2Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "BRT") == 0) {
                    if(CMD_struct.boardID == -1 ) {
                        mode = 1;
                    } else if (CMD_struct.boardID == playerInfo.p2Board){ // Vi er enige om p2's board
                        setupGame(playerInfo.p1Board, playerInfo.p2Board, outStream);
                        //runGame();
                        if(randomStart() == 1) {
                            // P1's tur
                            mode++;
                            playerInfo.p1Turns++;
                        } else {
                            // P2's tur
                            mode = 5;
                            playerInfo.p2Turns++;
                        }
                    } else {
                        printf("!!!!!Board for p2 var ikke ens!!!!!!\n");
                        mode = 1;
                    }
                } else {
                    printf("!!!!!BOARD MSG RECEIVED WRONG CMD!!!!!\n");
                }

                break;
            case 3: // TUR M MSG
                printf("DEBUG: MODE(3) TUR M MSG \n");
                playerInfo.p1Shots++;
                TURmsg('M',playerInfo.p1Turns,'M',checkWinner(1));
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "OKK") == 0) {
                    mode++;
                }else if(strcmp(CMD_struct.cmd , "SPL") == 0) {
                    printf("Player: 1 won!!\n");
                    mode = 7;
                }else {
                    printf("!!!!!TURN MSG RECEIVED WRONG CMD!!!!!\n");
                }


                break;
            case 4: // SHOT M MSG
                printf("DEBUG: MODE(4) SHOT MSG \n");
                turn = playerTurn(shot, 1);

                SKDmsg('M', playerInfo.p1Shots++ , shot);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "REG") == 0) {
                    if(CMD_struct.shot[0] == shot[0] && CMD_struct.shot[1] == shot[1] ) {
                        if(turn == 1) { // HIT
                            mode = 3;
                        } else {        // MISS
                            mode++;
                            playerInfo.p2Turns++;
                        }
                    } else {
                        printf("!!!!REG MSG CONTAINS WRONG COORDINATES!!!!\n");
                        printf("Received %c%c, but expeted: %c%c\n",CMD_struct.shot[0], CMD_struct.shot[1], shot[0], shot[1]);
                    }
                } else {
                    printf("!!!!!SHOT MSG RECEIVED WRONG CMD!!!!!\n");
                }

                break;
            case 5: // TURN S MSG
                printf("DEBUG: MODE(5) TURN S MSG \n");
                playerInfo.p2Shots++;
                TURmsg('M',playerInfo.p2Turns,'S',checkWinner(2));
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "SKD") == 0) {
                    //Save the recieved shots from slave
                    shot[0] = CMD_struct.shot[0];
                    shot[1] = CMD_struct.shot[1];
                    if(CMD_struct.shot_number != playerInfo.p2Shots) {
                        printf("!!!!! SLAVE SENDT WRONG SHOT COUNT: %d != %d!!!!!!\n",CMD_struct.shot_number, playerInfo.p2Shots);
                    }
                    mode++;
                } else if(strcmp(CMD_struct.cmd , "SPL") == 0) {
                    printf("Player: 2 won!!\n");
                    mode = 7;
                } else{
                    printf("!!!!!TURN MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 6: // REG MSG
                printf("DEBUG: MODE(6) REG MSG \n");
                turn = OtherplayerTurn(shot, 2);
                REGmsg('M',playerInfo.p2Shots,shot);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "OKK") == 0) {

                    if(turn == 1) { // HIT
                        mode = 5;
                    } else {
                        mode = 3;  // MISS
                        playerInfo.p1Turns++; // It's now player 1's turn.
                    }
                }else {
                    printf("!!!!!REG MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 7: //Slut spil
                printf("DEBUG: MODE(7) Game over, someone won!\n\n");
                mode = 0;
                break;

            default:
                printf("NOGET GIK FRYGTELIG GALT!!! ARRRGH\n");
                return;
                break;
        }
    }
    return;
}





/*void printTilLog(char *string) {
    fprintf(outStream, string);
    fflush(outStream);
}

 */