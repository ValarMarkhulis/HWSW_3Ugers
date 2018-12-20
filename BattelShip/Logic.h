//
// Created by Jonas on 20-12-2018.
//

#ifndef BATTELSHIP_LOGIC_H
#define BATTELSHIP_LOGIC_H

#define BOARD_WITH 10
#define BOARD_HIGHT 10

char MS;  // holds value if master or slave

extern char player1Ships[BOARD_WITH][BOARD_HIGHT];
extern char player1Shots[BOARD_WITH][BOARD_HIGHT];

extern char player2Ships[BOARD_WITH][BOARD_HIGHT];
extern char player2Shots[BOARD_WITH][BOARD_HIGHT];


void setupGame(int b1, int b2);

void printBoard(int choice);




#endif //BATTELSHIP_LOGIC_H
