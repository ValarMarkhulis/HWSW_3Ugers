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
                    scanf("%1d", &p1Board);
                } while (p1Board == -1);
                mode++;
                break;
            case 1: //Start besked
                printf("DEBUG: MODE(1) START MSG \n");
                STAmsg('M',p1Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd, "STA") == 0) {
                    p2Board = CMD_struct.boardID;
                    mode++;
                } else {
                    printf("!!!!!START MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 2://BRÆT BESKED
                printf("DEBUG: MODE(2) BOARD MSG\n");
                BRTmsg('M',p2Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "BRT") == 0) {
                    if(CMD_struct.boardID == -1 ) {
                        mode = 1;
                    } else if (CMD_struct.boardID == p2Board){
                        //printf("Board p2 er registret som %d\n", p2Board);
                        mode++;
                        p1Turns++;
                        //TODO Implementere tilfælig start af master eller slave..
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
                p1Shots++;
                TURmsg('M',p1Turns,'M','F'); //FIXME Lave funktion der tester vinder..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "OKK") == 0) {
                    mode++;
                }else if(strcmp(CMD_struct.cmd , "SPL") == 0) {
                    mode = 7;
                }else {
                    printf("!!!!!TURN MSG RECEIVED WRONG CMD!!!!!\n");
                }


                break;
            case 4: // SHOT M MSG
                printf("DEBUG: MODE(4) SHOT MSG \n");
                char shot[2] = {'a','2'};
                SKDmsg('M',p1Shots++,shot); //FIXME Lave det får input til skud..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "REG") == 0) {
                    if(CMD_struct.shot[0] == shot[0] && CMD_struct.shot[1] == shot[1] ) {
                        //FIXME Vurder det er Master eller slaves tur nu.
                        int turn;
                        printf("HIT OR MISS?: ");
                        scanf("%1d",&turn);
                        if(turn == 1) { // HIT
                            mode = 3;
                        } else {        // MISS
                            mode++;
                            p2Turns++;
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
                p2Shots++;
                TURmsg('M',p2Turns,'S','F'); //FIXME Lave funktion der tester vinder..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "SKD") == 0) {
                    //Save the recieved shots from slave
                    shot[0] = CMD_struct.shot[0];
                    shot[1] = CMD_struct.shot[1];
                    if(CMD_struct.shot_number != p2Shots) {
                        printf("!!!!! SLAVE SENDT WRONG SHOT COUNT: %d != %d!!!!!!\n",CMD_struct.shot_number, p2Shots);
                    }
                    mode++;
                } else if(strcmp(CMD_struct.cmd , "SPL") == 0) {
                    mode = 7;
                } else{
                    printf("!!!!!TURN MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 6: // REG MSG
                 printf("DEBUG: MODE(6) REG MSG \n");
                 REGmsg('M',p2Shots,shot);
                 getMsg();
                 checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "OKK") == 0) {
                    //FIXME Vurder det er Master eller slaves tur nu.
                    int turn;
                    printf("HIT OR MISS?: ");
                    scanf("%1d",&turn);
                    if(turn == 1) { // HIT
                        mode = 5;
                    } else {
                        mode = 3;  // MISS
                        p1Turns++; // It's now player 1's turn.
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
                return 0;
                break;
        }
    }
    return 0;
}
