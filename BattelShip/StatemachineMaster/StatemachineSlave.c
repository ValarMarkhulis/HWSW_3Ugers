#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include "messeages.h"


int main() {
    int mode = 0;
    int p1Board = -1;
    int p2Board = -1;
    int p1Turns = 0;
    int p2Turns = 0;
    int p1Shots = 0;
    int p2Shots = 0;
    int p2tempBoard = -1;
    int winner = -1;

    //Player2's incomming shots
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
                    scanf("%1d", &p2Board);
                } while (p2Board == -1);
                mode++;
                break;

            case 1: // Wait
                printf("DEBUG: MODE(1) WAIT MSG \n");
                getMsg();
                checkRecivedMsg();
                if(strcmp(CMD_struct.cmd, "STA") == 0) {
                    p1Board = CMD_struct.boardID;
                    mode++;
                } else {
                    printf("!!!!!START MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }

            case 2: //START MSG
                printf("DEBUG: MODE(2) START MSG \n");
                STAmsg('S' , p2Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd, "BRT") == 0) {
                    p2tempBoard = CMD_struct.boardID;
                    mode++;
                } else {
                    printf("!!!!!START MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }
                break;
            case 3: //BOARD BESKED
                printf("DEBUG: MODE(3) BOARD MSG\n");
                if(p2tempBoard == p2Board){
                    BRTmsg('S' , p2Board);
                }else{
                    BRTmsg('S' , -1);
                }
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "TUR") == 0) {

                    if(CMD_struct.turn_char == 'M'){
                        p1Shots++;
                        p1Turns = CMD_struct.shot_number;
                        //Go to TURN M MSG
                        mode++;

                    }else if(CMD_struct.turn_char == 'S'){
                        //Go to TURN S MSG
                        p2Turns = CMD_struct.shot_number;
                        p2Shots++;
                        //mode = 6
                        //TODO Test this plz
                    }else{
                        printf("!!!!!BOARD MSG RECEIVED WRONG turn char: %c!!!!!\n",CMD_struct.turn_char);
                    }
                }else if(strcmp(CMD_struct.cmd , "STA") == 0) {
                    //Go to START MSG
                    mode = 2;
                }else{
                    printf("!!!!!BOARD MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }

                break;
            case 4: //OKK MSG
                printf("DEBUG: MODE(4) OKK MSG!\n");
                OKKmsg();
                getMsg();
                checkRecivedMsg();
                if(strcmp(CMD_struct.cmd , "SKD") == 0) {
                    //Save the recieved shots from MASTER
                    shot[0] = CMD_struct.shot[0];
                    shot[1] = CMD_struct.shot[1];

                    if (CMD_struct.shot_number != p1Shots) {
                        printf("!!!!! SLAVE HAD WRONG SHOT COUNT FOR P1: %d != %d!!!!!!\n", CMD_struct.shot_number, p1Shots);
                    }
                    p2Shots = CMD_struct.shot_number;
                    mode++;
                }else{
                    printf("!!!!!OKK MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }

                break;
            case 5: // REG MSG
                printf("DEBUG: MODE(5) REG MSG \n");
                REGmsg('S' , p2Shots,shot);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "TUR") == 0) {
                    if(CMD_struct.turn_char == 'M'){
                        if(CMD_struct.winner == 'F'){
                            mode = 4;
                            p1Shots++;
                        }else if(CMD_struct.winner == 'T'){
                            mode = 8;
                            winner = 1;
                        }else{
                            printf("!!!!!REG MSG RECEIVED WINNER was recieved: %c!!!!!\n",CMD_struct.winner);
                        }
                    }else if(CMD_struct.turn_char == 'S'){
                        p2Turns++;
                        mode++;

                    }else{
                        printf("!!!!!REG MSG RECEIVED TURN CHAR WRONGLY recieved was: %c!!!!!\n",CMD_struct.turn_char);
                    }
                }else {
                    printf("!!!!!REG MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }
                break;

            case 6: // SHOT S MSG
                printf("DEBUG: MODE(6) SHOT S MSG \n");
                char shot[2] = {'a','2'};
                SKDmsg('S' , p2Shots,shot); //FIXME Lave det får input til skud..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "REG") == 0) {
                    if(CMD_struct.shot[0] != shot[0] || CMD_struct.shot[1] != shot[1] ) {
                        printf("Received %c%c, but shot at: %c%c\n",CMD_struct.shot[0], CMD_struct.shot[1], shot[0], shot[1]);
                    }
                    //TODO Lav skud fra slave på lokalt board
                    mode++;
                } else {
                    printf("!!!!!SHOT MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }
                break;
            case 7: //OKK MSG
                printf("DEBUG: MODE(7) OKK MSG!\n");
                OKKmsg();
                getMsg();
                checkRecivedMsg();
                if(strcmp(CMD_struct.cmd , "TUR") == 0) {
                    if(CMD_struct.turn_char == 'M'){
                        if(CMD_struct.winner == 'F'){
                            mode = 4;
                            p1Shots++;
                        }else{
                            printf("!!!!!OKK MSG RECEIVED M%c, which is not legal!!!!!\n",CMD_struct.winner);
                        }
                    }else if(CMD_struct.turn_char == 'S'){
                        if(CMD_struct.winner == 'F') {
                            mode = 6;
                            p2Shots++;
                        }else if(CMD_struct.winner == 'T') {
                            winner = 2;
                            mode = 8;
                        }else{
                            printf("!!!!!OKK MSG RECEIVED S%c, which is not legal!!!!!\n",CMD_struct.winner);
                        }

                    }else{
                        printf("!!!!!OKK MSG RECEIVED TURN wrongly %c was recieved!!!!!\n",CMD_struct.turn_char);
                    }
                }else {
                    printf("!!!!!OKK MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }
                break;

            case 8: //Slut spil
                printf("DEBUG: MODE(8) GAME OVER MSG!\n");
                if(winner == 1) {
                    SPLmsg('S' , 'M');
                } else if( winner == 2) {
                    SPLmsg('S' , 'S');
                } else {
                    printf("!!!!! END GAME HAVE WRONG WINNER!!!!%d\n",winner);
                }
                printf("DEBUG: Game over, Player %d won!\n\n",winner);
                mode = 0;
                break;

            default:
                return 0;
                break;
        }
    }
    return 0;
}
