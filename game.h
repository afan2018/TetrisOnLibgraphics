#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#ifndef _defGD
#define _defGD

typedef struct {
	bool isDropping;
	bool isGaming;
	int score;
	int level;
	int elimRowCounter;
	char usrName[25];
} Game;

typedef struct {
	// id stands for the kind of tetrimino of which the dropping one is
	// x, y stand for the top-left of the dropping tetrimino matrix
	int id, next, hold, column, row, direction;
	int mat[4][4];
} Dropping;

#endif // !_def

void refreshGame();

void showBlock();
void drawGameArea();
void drawBlock(int color, int row, int column, bool isHint);
void drawHintBlock(int row, int column);
void drawBlockOuterBorder(int row, int column);
void drawBlockInnerBorder(int row, int column);
void drawNameQuery();

void dropIt();
void fixIt();
void moveIt(int direction);
void rotateIt();
void dropToBottom();
int findBottomPosition();
void scoreIt(int count,int flag);
void createDropping();
void holdDropping();

bool checkForElimination();
void checkForLevelUp();
void eliminate(int index);
void gravity();

void newGame();
int switchGame(bool isPause);
void gameOver();

char* numToString(int x);