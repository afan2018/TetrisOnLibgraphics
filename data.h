#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "linkedlist.h"
#include "game.h"
#include "imgui.h"

#ifndef _defSD
#define _defSD

typedef struct {
	int score;
	int level;
	char name[25];
} ScoreData;

#endif

void initData();
void loadScore();
void loadGame();
void print(ScoreData *x);
void erase();

void drawRanklist();

void saveScoreData();
void writeScoreData();
void writeGameData();

void drawContinueQuery();