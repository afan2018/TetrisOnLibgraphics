#include "game.h"

#define GameStartX 0
#define GameEndX 8
#define GameStartY 0
#define GameEndY 12

#define BlockSize 0.5
#define BlockMargin 0.05

// 0 - 15 X
// 0 - 23 Y
// coordinate X and Y stand for the bottom-left of the block
// 0 stands for not occupied
// different values in map stand for different colors

int map[16][24];

int Tetriminos[10][4][4] = {
	{{0,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,1,0,0}},//Cis-L 1

	{{0,0,0,0},
	{0,2,0,0},
	{0,2,0,0},
	{2,2,0,0}},//Trans-L 2

	{{0,0,0,0},
	{3,0,0,0},
	{3,3,0,0},
	{0,3,0,0}},//Cis-S 3

	{{0,0,0,0},
	{0,4,0,0},
	{4,4,0,0},
	{4,0,0,0}},//Trans-S 4

	{{0,0,0,0},
	{0,0,0,0},
	{5,5,0,0},
	{5,5,0,0}},//O 5

	{{6,0,0,0},
	{6,0,0,0},
	{6,0,0,0},
	{6,0,0,0}},//I 6

	{{0,0,0,0},
	{0,0,0,0},
	{0,7,0,0},
	{7,7,7,0}}//E 7

};

struct Dropping {
	// id stands for the kind of tetrimino of which the dropping one is
	// x, y stand for the bottom-left of the dropping tetrimino matrix
	int id, x, y;
} drop;

bool isDropping;

void showBlock() {
	int i, j;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 24; j++)
			if (map[i][j] != 0) drawBlock(map[i][j], i, j);
	if (isDropping) {
		
		printf("%d %d %d \n", drop.id, drop.x, drop.y);
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++) {
				if (Tetriminos[drop.id][i][j] != 0 && drop.x + i >= 0 && drop.x + i <= 15 && drop.y + j >= 0 && drop.y+ j <= 23) {
					printf("%d %d %d %d *** \n", i, j, drop.x + i, drop.y + j);
					drawBlock(drop.id + 1, drop.x + i, drop.y + j);
				}
				
			}
	}
}

void drawBlock(int color, int x, int y) {
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
		SetPenColor("black");
		break;
	}
	drawBlockOuterBorder(x, y);
	drawBlockInnerBorder(x, y);
}

void drawBlockOuterBorder(int x, int y) {
	SetPenSize(2);
	MovePen(x*BlockSize, y*BlockSize);
	DrawLine(BlockSize, 0);
	DrawLine(0, BlockSize);
	DrawLine(-BlockSize, 0);
	DrawLine(0, -BlockSize);
}

void drawBlockInnerBorder(int x, int y) {
	SetPenSize(1);
	// TODO: Figure out why there are minor adjustments.
	MovePen(x*BlockSize+BlockMargin-0.005, y*BlockSize+BlockMargin+0.005);
	DrawLine(BlockSize-2*BlockMargin, 0);
	DrawLine(0, BlockSize-2*BlockMargin);
	DrawLine(-BlockSize+2*BlockMargin, 0);
	DrawLine(0, -BlockSize+2*BlockMargin);
}

int speed = 1, count;

void refreshGame() {
	if (!isDropping) {
		count = 0;
		drop.id = (int)(rand() * 10) % 7;
		drop.x = 6;
		drop.y = 23;
		isDropping = 1;
		return;
	}
	if (count == speed) {
		count = 0;
		dropIt();
		return;
	}
	count++;
}

void dropIt() {
	int i, j;
	bool isFixed = 0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (Tetriminos[drop.id][i][j] != 0 && (map[drop.x + i][drop.y + j - 1] != 0 || drop.y + j == 0)) {
				fixIt();
				isFixed = 1;
			}
		}
	if (isFixed) return;
	drop.y--;
}

void fixIt() {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (Tetriminos[drop.id][i][j]) map[drop.x + i][drop.y + j] = drop.id + 1;
	isDropping = 0;
}

void moveIt(int id) {
	int direction[5][2] = { {-1},{1} };
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (Tetriminos[drop.id][i][j] != 0 && (map[drop.x + i + direction[id][0]][drop.y + j] || drop.x + i + direction[id][0] < 0 || drop.x + i + direction[id][0] > 15)) return;
	drop.x += direction[id][0];
}