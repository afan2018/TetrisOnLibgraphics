#include "data.h"

linkedlistADT usrData;

FILE* fw;

extern Game game;
extern Dropping drop;
extern int map[24][16];

int popContinueQuery = 0;

void loadScore() {
	fw = fopen("score.dat", "r+");
	if (fw == NULL) {
		// No data file exists
		// Create empty data file
		fw = fopen("score.dat", "w+");
		fprintf(fw, "* -1 -1");
	}
	else {
		while (!feof(fw)) {
			ScoreData *nData = malloc(sizeof(ScoreData));
			fscanf(fw, "%s %d %d", nData->name, &nData->level, &nData->score);
			if (nData->level == -1) break; // end flag
			InsertNode(usrData, NULL, nData); // append new data to the end of linkedlist
		}
	}
	fclose(fw);
}

bool detectSavedGame() {
	fw = fopen("game.dat", "r+");
	if (fw == NULL) return 0;
	int tmp;
	fscanf(fw, "%d", &tmp);
	fclose(fw);
	if (tmp == -1) return 0; // empty saved game data
	return 1;
}

extern bool pauseButtonStatus;

void loadGame() {
	fw = fopen("game.dat", "r+");
	fscanf(fw, "%d %d %d", &game.level, &game.score, &game.elimRowCounter);
	fscanf(fw, "%d %d %d %d %d %d", &drop.column, &drop.row, &drop.direction, &drop.id, &drop.next, &drop.hold);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			fscanf(fw, "%d ", &drop.mat[i][j]);
		}
	}
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 16; j++) {
			fscanf(fw, "%d ", &map[i][j]);
		}
	}
	fclose(fw);
	game.isGaming = 1;
	game.isDropping = 0; // set game to paused
	pauseButtonStatus = 1;
	strcpy(game.usrName, "");
}

void initData() {
	usrData = NewLinkedList(); 
	loadScore(); // load ranklist data
	if (detectSavedGame()) popContinueQuery = 1; // ask the user whether to load saved game
}

void print(ScoreData* x) {
	fprintf(fw, "%s %d %d\n", x->name, x->level, x->score);
}

extern int popRanklist;

void drawRanklist() {
	SetPenColor("black");
	drawRectangle(2.5, 1.5, 7, 9, 1);
	SetPenColor("red");
	drawRectangle(2.5, 1.5, 7, 9, 0);
	MovePen(5.4, 9.8);
	DrawTextString("RANKLIST");
	MovePen(3.6, 9);
	DrawTextString("NAME");
	MovePen(5.6, 9);
	DrawTextString("LEVEL");
	MovePen(7.6, 9);
	DrawTextString("SCORE");
	SetPenColor("white");
	linkedlistADT cur = usrData;
	int cnt = 0;
	
	if (cur->next == NULL) {
		MovePen(5.2, 6);
		DrawTextString("NO RECORD");
	}
	while (cur->next != NULL && cnt < 8) { // no more than top 8
		ScoreData *nextData = cur->next->dataptr;
		cnt++;
		MovePen(3, 9 - cnt * 0.8);
		DrawTextString(numToString(cnt));
		MovePen(3.6, 9 - cnt * 0.8);
		DrawTextString(nextData->name);
		MovePen(5.6, 9 - cnt * 0.8);
		DrawTextString(numToString(nextData->level));
		MovePen(7.6, 9 - cnt * 0.8);
		DrawTextString(numToString(nextData->score));
		cur = cur->next;
	}
	if (button(GenUIID(0), 5, 1.8, 2, 0.5, "DISMISS")) {
		popRanklist = 0; // dismiss query
	}
}

void saveScoreData() {
	ScoreData *nData = malloc(sizeof(ScoreData));
	nData->score = game.score;
	nData->level = game.level;
	strcpy(nData->name, game.usrName);
	// ***************
	if (usrData->next == NULL) { // usrData is empty
		InsertNode(usrData, usrData, nData);
		writeScoreData();
		return;
	}
	// *************** not needed?
	linkedlistADT cur = usrData;
	while (cur->next != NULL) {
		ScoreData *nextData = cur->next->dataptr;
		if (nextData->score <= nData->score) {
			InsertNode(usrData, cur, nData);
			writeScoreData();
			return;
		}
		cur = cur->next;
	}
	InsertNode(usrData, cur, nData);
	writeScoreData();
}

void writeScoreData() {
	fw = fopen("score.dat", "w+");
	TraverseLinkedList(usrData, print);
	fprintf(fw, "* -1 -1");
	fclose(fw);
}

void writeGameData() {
	fw = fopen("game.dat", "w+");
	fprintf(fw, "%d %d %d\n", game.level, game.score, game.elimRowCounter);
	fprintf(fw, "%d %d %d %d %d %d\n", drop.column, drop.row, drop.direction, drop.id, drop.next, drop.hold);
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			fprintf(fw, "%d ", drop.mat[i][j]);
		}
		fprintf(fw, "\n");
	}
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 16; j++) {
			fprintf(fw, "%d ", map[i][j]);
		}
		fprintf(fw, "\n");
	}
	fclose(fw);
}

void drawContinueQuery() {
	SetPenColor("black");
	drawRectangle(3, 5, 6, 3, 1);
	SetPenColor("red");
	drawRectangle(3, 5, 6, 3, 0);
	MovePen(4.3, 7.2);
	DrawTextString("SAVED GAME DETECTED");
	MovePen(4.2, 6.5);
	DrawTextString("Would you like to continue?");
	if (button(GenUIID(0), 3.8, 5.4, 2, 0.5, "Continue")) {
		loadGame();
		erase(); // saved game data will be read only once
		popContinueQuery = 0;
	}
	if (button(GenUIID(0), 6.2, 5.4, 2, 0.5, "Cancel")) {
		erase(); // saved game data will be read only once
		popContinueQuery = 0;
	}
}

void erase() {
	fw = fopen("game.dat", "w+");
	fprintf(fw, "-1 -1 -1");
	fclose(fw);
}