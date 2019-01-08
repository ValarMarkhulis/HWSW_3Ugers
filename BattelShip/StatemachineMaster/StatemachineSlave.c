#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

void STAmsg(int input);
void BRTmsg(int boardNr);
void SKDmsg(int skudNr, char * shot);
void SPLmsg(char MorS);
void REGmsg(int skudNr, char * shot);
void OKKmsg();

void getMsg();

void checkRecivedMsg();

int msgID = 0;
char ReciveString[12];
char SendString[12];

struct CMD{
    char sender;
    int msgID;
    char cmd[3];
    int boardID;
    char shot[2];
    char turn_char;
    char winner;
    int shot_number;
}CMD_struct;

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
                printf("DEBUG: START (INPUT)\n");
                do {
                    printf("Input a board ID:");
                    scanf("%1d", &p2Board);
                } while (p2Board == -1);
                mode++;
                break;

            case 1: // Wait
                printf("DEBUG: WAIT MSG \n");
                getMsg();
                checkRecivedMsg();
                if(strcmp(CMD_struct.cmd, "STA") == 0) {
                    p1Board = CMD_struct.boardID;
                    mode++;
                } else {
                    printf("!!!!!START MSG RECEIVED WRONG CMD: %s!!!!!\n",CMD_struct.cmd);
                }

            case 2: //START MSG
                printf("DEBUG: START MSG \n");
                STAmsg(p2Board);
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
                printf("DEBUG: BOARD MSG\n");
                if(p2tempBoard == p2Board){
                    BRTmsg(p2Board);
                }else{
                    BRTmsg(-1);
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
                printf("DEBUG: OKK MSG!\n");
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
                printf("DEBUG: REG MSG \n");
                REGmsg(p2Shots,shot);
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
                printf("DEBUG: SHOT S MSG \n");
                char shot[2] = {'a','2'};
                SKDmsg(p2Shots,shot); //FIXME Lave det får input til skud..
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
                printf("DEBUG: OKK MSG!\n");
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
                if(winner == 1) {
                    SPLmsg('M');
                } else if( winner == 2) {
                    SPLmsg('S');
                } else {
                    printf("!!!!! END GAME HAVE WRONG WINNER!!!!%d\n",winner);
                }
                printf("DEBUG: Game over, someone won!\n\n");
                mode = 0;
                break;

            default:
                return 0;
                break;
        }
    }
    return 0;
}

void checkRecivedMsg() {
    CMD_struct.sender = ReciveString[0];

    char Strings[3];
    for (int i = 0; i < 3; i++) {
        Strings[i] = ReciveString[i+1];
    }
    CMD_struct.msgID = atoi(Strings);
    for (int i = 0; i < 3; i++) {
        Strings[i] = ReciveString[i+4];
    }
    strcpy( CMD_struct.cmd, Strings );
    printf("CMD i struckt er nu: %s \n",Strings);

    if(strcmp(CMD_struct.cmd,"STA") == 0){
        //printf("test\n");
        char temp = ReciveString[7];
        CMD_struct.boardID = atoi(&temp);


    }else if(strcmp(CMD_struct.cmd,"BRT") == 0){
        char temp_sign = ReciveString[7];
        char temp = ReciveString[8];
        if(temp_sign == '-'){
            CMD_struct.boardID = -1;
        }else if(temp_sign == '+'){
            CMD_struct.boardID = atoi(&temp);
        }else{
            printf("!!!!!!THE BRT COMMAND WAS RECIEVED, BUT SOMETHING WENT WRONG WITH THE BOARD NUMBER!!!!!!!\n");
        }


    }else if(strcmp(CMD_struct.cmd,"TUR") == 0){
        char temp_int[2];
        for (int i = 0; i < 2; i++) {
            temp_int[i] = ReciveString[i+7];
        }
        CMD_struct.shot_number = atoi(temp_int);
        CMD_struct.turn_char = ReciveString[9];
        CMD_struct.winner   =  ReciveString[10];

    }else if(strcmp(CMD_struct.cmd,"SPL") == 0){
        CMD_struct.winner = ReciveString[7];

    }else if(strcmp(CMD_struct.cmd,"REG") == 0 || strcmp(CMD_struct.cmd,"SKD") == 0){
        char tempTurn[2];
        for (int i = 0; i < 2; i++) {
            tempTurn[0] = ReciveString[i+7];
        }
        CMD_struct.shot_number = atoi(tempTurn);
        CMD_struct.shot[0] = ReciveString[9];
        CMD_struct.shot[1] = ReciveString[10];

    }else if(strcmp(CMD_struct.cmd,"OKK") == 0){

    } else {
        printf("!!!!!RECEIVED A COMMAND THAT DOES NOT EXIST!!!!!!\n");
    }

}
//FIXME Don't overflow (999) msgID

// FIXME Send MASTER / SLAVE videre til alle messeage beskeder!!.
void getMsg() {
    scanf("%11s", ReciveString);
    printf("getMsg modtog: \"%s\"\n",ReciveString);
}

//Messages
void STAmsg(int boardNr) {
    printf("S%03dSTA%d   \n",msgID++,boardNr);
}

void BRTmsg(int boardNr) {
    //TODO Når det skal sendes som en char, skal -/+ deles op som sin egen char
    if(boardNr > 0){
        printf("S%03dBRT+%d   \n",msgID++,boardNr);
    }else{
        printf("S%03dBRT-1   \n",msgID++);
    }
}

void SKDmsg(int skudNr, char *shot) {
    printf("S%03dSKD%02d%c%c\n",msgID++,skudNr,shot[0],shot[1]);
}

void SPLmsg(char MorS) {
    printf("S%03dSPL%c   \n",msgID++,MorS);
}


void OKKmsg() {
    printf("S%03dOKK    \n",msgID++);
}

void REGmsg(int skudNr, char *shot) {
    printf("S%03dREG%02d%c%c\n",msgID++,skudNr,shot[0],shot[1]);
}