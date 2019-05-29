#include "game.h"
#include "imgui.h"
#include "graphics.h"
#include "data.h"
#include "side.h"

#define GameStartX 0
#define GameEndX 8
#define GameStartY 0
#define GameEndY 12

#define BlockSize 0.5
#define BlockMargin 0.06

#define GameAreaWidth 8
#define GameAreaHeight 12

// 0 - 23 rows
// 0 - 15 column
// coordinate stand for the bottom-left of the block
// 0 stands for not occupied
// different values in map stand for different colors

int map[26][16];

int Tetriminos[10][4][4][4] = {
	
{
		{{1,1,0,0},
		{ 1,0,0,0 },
		{ 1,0,0,0 },
		{ 0,0,0,0 }},

		{{0,0,0,0},
		{ 1,0,0,0 },
		{ 1,1,1,0 },
		{ 0,0,0,0 }},

		{{0,0,1,0 },
		{ 0,0,1,0 },
		{ 0,1,1,0 },
		{ 0,0,0,0 }},

		{{1,1,1,0},
		{ 0,0,1,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }}
	},

	{
		{{2,2,0,0},
		{ 0,2,0,0 },
		{ 0,2,0,0 },
		{ 0,0,0,0 }},

		{ {0,0,0,0},
		{ 2,2,2,0 },
		{ 2,0,0,0 },
		{ 0,0,0,0 }},

		{ {0,2,0,0 },
		{ 0,2,0,0 },
		{ 0,2,2,0 },
		{ 0,0,0,0 }},

		{ {0,0,2,0},
		{ 2,2,2,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } }
	},

	{
		{ {3, 0, 0, 0},
		{ 3,3,0,0 },
		{ 0,3,0,0 },
		{ 0,0,0,0 }},

		{ {0,0,0,0},
		{ 0,3,3,0 },
		{ 3,3,0,0 },
		{ 0,0,0,0 } },

		{ {0,3,0,0 },
		{ 0,3,3,0 },
		{ 0,0,3,0 },
		{ 0,0,0,0 } },

		{ {0,3,3,0},
		{ 3,3,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } }
	},

	{
		{ {0, 4, 0, 0},
		{ 4,4,0,0 },
		{ 4,0,0,0 },
		{ 0,0,0,0 }},

		{ {0,0,0,0},
		{ 4,4,0,0 },
		{ 0,4,4,0 },
		{ 0,0,0,0 } },

		{ {0,0,4,0 },
		{ 0,4,4,0 },
		{ 0,4,0,0 },
		{ 0,0,0,0 } },

		{ {4,4,0,0},
		{ 0,4,4,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } }
	},

	{
		{ {5, 5, 0, 0},
		{ 5,5,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {5, 5, 0, 0},
		{ 5,5,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {5, 5, 0, 0},
		{ 5,5,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {5, 5, 0, 0},
		{ 5,5,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }}
	},

	{
		{ {6, 0, 0, 0},
		{ 6,0,0,0 },
		{ 6,0,0,0 },
		{ 6,0,0,0 }},

		{ {6, 6, 6, 6},
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {6, 0, 0, 0},
		{ 6,0,0,0 },
		{ 6,0,0,0 },
		{ 6,0,0,0 }},

		{ {6, 6, 6, 6},
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},
	},

	{
		{ {0, 7, 0, 0},
		{ 7,7,7,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {0,7,0,0},
		{ 7,7,0,0 },
		{ 0,7,0,0 },
		{ 0,0,0,0 } },

		{ {0,0,0,0 },
		{ 7,7,7,0 },
		{ 0,7,0,0 },
		{ 0,0,0,0 } },

		{ {0,7,0,0},
		{ 0,7,7,0 },
		{ 0,7,0,0 },
		{ 0,0,0,0 } }
	}
};

int popNameQuery = 0;

Dropping drop;

Game game;

void showBlock() {
	int i, j;
	for (i = 0; i < 24; i++)
		for (j = 0; j < 16; j++)
			if (map[i][j] != 0) drawBlock(map[i][j], i, j, 0);
	int bottom = findBottomPosition();
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (drop.mat[i][j] != 0 && bottom - i < 24) {
				drawBlock(8, bottom - i, drop.column + j, 1);
			}
		}
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (drop.mat[i][j] != 0 && drop.row - i  < 24) {
				drawBlock(drop.id + 1, drop.row - i, drop.column + j, 0);
			}
		}
	if (game.isGaming && !game.isDropping) drawPause();
}

void drawGameArea() {
	SetPenColor("red");
	SetPenSize(3);
	MovePen(GameAreaWidth, 0);
	DrawLine(0, GameAreaHeight);
	DrawLine(-GameAreaHeight, 0);
}

extern int theme;

void drawBlock(int color, int row, int column,bool isHint) {
	switch (color) {
	case 1:
		SetPenColor("red");
		break;
	case 2:
		SetPenColor("blue");
		break;
	case 3:
		SetPenColor("magenta");
		break;
	case 4:
		SetPenColor("orange");
		break;
	case 5:
		SetPenColor("violet");
		break;
	case 6:
		SetPenColor("green");
		break;
	case 7:
		SetPenColor(theme ? "white" : "black");
		break;
	case 8:
		SetPenColor("dark gray");
	}
	if (isHint) {
		drawHintBlock(row, column);
		return;
	}
	drawBlockOuterBorder(row, column);
	drawBlockInnerBorder(row, column);
}

void drawHintBlock(int row, int column) {
	SetPenSize(2);
	MovePen(column*BlockSize, row*BlockSize);
	DrawLine(BlockSize, 0);
	DrawLine(0, BlockSize);
	DrawLine(-BlockSize, 0);
	DrawLine(0, -BlockSize);
}

void drawBlockOuterBorder(int row, int column) {
	SetPenSize(2);
	MovePen(column*BlockSize, row*BlockSize);
	DrawLine(BlockSize, 0);
	DrawLine(0, BlockSize);
	DrawLine(-BlockSize, 0);
	DrawLine(0, -BlockSize);
}

void drawBlockInnerBorder(int row, int column) {
	drawRectangle(column*BlockSize + BlockMargin - 0.005, row*BlockSize + BlockMargin + 0.005, BlockSize - 2 * BlockMargin, BlockSize - 2 * BlockMargin, 1);
}

void drawNameQuery() {
	SetPenColor("black");
	drawRectangle(3, 5, 6, 3, 1);
	SetPenColor("red");
	drawRectangle(3, 5, 6, 3, 0);
	static char name[25] = "";
	textbox(GenUIID(0), 4, 6.2, 4, 0.5, name, sizeof(name));
	MovePen(4.6, 7);
	DrawTextString("TELL ME YOUR NAME");
	MovePen(5.2, 7.5);
	DrawTextString("GAME OVER");
	if (button(GenUIID(0), 5, 5.4, 2, 0.5, "OK")) {
		strcpy(game.usrName, name);
		strcpy(name, "");
		popNameQuery = 0;
		saveScoreData();
		game.isGaming = 0;
	}
}

int speed = 10, count;

void refreshGame() {
	if (!game.isGaming || !game.isDropping) return;
	if (count == speed - game.level) {
		count = 0;
		dropIt();
		return;
	}
	count++;
}

void dropIt() {
	if (!game.isDropping) return;
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (drop.mat[i][j] != 0 && (map[drop.row - i - 1][drop.column + j] != 0 || drop.row - i == 0)) {
				fixIt();
				return;
			}
		}
	drop.row--;
}

void fixIt() {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (!drop.mat[i][j]) continue;
			if (drop.row - i > 23) {
				gameOver();
				return;
			}
			map[drop.row - i][drop.column + j] = drop.id + 1;
		}
	while (checkForElimination());
	checkForLevelUp();
	createDropping();
	writeGameData();
}

bool usedHold = 0;

void createDropping() {
	usedHold = 0;
	drop.id = drop.next == -1 ? (int)(rand() * 10) % 7 : drop.next;
	drop.next = (int)(rand() * 10) % 7;
	memcpy(drop.mat, Tetriminos[drop.id][0], sizeof(drop.mat));
	drop.direction = 0;
	drop.column = 6;
	drop.row = 24;
	return;
}

void moveIt(int id) {
	if (!game.isDropping || id > 1) return;
	int direction[5][2] = { {-1},{1} };
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (drop.mat[i][j] != 0 && (map[drop.row - i][drop.column + j + direction[id][0]] || drop.column + j + direction[id][0] < 0 || drop.column + j + direction[id][0] > 15))
				return;
	drop.column += direction[id][0];
}

bool checkForElimination() {
	int i, j, elimRowCounter = 0;
	for (i = 0; i < 24; i++) {
		bool elimAble = 1;
		for (j = 0; j < 16; j++) {
			if (map[i][j] == 0) {
				elimAble = 0;
				break;
			}
		}
		if (elimAble) {
			elimRowCounter++;
			eliminate(i);
			//gravity();
		}
	}
	scoreIt(elimRowCounter, 0);
	game.elimRowCounter += elimRowCounter;
	return elimRowCounter != 0;
}

void eliminate(int index) {
	int i, j;
	for (i = index; i < 24; i++) {
		bool isBlank = 1;
		for (j = 0; j < 16; j++) {
			if (map[i + 1][j] != 0) isBlank = 0;
			map[i][j] = map[i + 1][j];
		}
		if (isBlank) break;
	}
}

int goal[10] = { 0,5,10,15,20,20,20,20,20,20 };

void checkForLevelUp() {
	if (game.elimRowCounter >= goal[game.level]) {
		game.elimRowCounter -= goal[game.level];
		game.level++;
	}
}

void rotateIt() {
	if (!game.isDropping) return;
	int i, j, k, l, py[3] = { 0,1,-1 };
	if (drop.id == 5) py[1] = 3, py[2] = -3;
	for (l = 0; l <= 2; l++) {
		for (k = 0; k < (drop.id == 5 ? 1 : 3); k++) {
			bool feasible = 1;
			drop.direction = (drop.direction + 1) % 4;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (Tetriminos[drop.id][drop.direction][i][j] != 0 && (map[drop.row - i][drop.column + py[l] + j] || drop.row - i < 0 || drop.column + py[l] + j > 15))
						feasible = 0;
				}
			}
			if (feasible) {
				drop.column += py[l];
				memcpy(drop.mat, Tetriminos[drop.id][drop.direction],sizeof(drop.mat));
				return;
			}
		}
	}
}

void dropToBottom() {
	if (!game.isDropping) return;
	int bottom = findBottomPosition();
	scoreIt(drop.row - bottom, 1);
	drop.row = bottom;
	fixIt();
}

int findBottomPosition() {
	int i, j, k;
	for (k = drop.row - 1; k >= 0; k--) {
		bool flag = 0;
		for (i = 3; i >= 0; i--) {
			for (j = 0; j < 4; j++) {
				if (!drop.mat[i][j]) continue;
				if (k - i < 0) {
					return k + 1;
				}
				if (map[k - i][drop.column + j]) {
					return k + 1;
				}
			}
		}
	}
	return 0;
}

void newGame() {
	game.isGaming = 1;
	game.isDropping = 1;
	game.score = 0;
	game.elimRowCounter = 0;
	game.level = 1;
	drop.next = -1;
	drop.hold = -1;
	createDropping();
	memset(map, 0, sizeof(map));
	erase();
}

int switchGame(bool isPause) {
	if (!game.isGaming) return -1;
	if (isPause) {
		game.isDropping = 0;
	}
	else game.isDropping = 1;
	return 0;
}

void gameOver() {
	int i, j;
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 16; j++) {
			if (map[i][j]) map[i][j] = 8;
		}
	}
 	drop.id = 7;
	game.isDropping = 0;
	showBlock();
	popNameQuery = 1;
	erase();
}

int addScore[5] = { 0,100,200,400,800 };

void scoreIt(int count, int flag) {
	game.score += (flag ? count : addScore[count]) * game.level;
}

char* numToString(int x) {
	if (x == 0) return "0";
	static char str[15];
	int digit[15] = { 0 }, i, top=0;
	while (x) {
		digit[top] = x % 10;
		x /= 10;
		top++;
	}
	for (i = top - 1; i >= 0; i--) {
		str[top - i - 1] = digit[i] + '0';
	}
	str[top] = '\0';
	return str;
}

void holdDropping() {
	if (usedHold || !game.isDropping) return;
	if (drop.hold == -1) {
		drop.hold = drop.id;
		createDropping();
		return;
	}
	int tmp;
	tmp = drop.hold;
	drop.hold = drop.id;
	drop.id = tmp;
	drop.column = 6;
	drop.row = 24;
	memcpy(drop.mat, Tetriminos[drop.id][0], sizeof(drop.mat));
	usedHold = 1;
}