#include "data.h"

linkedlistADT usrData;

FILE* fw;

extern Game game;
extern Dropping drop;
extern int map[24][16];

char * c[] = { "Menu2","Menu2","Menu1","Menu1","Menu3","Menu3","Menu4","Menu4" };

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

char* textFileRead(char* filename) {
	char* t;
	FILE *pf = fopen(filename, "rb");
	fseek(pf, 0, SEEK_END);
	long lSize = ftell(pf);
	t = (char*)malloc(sizeof(char)*(lSize)+20);
	rewind(pf);
	fread(t, sizeof(char), lSize, pf);
	t[lSize] = '\0';
	fclose(pf);
	return t;
}

bool detectSavedGame() {
	fw = fopen("game.dat", "r+");
	if (fw == NULL) return 0;
	int tmp;
	fscanf(fw, "%d", &tmp);
	fclose(fw);
	if (tmp == -1) return 0;
	return verify(textFileRead("game.dat"), "game.ver");
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
	game.isDropping = 0;
	pauseButtonStatus = 1;
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
extern int theme;

void drawRanklist() {
	if (switchGame(1) != -1) pauseButtonStatus = 1;
	SetPenColor("Background1");
	drawRectangle(2.5, 1.5, 7, 9, 1);
	SetPenColor("Border1");
	drawRectangle(2.5, 1.5, 7, 9, 0);
	MovePen(5.4, 9.8);
	DrawTextString("RANKLIST");
	MovePen(3.6, 9);
	DrawTextString("NAME");
	MovePen(5.6, 9);
	DrawTextString("LEVEL");
	MovePen(7.6, 9);
	DrawTextString("SCORE");
	SetPenColor("Font1");
	linkedlistADT cur = usrData;
	int cnt = 0;
	
	if (cur->next == NULL) {
		MovePen(5.2, 6);
		DrawTextString("NO RECORD");
	}
	while (cur->next != NULL && cnt < 7) {
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
	setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	if (button(GenUIID(0), 5, 1.8, 2, 0.5, "DISMISS")) {
		popRanklist = 0;
	}
	if (button(GenUIID(0), 3.2, 9.65, 1.5, 0.5, "CLEAR")) {
		FreeLinkedList(usrData);
		usrData = NewLinkedList();
		erase("score.dat");
	}
}

void saveScoreData() {
	ScoreData *nData = malloc(sizeof(ScoreData));
	nData->score = game.score;
	nData->level = game.level;
	strcpy(nData->name, game.usrName);
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
	fprintf(fw, "-1 -1 -1");
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
	encode(textFileRead("game.dat"), "game.ver");
}

void drawLoadGameQuery() {
	SetPenColor("Background1");
	drawRectangle(3, 5, 6, 3, 1);
	SetPenColor("Border1");
	drawRectangle(3, 5, 6, 3, 0);
	MovePen(4.3, 7.2);
	DrawTextString("SAVED GAME DETECTED");
	MovePen(4.2, 6.5);
	DrawTextString("Would you like to continue?");
	setTextBoxColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setButtonColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	setMenuColors(c[theme * 4], c[theme * 4 + 1], c[theme * 4 + 2], c[theme * 4 + 3], 0);
	if (button(GenUIID(0), 3.8, 5.4, 2, 0.5, "Continue")) {
		loadGame();
		popContinueQuery = 0;
	}
	if (button(GenUIID(0), 6.2, 5.4, 2, 0.5, "Cancel")) {
		erase("game.dat");
		popContinueQuery = 0;
	}
}

void erase(char* fileName) {
	fw = fopen(fileName, "w+");
	fprintf(fw, "-1 -1 -1");
	fclose(fw);
}

void encode(char* str, char *fileName) {
	int i;
	strcat(str, "{DuoGeiDianFenBa}");
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, str, strlen((char *)str));
	MD5Final(&md5, decrypt);
	fw = fopen(fileName, "w+");
	for (i = 0; i < 16; i++) {
		fprintf(fw, "%02x ", decrypt[i]);
	}
 	fclose(fw);
}

bool verify(char* str, char *fileName) {
	int i;
	fw = fopen(fileName, "r+");
	if (fw == NULL) return 0;
	strcat(str, "{DuoGeiDianFenBa}");
	unsigned char *encrypt = str;
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, encrypt, strlen((char *)encrypt));
	MD5Final(&md5, decrypt);
	int x;
	for (i = 0; i < 16; i++) {
		fscanf(fw, "%02x", &x);
		if (decrypt[i] != x) {
			fclose(fw);
			return 0;
		}
	}
	fclose(fw);
	return 1;
}
