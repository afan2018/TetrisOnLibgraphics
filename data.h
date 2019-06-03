#ifndef _DATA
#define _DATA

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "linkedlist.h"

#include "imgui.h"
#include "md5.h"

#include "game.h"

typedef struct {
	int score;
	int level;
	char name[25];
} ScoreData;



void initData();
void loadScore();
void loadGame();
void print(ScoreData *x);
void erase(char* fileName);

void drawRanklist();

void saveScoreData();
void writeScoreData();
void writeGameData();

void drawLoadGameQuery();

void encode(char* str, char *fileName);
bool verify(char* str, char *fileName);

char* textFileRead(char* filename);

#endif