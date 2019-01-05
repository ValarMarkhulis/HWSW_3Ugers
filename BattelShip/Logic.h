//
// Created by Jonas on 20-12-2018.
//

#ifndef BATTELSHIP_LOGIC_H
#define BATTELSHIP_LOGIC_H

#define BOARD_WITH 10
#define BOARD_HIGHT 10

//char MS;  // holds value if master or slave

enum GAMESTATUS{OVER = 0, RUNNING = 1, READY};



extern char ships[2][BOARD_WITH][BOARD_HIGHT];
extern char shots[2][BOARD_WITH][BOARD_HIGHT];



void setupGame(int b1, int b2);

void printBoard(int choice);
void printField(char c);

int runGame();
int playerTurn(int player, int shipsLeft);
void getCoordinates(char * shot);
int shotLegal(int player, char * shot);
int shootAt(int player, char * shot);


#endif //BATTELSHIP_LOGIC_H
