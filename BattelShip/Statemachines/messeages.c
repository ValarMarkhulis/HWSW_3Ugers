//
// Created by Jonas on 09-01-2019.
//

#include "messeages.h"
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

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
            tempTurn[i] = ReciveString[i+7];
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
void STAmsg(char Sender, int boardNr) {
    printf("%c%03dSTA%d   \n",Sender, msgID++,boardNr);
}

void BRTmsg(char Sender, int boardNr) {
    //TODO Når det skal sendes som en char, skal -/+ deles op som sin egen char
    if(boardNr > 0){
        printf("%c%03dBRT+%d   \n", Sender ,msgID++,boardNr);
    }else{
        printf("%c%03dBRT%d   \n", Sender,msgID++,boardNr);
    }
}

void SKDmsg(char Sender, int skudNr, char *shot) {
    printf("%c%03dSKD%02d%c%c\n", Sender,msgID++,skudNr,shot[0],shot[1]);
}

void SPLmsg(char Sender, char MorS) {
    printf("%c%03dSPL%c   \n", Sender,msgID++,MorS);
}

void TURmsg(char Sender, int turNr, char MorS, char TorF) {
    printf("%c%03dTUR%02d%c%c\n", Sender,msgID++,turNr,MorS,TorF);
}

void OKKmsg() {
    printf("S%03dOKK    \n", msgID++);
}

void REGmsg(char Sender, int skudNr, char *shot) {
    printf("%c%03dREG%02d%c%c\n", Sender,msgID++,skudNr,shot[0],shot[1]);
}