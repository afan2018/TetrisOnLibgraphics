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

void refreshGame();

void showBlock();
void drawGameArea();
void drawBlock(int color, int row, int column);
void drawHintBlock(int row, int column);
void drawBlockOuterBorder(int row, int column);
void drawBlockInnerBorder(int row, int column);
void drawScoreboard();
void drawLevelboard();
void drawGoalboard();
void drawDanger(int flag);
void drawNameQuery();

void dropIt();
void fixIt();
void moveIt(int direction);
void rotateIt();
void dropToBottom();
int findBottomPosition();
void scoreIt(int count,int flag);

bool checkForElimination();
void checkForLevelUp();
void eliminate(int index);
void gravity();

void newGame();
int switchGame(bool isPause);
void gameOver();

char* numToString(int x);