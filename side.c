#include "side.h"

extern Game game;
extern Dropping drop;
extern Tetriminos[10][4][4][4];
extern theme;

void drawScoreboard() {
	SetPenColor(theme ? "Background1" : "Border1");
	drawBox(9, 10.5, 2, 1, 0, game.isGaming ? numToString(game.score) : "HAPPY", "L", theme ? "Side1" : "Red1");
	MovePen(9.55, 11.7);
	DrawTextString("SCORE");
}

void drawLevelboard() {
	SetPenColor(theme ? "Background1" : "Border1");
	drawBox(9, 8.8, 2, 1, 0, game.isGaming ? numToString(game.level) : "HAPPY", "L", theme ? "Side2" : "Side4");
	MovePen(9.6, 10);
	DrawTextString("LEVEL");
}

extern int goal[10];

void drawGoalboard() {
	SetPenColor(theme ? "Background1" : "Border1");
	drawBox(9, 7, 2, 1, 0, game.isGaming ? numToString(goal[game.level] - game.elimRowCounter) : "TETRIS!", "L", theme ? "Side2" : "Side4");
	MovePen(9.65, 8.2);
	DrawTextString("GOAL");
}

void drawPause() {
	SetPenColor(theme ? "Red1" : "Side3");
	MovePen(9.2, 6.2);
	DrawTextString("---PAUSED---");
}

void drawNextDropping() {
	if (!game.isGaming) return;
	MovePen(9.6, 5.5);
	SetPenColor(theme ? "Font1" : "Font2");
	DrawTextString("NEXT");
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (drop.next == 5) {
				if (Tetriminos[drop.next][1][i][j] != 0) {
					drawBlock(drop.next + 1, 8 - i, 18 + j, 0);
				}
			}
			else if (Tetriminos[drop.next][0][i][j] != 0) {
				drawBlock(drop.next + 1, 9 - i, 19 + j, 0);
			}
		}
}

void drawHoldDropping() {
	if (!game.isGaming) return;
	MovePen(9.6, 2.5);
	SetPenColor(theme ? "Font1" : "Font2");
	DrawTextString("HOLD");
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (drop.hold == 5) {
				if (Tetriminos[drop.hold][1][i][j] != 0) {
					drawBlock(drop.hold + 1, 2 - i, 18 + j, 0);
				}
			}
			else if (Tetriminos[drop.hold][0][i][j] != 0) {
				drawBlock(drop.hold + 1, 3 - i, 19 + j, 0);
			}
		}
}