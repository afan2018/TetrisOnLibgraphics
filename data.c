#include "data.h"

linkedlistADT usrData;

FILE* fw;

typedef struct {
	int score;
	int level;
	char name[25];
} ScoreData;

extern Game game;
extern Dropping drop;
extern int map[24][16];

int popContinueQuery = 0;

void loadScore() {
	fw = fopen("score.dat", "r+");
	if (fw == NULL) {
		fw = fopen("score.dat", "w+");
		fprintf(fw, "* -1 -1");
	}
	else {
		while (!feof(fw)) {
			ScoreData *nData = malloc(sizeof(ScoreData));
			fscanf(fw, "%s %d %d", nData->name, &nData->level, &nData->score);
			if (nData->level == -1) break;
			InsertNode(usrData, NULL, nData);
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
	if (tmp == -1) return 0;
	return 1;
}

void loadGame() {
	fw = fopen("game.dat", "r+");
	fscanf(fw, "%d %d %d", &game.level, &game.score, &game.elimRowCounter);
	fscanf(fw, "%d %d %d %d", &drop.column, &drop.row, &drop.direction, &drop.id);
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
	game.isDropping = 0;
	strcpy(game.usrName, "");
}

void initData() {
	usrData = NewLinkedList(); 
	loadScore();
	if (detectSavedGame()) popContinueQuery = 1;
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
	while (cur->next != NULL && cnt < 8) {
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
		popRanklist = 0;
	}
}

void saveScoreData() {
	ScoreData *nData = malloc(sizeof(ScoreData));
	nData->score = game.score;
	nData->level = game.level;
	strcpy(nData->name, game.usrName, sizeof(game.usrName));
	if (usrData->next == NULL) {
		InsertNode(usrData, usrData, nData);
		writeScoreData();
		return;
	}
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
	fprintf(fw, "%d %d %d %d\n", drop.column, drop.row, drop.direction, drop.id);
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
		erase();
		popContinueQuery = 0;
	}
	if (button(GenUIID(0), 6.2, 5.4, 2, 0.5, "Cancel")) {
		erase();
		popContinueQuery = 0;
	}
}

void erase() {
	fw = fopen("game.dat", "w+");
	fprintf(fw, "-1 -1 -1");
	fclose(fw);
}