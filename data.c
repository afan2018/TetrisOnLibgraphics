#include "data.h"
#include "game.h"
#include "imgui.h"

linkedlistADT usrData;

void initData() {
	usrData = NewLinkedList();
}

typedef struct {
	int score;
	int level;
	char name[25];
} ScoreData;

int totalUsr;

void print(ScoreData* x) {
	printf("%s %d %d\n", x->name, x->score, x->level);
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

void saveScoreData(int score, int level, char* name) {
	ScoreData *nData = malloc(sizeof(ScoreData));
	nData->score = score;
	nData->level = level;
	strcpy(nData->name, name, sizeof(name));
	if (usrData->next == NULL) {
		InsertNode(usrData, usrData, nData);
		return;
	}
	linkedlistADT cur = usrData;
	while (cur->next != NULL) {
		ScoreData *nextData = cur->next->dataptr;
		if (nextData->score <= nData->score) {
			InsertNode(usrData, cur, nData);
			return;
		}
		cur = cur->next;
	}
	InsertNode(usrData, cur, nData);
}

