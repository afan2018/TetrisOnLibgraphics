#ifndef _GAME
#define _GAME

#include "graphics.h"
#include "extgraph.h"

#include "imgui.h"

#include "data.h"
#include "side.h"

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
	int id;
	int next;
	int hold;
	int column, row;
	int direction;
	bool ready;
	int mat[4][4];
} Dropping;

void refreshGame();

void showBlock();
void drawGameArea();
void drawBlock(int color, int row, int column, bool isHint);
void drawHintBlock(int row, int column);
void drawBlockOuterBorder(int row, int column);
void drawBlockInnerBorder(int row, int column);
void drawNameQuery();
void drawRUSure();

void dropIt();
void fixIt();
void moveIt(int direction);
void rotateIt();
void dropToBottom();
void scoreIt(int count, int flag);
void createDropping();
void holdDropping();
int findBottomPosition();

bool checkForElimination();
void checkForLevelUp();
void eliminate(int index);

void newGame();
int switchGame(bool isPause);
void gameOver();

char* numToString(int x);

#endif