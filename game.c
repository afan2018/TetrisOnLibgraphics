#include "game.h"

#define GameStartX 0
#define GameEndX 8
#define GameStartY 0
#define GameEndY 12

#define BlockSize 0.5
#define BlockMargin 0.05

extern int stop;
extern int start;
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
		{ {0, 5, 0, 0},
		{ 5,5,0,0 },
		{ 5,0,0,0 },
		{ 0,0,0,0 }},

		{ {0,0,0,0},
		{ 5,5,0,0 },
		{ 0,5,5,0 },
		{ 0,0,0,0 } },

		{ {0,0,5,0 },
		{ 0,5,5,0 },
		{ 0,5,0,0 },
		{ 0,0,0,0 } },

		{ {5,5,0,0},
		{ 0,5,5,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } }
	},

	{
		{ {6, 6, 0, 0},
		{ 6,6,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {6, 6, 0, 0},
		{ 6,6,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {6, 6, 0, 0},
		{ 6,6,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {6, 6, 0, 0},
		{ 6,6,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }}
	},

	{
		{ {7, 0, 0, 0},
		{ 7,0,0,0 },
		{ 7,0,0,0 },
		{ 7,0,0,0 }},

		{ {7, 7, 7, 7},
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }},

		{ {7, 0, 0, 0},
		{ 7,0,0,0 },
		{ 7,0,0,0 },
		{ 7,0,0,0 }},

		{ {7, 7, 7, 7},
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

struct Dropping {
	// id stands for the kind of tetrimino of which the dropping one is
	// x, y stand for the top-left of the dropping tetrimino matrix
	int id, column, row, direction;
	int mat[4][4];
} drop;

bool isDropping;

void showBlock() {
	int i, j;
	for (i = 0; i < 24; i++)
		for (j = 0; j < 16; j++)
			if (map[i][j] != 0) drawBlock(map[i][j], i, j, 0);
	if (isDropping) {
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
	}
}

void drawBlock(int color, int row, int column,int isHint) {
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
		SetPenColor("white");
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
	SetPenSize(1);
	// TODO: Figure out why there are minor adjustments.
	MovePen(column*BlockSize+BlockMargin-0.005, row*BlockSize+BlockMargin+0.005);
	DrawLine(BlockSize-2*BlockMargin, 0);
	DrawLine(0, BlockSize-2*BlockMargin);
	DrawLine(-BlockSize+2*BlockMargin, 0);
	DrawLine(0, -BlockSize+2*BlockMargin);
}

int speed = 5, count;

void refreshGame() {
	if ((!isDropping)&&(start==1)) {
		count = 0;
		drop.id = (int)(rand() * 10) % 7;
		memcpy(drop.mat, Tetriminos[drop.id][0], sizeof(drop.mat));
		drop.direction = 0;
		drop.column = 6;
		drop.row = 24;
		isDropping = 1;
		return;
	}
	if ((count == speed)&&(stop==0)) {
		count = 0;
		dropIt();
		return;
	}
	if ((count == speed) && (stop == 1)) {
		return;
	}
	count++;
}

void dropIt() {
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
			}
			map[drop.row - i][drop.column + j] = drop.id + 1;
		}
	isDropping = 0;
	while (checkForElimination());
}

void moveIt(int id) {
	int direction[5][2] = { {-1},{1} };
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (drop.mat[i][j] != 0 && (map[drop.row - i][drop.column + j + direction[id][0]] || drop.column + j + direction[id][0] < 0 || drop.column + j + direction[id][0] > 15))
				return;
	drop.column += direction[id][0];
}

bool checkForElimination() {
	int i, j;
	bool didSomething = 0;
	for (i = 0; i < 24; i++) {
		bool elimAble = 1;
		for (j = 0; j < 16; j++) {
			if (map[i][j] == 0) {
				elimAble = 0;
				break;
			}
		}
		if (elimAble) {
			didSomething = 1;
			eliminate(i);
			//gravity();
		}
	}
	return didSomething;
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


// Is this needed?
/*
 ........
 .*......
 ********
 ......**
 ......**
*/
void gravity() {
	int i, j;
	for (j = 1; j < 24; j++) {
		for (i = 0; i < 16; i++) {
			if (map[i][j] == 0) continue;
			if (((i == 0) || (i - 1 >= 0 && map[i - 1][j - 1] == 0)) && (map[i][j - 1] == 0) && ((i == 23 || (i + 1 < 24 && map[i + 1][j - 1] == 0)))) {
				map[i][j - 1] = map[i][j];
				map[i][j] = 0;
			}
		}
	}
}

void rotateIt() {
	if (!isDropping) return;
	int i, j, k;
	for (k = 0; k < 4; k++) {
		bool feasible = 1;
		drop.direction = (drop.direction + 1) % 4;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (Tetriminos[drop.id][drop.direction][i][j] != 0 && (map[drop.row - i][drop.column + j] || drop.row - i < 0 || drop.column + j > 15)) feasible = 0;
			}
		}
		if (feasible) {
			memcpy(drop.mat, Tetriminos[drop.id][drop.direction],sizeof(drop.mat));
			return;
		}
	}
}

void dropToBottom() {
	drop.row = findBottomPosition();
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

void gameOver() {
	int i, j;
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 16; j++) {
			if (map[i][j]) map[i][j] = 8;
		}
	}
	drop.id = 7;
	showBlock();
	cancelTimerEvent(1);
}