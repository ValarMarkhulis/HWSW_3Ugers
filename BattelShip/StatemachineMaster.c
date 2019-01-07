#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

// Tilføj logik til increment af tur og skud
// Tjek at reg tester for det den "kvittere for"/acker
//Husk at slaves antal skud bliver opdateret ved masters REG##xy besked!
//Lav samme som slave

/*
 * Gennemfør et spil med 2 skud fra masteren, 1 fra slaven og slaven siger SPL og afslutter spillet
2
S001STA3
S002BRT+3
S003OKK
S003REG01a2
1
S003OKK
S003REG01a2
0
S003SKD01a2
1
S003OKK
S000SPLS

 */

void STAmsg(int input);
void BRTmsg(int boardNr);
void SKDmsg(int skudNr, char * shot);
void TURmsg(int turNr, char MorS, char TorF);
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
                    scanf("%1d", &p1Board);
                } while (p1Board == -1);
                mode++;
                break;
            case 1: //Start besked
                printf("DEBUG: START MSG \n");
                STAmsg(p1Board);
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
                printf("DEBUG: BOARD MSG\n");
                BRTmsg(p2Board);
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "BRT") == 0) {
                    if(CMD_struct.boardID == -1 ) {
                        mode = 1;
                    } else if (CMD_struct.boardID == p2Board){
                        //printf("Board p2 er registret som %d\n", p2Board);
                        mode++;
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
                printf("DEBUG: TUR M MSG \n");

                TURmsg(p1Turns++,'M','F'); //FIXME Lave funktion der tester vinder..
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
                printf("DEBUG: SHOT MSG \n");
                char shot[2] = {'a','2'};
                SKDmsg(p1Shots++,shot); //FIXME Lave det får input til skud..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "REG") == 0) {
                    if(CMD_struct.shot[0] == shot[0] && CMD_struct.shot[1] == shot[1] ) {
                        //FIXME Vurder det er Master eller slaves tur nu.
                        int turn;
                        printf("HIT OR MISS?: ");
                        scanf("%1d",&turn);
                        if(turn == 1) {
                            mode = 3;
                        } else {
                            mode++;
                        }
                    } else {
                        printf("!!!!REG MSG CONTAINS WRONG COORDINATES!!!!\n");
                    }
                } else {
                    printf("!!!!!SHOT MSG RECEIVED WRONG CMD!!!!!\n");
                }

                break;
            case 5: // TURN S MSG
                printf("DEBUG: TURN S MSG \n");
                TURmsg(p2Turns++,'S','F'); //FIXME Lave funktion der tester vinder..
                getMsg();
                checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "SKD") == 0) {
                    //Save the recieved shots from slave
                    shot[0] = CMD_struct.shot[0];
                    shot[1] = CMD_struct.shot[1];

                    mode++;
                } else if(strcmp(CMD_struct.cmd , "SPL") == 0) {
                    mode = 7;
                } else{
                    printf("!!!!!TURN MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 6: // REG MSG
                 printf("DEBUG: REG MSG \n");
                 REGmsg(p2Shots,shot);
                 getMsg();
                 checkRecivedMsg();

                if(strcmp(CMD_struct.cmd , "OKK") == 0) {
                    //FIXME Vurder det er Master eller slaves tur nu.
                    int turn;
                    printf("HIT OR MISS?: ");
                    scanf("%1d",&turn);
                    if(turn == 1) {
                        mode = 5;
                    } else {
                        mode = 3;
                    }
                }else {
                    printf("!!!!!REG MSG RECEIVED WRONG CMD!!!!!\n");
                }
                break;
            case 7: //Slut spil
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
        printf("test\n");
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


void getMsg() {
    scanf("%11s", ReciveString);
    printf("getMsg modtog: \"%s\"\n",ReciveString);
}

//Messages
void STAmsg(int boardNr) {
    printf("M%03dSTA%d   \n",msgID++,boardNr);
}

void BRTmsg(int boardNr) {
    //TODO Når det skal sendes som en char, skal -/+ deles op som sin egen char
    if(boardNr > 0){
        printf("M%03dBRT+%d   \n",msgID++,boardNr);
    }else{
        printf("M%03dBRT%d   \n",msgID++,boardNr);
    }
}

void SKDmsg(int skudNr, char *shot) {
    printf("M%03dSKD%02d%c%c\n",msgID++,skudNr,shot[0],shot[1]);
}

void SPLmsg(char MorS) {
    printf("M%03dSPL%c   \n",msgID++,MorS);
}

void TURmsg(int turNr, char MorS, char TorF) {
    printf("M%03dTUR%02d%c%c\n",msgID++,turNr,MorS,TorF);
}

void OKKmsg() {
    printf("M%03dOKK    \n",msgID++);
}

void REGmsg(int skudNr, char *shot) {
    printf("M%03dREG%02d%c%c\n",msgID++,skudNr,shot[0],shot[1]);
}