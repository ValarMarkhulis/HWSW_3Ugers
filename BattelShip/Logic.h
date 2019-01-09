//
// Created by Jonas on 20-12-2018.
//
#include <stdio.h>
#ifndef BATTELSHIP_LOGIC_H
#define BATTELSHIP_LOGIC_H

#define BOARD_WIDTH 10
#define BOARD_HIGHT 10

//char MS;  // holds value if master or slave

enum GAMESTATUS{OVER = 0, RUNNING = 1, READY};

int OtherplayerTurn(char *shot, int player);
char checkWinner(int player);


int randomStart();
struct PlayerInfo {
    int p1Board;
    int p2Board;
    int p1Turns;
    int p2Turns;
    int p1Shots;
    int p2Shots;
} playerInfo;

int shipsLeft[2];

extern char ships[2][BOARD_WIDTH][BOARD_HIGHT];
extern char shots[2][BOARD_WIDTH][BOARD_HIGHT];


void setupGame(int b1, int b2, FILE *outStream2);

void printBoard(int choice);
void printField(char c);

int runGame();
int playerTurn(char *shot, int player);
void getCoordinates(char * shot);
int shotLegal(int player, char * shot);
int shootAt(int player, char * shot);

//Cursor implementation
void getCoordinatesCursor(char *shot, int player);

struct cursor_struct {
    int x:5;
    int y:5;
    //int pressed:1;
} cursorP1, cursorP2;

//Print log
void printTilLog(char *string);

#endif //BATTELSHIP_LOGIC_H