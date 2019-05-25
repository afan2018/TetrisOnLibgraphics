#include "data.h"
#include "game.h"

linkedlistADT usrData;

void init() {
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
		}
		cur = cur->next;
	}
	InsertNode(usrData, cur, nData);
}

