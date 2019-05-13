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
void drawBlock(int color, int x, int y);
void drawBlockOuterBorder(int x, int y);
void drawBlockInnerBorder(int x, int y);

void dropIt();
void fixIt();
void moveIt(int direction);
void rotateIt();

bool checkForElimination();
void eliminate(int index);
void gravity();