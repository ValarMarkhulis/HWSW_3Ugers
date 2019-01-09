//
// Created by Jonas on 09-01-2019.
//

#ifndef STATEMACHINEMASTER_MESSEAGES_H
#define STATEMACHINEMASTER_MESSEAGES_H

void STAmsg(char Sender, int input);
void BRTmsg(char Sender, int boardNr);
void SKDmsg(char Sender, int skudNr, char * shot);
void TURmsg(char Sender, int turNr, char MorS, char TorF);
void SPLmsg(char Sender, char MorS);
void REGmsg(char Sender, int skudNr, char * shot);
void OKKmsg();

void getMsg();

void checkRecivedMsg();

int msgID;
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







#endif //STATEMACHINEMASTER_MESSEAGES_H
